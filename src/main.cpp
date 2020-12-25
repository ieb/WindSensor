
#include <Arduino.h>
#include <Wire.h>
#include <AltSoftSerial.h>

// #include <SoftwareSerial.h>  // http://arduino.cc/en/Reference/softwareSerial


#define AMS_5600_ADDRESS 0x36
#define AMS_5600_RAW_AND_HI 0x0c
#define AMS_5600_RAW_AND_LO 0x0d
#define AMS_5600_STAT 0x0b
#define PULSE_PIN 2

// RF hardware setup
#define RF_TX_PIN 5
#define RF_RX_PIN 4
#define RF_DATA_EN_PIN 6

// RF device setup
#define RF_ID "AT+RFID1021"
#define RF_DEV_ID "AT+DVID1123"
#define RF_CHNO "AT+RFC001"



volatile unsigned long lastEdge = micros();
volatile unsigned long period = 500000;
volatile unsigned long edges = 0;
unsigned long edgescount = 0;
// 5 readings per second.
uint16_t delayms = 200;
word angle = 0;
String comma = ",";
unsigned long lastLoop = millis();
unsigned long calltime = 0;
String outputLine;
String inputLine = "";

// use Sofrware serial for data so that we dont have to recolve conflicts sharing 
// the hardware uart with programing. (would have been nice to use the hardware uart, but its easy to blow the RF chipset when programming, 
// which then blows the pro mini power and io pins)
// SoftwareSerial rf(RF_RX_PIN, RF_TX_PIN);  // (Rx, Tx)
AltSoftSerial rf;


uint16_t readTwoBytes(int i2c_addr, int in_adr_hi, int in_adr_lo)
{
 
  /* Read Low Byte */
  Wire.beginTransmission(i2c_addr);
  Wire.write(in_adr_lo);
  Wire.endTransmission();
  Wire.requestFrom(i2c_addr, 1);
  while(Wire.available() == 0);
  int low = Wire.read();
 
  /* Read High Byte */  
  Wire.beginTransmission(i2c_addr);
  Wire.write(in_adr_hi);
  Wire.endTransmission();
  Wire.requestFrom(i2c_addr, 1);
  
  while(Wire.available() == 0);
  int high = Wire.read();
  if ( high < 0 || low < 0) {
    return 0;
  }
  return ((high&0xff) << 8) | (low&0xff);
}



uint8_t readOneByte(int i2c_addr, int in_adr)
{
  Wire.beginTransmission(i2c_addr);
  Wire.write(in_adr);
  Wire.endTransmission();
  Wire.requestFrom(i2c_addr, 1);
  while(Wire.available() == 0);
  int retVal = Wire.read();
  if ( retVal < 0 ) {
    return 0;
  }
  
  return retVal & 0xff;
}

uint16_t getRawAngle() {
  return readTwoBytes(AMS_5600_ADDRESS, AMS_5600_RAW_AND_HI, AMS_5600_RAW_AND_LO) & 0x0FFF;
}

uint16_t getAngle() {
  return readTwoBytes(AMS_5600_ADDRESS, 0x0e, 0x0f) & 0x0FFF;
}

uint16_t getMagnitue() {
  return readTwoBytes(AMS_5600_ADDRESS, 0x1b, 0x1c) & 0x0FFF;

}

uint8_t getAgc() {
  return readOneByte(AMS_5600_ADDRESS, 0x1a);

}

int getMagnetStrength()
{
  int magStatus;
  int retVal = 0;
  /*0 0 MD ML MH 0 0 0*/
  /* MD high = AGC minimum overflow, Magnet to strong */
  /* ML high = AGC Maximum overflow, magnet to weak*/ 
  /* MH high = magnet detected*/ 
  magStatus = readOneByte(AMS_5600_ADDRESS, AMS_5600_STAT);
  if(magStatus & 0x20)
  {
      retVal = 2; /*just right */
      if(magStatus & 0x10)
        retVal = 1; /*to weak */
      else if(magStatus & 0x08)
        retVal = 3; /*to strong */
  }
  
  return retVal;
}

/*
 * Counts the number of edges for debug
 * the period between edges for determining rpm
 * and the last edge for determining no rotation.
 * measuring the periods is more expensive than simply
 * counting the pulses however, where the rpm is low
 * this is required to ensure that the rpm measured 
 * doesnt correlate with the observation period.
 * 
 * In addition, if no interupt is called, then there is
 * no change to period on subsequent observations, which results
 * in a non zero measurement. Hence we expose the time of the last
 * edge so an observer can confirm pulses have been seen since the 
 * last measurement.
 */
void countPulseInterruptHandler() {
    static unsigned long newEdge = micros();
    lastEdge = newEdge;
    newEdge = micros();
    if (newEdge > lastEdge) {
      period = newEdge - lastEdge;
    }
    edges++; 
}

