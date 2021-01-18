
#include <Arduino.h>
#include <as5600.h>
#include <jdy40.h>
#include <hall3144.h>


#define VERBOSE_LN(x) 
#define VERBOSE(x) 
//#define VERBOSE_LN(x) Serial.println(x)
//#define VERBOSE(x) Serial.print(x)

// use Sofrware serial for data so that we dont have to recolve conflicts sharing 
// the hardware uart with programing. (would have been nice to use the hardware uart, but its easy to blow the RF chipset when programming, 
// which then blows the pro mini power and io pins)

#include <SoftwareSerial.h>  // http://arduino.cc/en/Reference/softwareSerial
#define RF_TX_PIN 4
#define RF_RX_PIN 5
#define RF_DATA_EN_PIN 6


#define PULSE_PIN 2


#define COMMA ","
#define OUTPUT_FORMAT "%2d,%4u,%7.3f,"







void blink(int times, uint16_t ms) {
    static int n = 0;
    for (int t = 0; t < times; t++) {
      digitalWrite(13, n%2);
      n++;
      delay(ms);
    }
}







As5600L angleSensor(AMS_5600L_ADDRESS);
Jdy40 jdy40(RF_DATA_EN_PIN);
Hall3144 pulseSensor(PULSE_PIN);
SoftwareSerial rf(RF_RX_PIN, RF_TX_PIN);




void setup(){

  Serial.begin(38400); // control 

  Serial.println(F("WindSensor 1.0"));
  Serial.println(F("Baud: 9600, RFID:1012, DevID:1123, RFChannel:1"));
  rf.begin(9600); 

  jdy40.setDebug(&Serial);
  jdy40.begin(&rf, 9600);
  jdy40.startConfig();
  jdy40.init();
  jdy40.setRFID(1021);
  jdy40.setDeviceID(1123);
  jdy40.setChannel(1);
 
  angleSensor.setDebugStream(&Serial, false);
  angleSensor.begin();
  // the library only supports 1 hall device at present.
  pulseSensor.begin();
  Serial.println(F("Init Complte"));
}

char outputBuffer[20]; 

void loop(){
    static uint16_t delayms = 200;
    static uint16_t angle = 0;
    static unsigned long lastLoop = millis();
    static unsigned long calltime = 0;

    blink(1,delayms);
    unsigned long now = millis();
    if (now > lastLoop && (now - lastLoop) > delayms) {
      calltime = now - lastLoop - delayms;
    }
    lastLoop = now;

    VERBOSE_LN(F("Get Period"));
    // period is in micro seconds
    // windspeed is in pulses/second with a min of 1000000/32000000 ie 1 pulse every 32s or
    // 1 revolution every 64s.
    // max is the resolution of the micro second timer, which for a 8MHz pro mini is 8 us.
    // hence max speed is 1000000/8 or 125000 rps or 7.5M rpm.... 100Kn is going to be about 550 Hz
    // hence the smallest period will be about 2000.
    // Does this need to be smoothed here ?
    // I dont think so, we are recording the time period
    // between edges with the edges being generated by a 
    // physical shaft rotatiting. Provided noise of the sensor
    // is not an issue the standard deviation between measurements
    // will be low, and hence some form of moving average is unecessary.
    // as the inertia in the sensor is not zero.
    unsigned long period = pulseSensor.getPeriod();
    double windSpeed = 0;
    if (period > 0 ) {
      windSpeed = (double)(1000000.0)/period;
    }


    VERBOSE_LN(F("Get Magnet"));
    int magnet = angleSensor.getMagnetStrength();
    VERBOSE_LN(F("Get Angle"));
    if(magnet != 0) {
      // 0 - 4096 == 0-360 deg
      // again, inertia exists that means 5Hz measurements
      // dont need to be smoothed in the sensor itself.
       angle = angleSensor.getRawAngle();
    }
    // 01,4096,999.999,
    sprintf(outputBuffer,OUTPUT_FORMAT,
       magnet,
       angle,
       windSpeed);       
    
    uint16_t checksum = jdy40.writeLine(outputBuffer);

    if(Serial) {

      int detected = 0;
      if(magnet != 0) {
        detected = 1;
      }
      VERBOSE_LN(F("Get Magnitude"));
      int magnitude = angleSensor.getMagnitue();
      VERBOSE_LN(F("Get Agc"));
      int agc = angleSensor.getAgc();
      unsigned long edgescount = pulseSensor.getEdgesCount();
      static int header = 0;
      if (header == 0 ) {
        Serial.println(F("detected,magnet,agc,magnitude,angle,period,windSpeed,now,delayms,edgescount,calltime,rf_checksum"));
        header=20;
      }
      header--;
      Serial.print(detected);
      Serial.print(COMMA);
      Serial.print(magnet);
      Serial.print(COMMA);
      Serial.print(agc);
      Serial.print(COMMA);
      Serial.print(magnitude);
      Serial.print(COMMA);
      Serial.print(angle);
      Serial.print(COMMA);
      Serial.print(period);
      Serial.print(COMMA);
      Serial.print(windSpeed);
      Serial.print(COMMA);
      Serial.print(now);
      Serial.print(COMMA);
      Serial.print(delayms);
      Serial.print(COMMA);
      Serial.print(edgescount);
      Serial.print(COMMA);
      Serial.print(calltime);
      Serial.print(COMMA);
      Serial.println(checksum,HEX);
    }
}


