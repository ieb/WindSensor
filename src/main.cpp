
#include <Arduino.h>
#include <as5600.h>
#include <jdy40.h>
#include <hall3144.h>


#define DEBUG_MODE 1
#define VERBOSE_LN(x) 
#define VERBOSE(x) 
// #define VERBOSE_LN(x) Serial.println(x)
// #define VERBOSE(x) Serial.print(x)

// use Sofrware serial for data so that we dont have to recolve conflicts sharing 
// the hardware uart with programing. (would have been nice to use the hardware uart, but its easy to blow the RF chipset when programming, 
// which then blows the pro mini power and io pins)

#include <SoftwareSerial.h>  // http://arduino.cc/en/Reference/softwareSerial
#define RF_TX_PIN 4
#define RF_RX_PIN 5
#define RF_DATA_EN_PIN 6


#define PULSE_PIN 2











void blink(int times, uint16_t ms) {
    static int n = 0;
    for (int t = 0; t < times; t++) {
      digitalWrite(13, n%2);
      n++;
      delay(ms);
    }
}







As5600L * angleSensor;
Jdy40 * jdy40;
Hall3144 * pulseSensor;
SoftwareSerial rf(RF_RX_PIN, RF_TX_PIN);




void setup(){

  Serial.begin(38400); // control 

  rf.begin(9600); 
  jdy40 = new Jdy40(RF_DATA_EN_PIN, 9600, &rf, &Serial);
  jdy40->startConfig();
  jdy40->init();
  jdy40->setRFID("1021");
  jdy40->setDeviceID("1123");
  jdy40->setChannel("001");

  angleSensor = new As5600L(AMS_5600L_ADDRESS,&Serial,false);
  // the library only supports 1 hall device at present.
  pulseSensor = new Hall3144(PULSE_PIN);
}


void loop(){
    static uint16_t delayms = 200;
    static word angle = 0;
    static String comma = ",";
    static unsigned long lastLoop = millis();
    static unsigned long calltime = 0;

    blink(1,delayms);
    unsigned long now = millis();
    if (now > lastLoop && (now - lastLoop) > delayms) {
      calltime = now - lastLoop - delayms;
    }
    lastLoop = now;

    VERBOSE_LN("Get Period");
    // period is in micro seconds
    // windspeed is in pulses/second with a min of 1000000/32000000 ie 1 pulse every 32s or
    // 1 revolution every 64s.
    // max is the resolution of the micro second timer, which for a 8MHz pro mini is 8 us.
    // hence max speed is 1000000/8 or 125000 rps or 7.5M rpm.... 100Kn is going to be about 550 Hz
    // hence the smallest period will be about 2000.
    unsigned long period = pulseSensor->getPeriod();
    float windSpeed = 0;
    if (period > 0 ) {
      windSpeed = (float)(1000000.0)/period;
    }

    VERBOSE_LN("Get Magnet");
    int magnet = angleSensor->getMagnetStrength();
    VERBOSE_LN("Get Angle");
    if(magnet != 0) {
      // 0 - 4096 == 0-360 deg
       angle = angleSensor->getRawAngle();
    }
#ifdef DEBUG_MODE
    int detected = 0;
    if(magnet != 0) {
       detected = 1;
    }
    VERBOSE_LN("Get Magnitude");
    int magnitude = angleSensor->getMagnitue();
    VERBOSE_LN("Get Agc");
    int agc = angleSensor->getAgc();
    unsigned long edgescount = pulseSensor->getEdgesCount();

    String outputLine = String(detected)+comma+
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
    
    uint16_t checksum = jdy40->writeLine(outputLine.c_str());

#ifdef DEBUG_MODE
    static int header = 0;
    if (header == 0 ) {
      Serial.println("detected,magnet,agc,magnitude,angle,period,windSpeed,now,delayms,edgescount,calltime,checksum");
      header=20;
    }
    header--;
    Serial.print(outputLine);
    Serial.println(checksum,HEX);
#endif
}