/**
 * Get the period and last edge from the volatile longs updated by the interrupt 
 * handler. If the last edge was before the previous observation
 * then no new edges have been seen and period must be at least 
 * the measured period and the time between the last edge and now.
 * 
 * Finally if the period is > 32s, then we assume its 32s
 */ 
unsigned long getPeriod() {
    static unsigned long prevCall = micros();
    unsigned long thisCall = micros();
    noInterrupts();
    unsigned long p = period;
    unsigned long le = lastEdge;
    edgescount = edges;
    interrupts();
    
    if ( le < prevCall ) {
      // no edge since the last get, increase the
      // period by the difference
      p = p+thisCall-le;
    }
    prevCall = thisCall;

    if ( p > 32000000) { //
      return 32000000;
    } else {
      return p;
    }
}

uint16_t crc_ccitt (const uint8_t * str, unsigned int length) {
  uint16_t crc = 0;
  for (unsigned int i = 0; i < length; i++) {
    uint8_t data = str[i];
    data ^= crc & 0xff;
    data ^= data << 4;
    crc = ((((uint16_t)data << 8) | (crc >> 8)) ^ (uint8_t)(data >> 4) 
                    ^ ((uint16_t)data << 3));
  }
  return crc;  
}

void dumpHex(const char * str) {
  for (unsigned int i = 0; i <strlen(str); i++)
  {
    Serial.print(str[i], HEX);//excludes NULL byte
  }
  Serial.print(":");
  Serial.println(strlen(str));
}


int expect(const char *cmd, const char *response) {
  for(int i = 0; i < 4; i++ ) {
    delay(500);
    while(rf.available()) {
      rf.read();
    }

    rf.println(cmd);
    delay(100);
    String res = rf.readStringUntil('\n');
    res.trim();
    if ( res.equals(response) ) {
      Serial.print(cmd);
      Serial.println(" OK");
      return 1;    
    } 
    Serial.println("Init Failed command:");
    Serial.println(cmd);
    Serial.println(res);
    dumpHex(res.c_str());
    dumpHex(response);
  }
  Serial.println("ERROR Retried 4 times and still failed");
  return 0;
}


void setupJDY40() {
  // enable AT command set
  digitalWrite(RF_DATA_EN_PIN, 0);
  // set RF send vaud to 9600
  //
  delay(1000);

  expect("AT+BAUD4","OK");
  expect(RF_ID,"OK"); // Wireless ID set to 1021
  expect(RF_DEV_ID,"OK"); // Device ID set to 1123
  expect(RF_CHNO,"OK"); // Channel 001
  expect("AT+POWE9","OK"); // Power 12db
  expect("AT+CLSSA0","OK"); // Serial transmission.
  // enable data communications
  digitalWrite(RF_DATA_EN_PIN, 1);
}








void setup(){
 pinMode(PULSE_PIN, INPUT_PULLUP);
 pinMode(RF_DATA_EN_PIN, OUTPUT);
 pinMode(RF_TX_PIN, OUTPUT);
 pinMode(RF_RX_PIN, INPUT_PULLUP);

 attachInterrupt(digitalPinToInterrupt(PULSE_PIN), countPulseInterruptHandler, FALLING);
 Serial.begin(38400); // control 
 rf.begin(9600);

 setupJDY40();


 Wire.begin();

#ifdef DEBUG_MODE
 String testing = "testing";
 Serial.println(crc_ccitt((const uint8_t *)testing.c_str(), testing.length()), HEX); 
#endif
 // BC35
}

int n = 0;

void loop(){
    digitalWrite(13, n%2);
    n++;

    delay(delayms);
    unsigned long now = millis();
    if (now > lastLoop && (now - lastLoop) > delayms) {
      calltime = now - lastLoop - delayms;
    }
    lastLoop = now;


    unsigned long period = getPeriod();
    float windSpeed = 0;
    if (period > 0 ) {
      windSpeed = (float)(1000000.0)/period;
    }

    int magnet = getMagnetStrength();
    if(magnet != 0) {
       angle = getRawAngle();
    }
#ifdef DEBUG_MODE
    int detected = 0;
    if(magnet != 0) {
       detected = 1;
    }
    int magnitude = getMagnitue();
    int agc = getAgc();
    outputLine = String(detected)+comma+
                 String(magnet)+comma+
                 String(agc)+comma+
                 String(magnitude)+comma+
                 String(angle)+comma+
                 String(period)+comma+
                 String(windSpeed,3)+comma+
                 String(now)+comma+
                 String(delayms)+comma+
                 String(edgescount)+comma+
                 String(calltime)+comma;
#else
    outputLine = String(magnet)+comma+
                 String(angle)+comma+
                 String(windSpeed,3)+comma;
#endif
    
    uint16_t checksum = crc_ccitt((const uint8_t *)outputLine.c_str(), outputLine.length());
    outputLine += String(checksum,HEX);
    rf.println(outputLine);

#ifdef DEBUG_MODE
    Serial.println(outputLine);
#endif
}


