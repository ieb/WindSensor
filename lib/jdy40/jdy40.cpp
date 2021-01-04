#include "jdy40.h"



Jdy40::Jdy40(int dataEnablePin, uint16_t _baud, Stream *_jdy40Stream, Stream *_debugStream) {
    dataEnPin = dataEnablePin;
    bufferPos = 0;
    jdy40Stream = _jdy40Stream;
    debugStream = _debugStream;
    baud = _baud;
    pinMode(dataEnPin, OUTPUT);
}




void Jdy40::startConfig() {
  if ( !inConfig ) {
      digitalWrite(dataEnPin, 0);
      delay(500);
      inConfig = true;  
  }
}

void Jdy40::endConfig() {
  if ( inConfig ) {
      digitalWrite(dataEnPin, 0);   
      delay(500);
      inConfig = false;  
  }
}

void Jdy40::init() {
  setBaud(baud);
  expect("AT+CLSSA0","OK"); // Serial transmission.
  expect("AT+POWE9","OK"); // Power 12db
}


void Jdy40::setBaud(uint16_t baud) {
   startConfig();
   switch(baud) {
       case 1200: expect("AT+BAUD1","OK"); return;
       case 2400: expect("AT+BAUD2","OK"); return;
       case 4800: expect("AT+BAUD3","OK"); return;
       case 9600: expect("AT+BAUD4","OK"); return;
       case 14400: expect("AT+BAUD5","OK"); return;
       case 19200: expect("AT+BAUD6","OK"); return;
       default: expect("AT+BAUD4","OK"); return;
   }
}

void Jdy40::setRFID(const char*  rfid) {
  String cmd = String("AT+RFID") + String(rfid);
  startConfig();
  expect(cmd.c_str(),"OK"); // Wireless ID set to 1020
}
void Jdy40::setDeviceID(const char* dvid) {
  String cmd = String("AT+DVID") + String(dvid);
  startConfig();
  expect(cmd.c_str(),"OK"); // Wireless ID set to 1020
}
void Jdy40::setChannel(const char* chan) {
  String cmd = String("AT+RFC") + String(chan);
  startConfig();
  expect(cmd.c_str(),"OK"); // Wireless ID set to 1020
}

uint16_t Jdy40::crc_ccitt (const uint8_t * str, unsigned int length) {
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


int16_t Jdy40::checkCRC(const char *inputLine) {
  uint16_t len = strlen(inputLine);
  int lastComma = len;
  if ( len == 0 ) {
    return -1;
  }

  while( lastComma > 0 && inputLine[lastComma] != ',') lastComma--;
  if (lastComma == len-1 ) {
    return -1;
  }
  // check the crc, incuding the comma
  uint16_t crc_check = crc_ccitt((const uint8_t *)inputLine, lastComma); 
  uint16_t crc_in = strtoul(&inputLine[lastComma+1],NULL,16);
  if (crc_check == crc_in) {
    return lastComma;
  } else {
    return -1;
  }
}


uint16_t Jdy40::writeLine(const char *output) {
  endConfig();
  uint16_t len = strlen(output);
  uint16_t checksum = crc_ccitt((const uint8_t *)output, len);
  jdy40Stream->print(output);
  jdy40Stream->print(',');
  jdy40Stream->println(checksum,HEX);
  return checksum;
}


char * Jdy40::readLine() {
   endConfig();
  // Read lines from serial into buffer for processing.
  // 
  while(jdy40Stream->available() > 0) {
    char b = jdy40Stream->read();

    if ( b == '\n') {
      inputLine[bufferPos] = '\0';
      int16_t crcPos = checkCRC(inputLine);
      if ( crcPos >= 0 ) {
        inputLine[crcPos] = '\0';
        bufferPos = 0;
        return inputLine;
      } else {
        debugStream->print("CRC Error, rejected");
        debugStream->println(inputLine);
        // drop the line CRC invalid.
        bufferPos = 0;
        return NULL;
      }
    } else if ( bufferPos < READBUFFER_LEN-1 ) {
      inputLine[bufferPos] = b;
      bufferPos++;
    } else {
      // drop extra characters.
    }
  }
  return NULL;
}


int Jdy40::expect(const char *cmd, const char *response) {
  for(int i = 0; i < 4; i++) {
    delay(500);
    while(jdy40Stream->available()) {
      jdy40Stream->read();
    }

    jdy40Stream->println(cmd);
    delay(100);
    String res = jdy40Stream->readStringUntil('\n');
    res.trim();
    if ( res.equals(response) ) {
      debugStream->print(cmd);
      debugStream->println(" OK");
      return 1;    
    } 
    debugStream->println("Init Failed command:");
    debugStream->println(cmd);
    debugStream->println(res);
    dumpHex(res.c_str());
    dumpHex(response);
  }
  return 0;
}

void Jdy40::dumpHex(const char * str) {
  for (int i = 0; i<strlen(str); i++)
  {
    debugStream->print(str[i], HEX);//excludes NULL byte
  }
  debugStream->print(":");
  debugStream->println(strlen(str));
}
