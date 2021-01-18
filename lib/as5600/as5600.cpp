
#include "as5600.h"

#define VERBOSE_LN(x) if ( debugStream != NULL && verbose ) debugStream->println(x)
#define VERBOSE(x) if ( debugStream != NULL && verbose ) debugStream->print(x)
#define DEBUG_LN(x) if ( debugStream != NULL) debugStream->println(x)
#define DEBUG(x) if ( debugStream != NULL) debugStream->print(x)
#define AMS_5600_RAW_AND_HI 0x0c
#define AMS_5600_RAW_AND_LO 0x0d
#define AMS_5600_STAT 0x0b


As5600L::As5600L(int _i2c_addr) {
    debugStream = NULL;
    i2c_addr = _i2c_addr;
    verbose = false;
}

void As5600L::setDebugStream(Stream *_debugStream, bool _verbose) {
    verbose = _verbose;
    debugStream = _debugStream;
}

void As5600L::begin(void) {
  Wire.begin();
}


uint16_t As5600L::readTwoBytes(int in_adr_hi, int in_adr_lo)
{
  VERBOSE_LN(F("Read 2 bytes "));
 
  /* Read Low Byte */
  Wire.beginTransmission(i2c_addr);
  Wire.write(in_adr_lo);
  Wire.endTransmission();
  Wire.requestFrom(i2c_addr, 1);
  VERBOSE_LN(F("Written, waiting for read byte 1 "));
  int low = Wire.read();
 
  /* Read High Byte */  
  Wire.beginTransmission(i2c_addr);
  Wire.write(in_adr_hi);
  Wire.endTransmission();
  Wire.requestFrom(i2c_addr, 1);
  
  VERBOSE_LN(F("Written, waiting for read byte 2"));
  int high = Wire.read();
  if ( high < 0 || low < 0) {
    return 0;
  }
  return ((high&0xff) << 8) | (low&0xff);
}

/**
 *  * Output   0 .. success
 *          1 .. length to long for buffer
 *          2 .. address send, NACK received
 *          3 .. data send, NACK received
 *          4 .. other twi error (lost bus arbitration, bus error, ..)
 */
void As5600L::reportTransmission(uint8_t e) {
  switch(e) {
    case 0:
       VERBOSE_LN(F("Wire: sucess"));
       break;
    case 1:
       DEBUG_LN(F("Wire: length to long for buffer"));
       break;
    case 2:
       DEBUG_LN(F("Wire: address send, NACK received"));
       break;
    case 3:
       DEBUG_LN(F("Wire: data send, NACK received"));
       break;
    case 4:
       DEBUG_LN(F("Wire other twi error (lost bus arbitration, bus error, ..)"));
       break;
    default:
       DEBUG(F("Wire unknown error: "));
       DEBUG_LN(e);
       break;
  }
}


uint8_t As5600L::readOneByte(int in_adr)
{
  VERBOSE_LN(F("Read 1 byte "));
  for( int i = 0; i < 4; i++ ) {
    Wire.beginTransmission(i2c_addr);
    Wire.write(in_adr);
    VERBOSE(F("Write Error "));
    VERBOSE_LN(Wire.getWriteError());
    uint8_t e = Wire.endTransmission();
    reportTransmission(e);
    if ( e == 0 ) {
      break;
    } 
    delay(10);
  }

  Wire.requestFrom(i2c_addr, 1);
  VERBOSE_LN(F("Written, waiting for read "));
  int retVal = Wire.read();
  if ( retVal < 0 ) {
    return 0;
  }
  
  return retVal & 0xff;
}

uint16_t As5600L::getRawAngle() {
  return readTwoBytes(AMS_5600_RAW_AND_HI, AMS_5600_RAW_AND_LO) & 0x0FFF;
}

uint16_t As5600L::getAngle() {
  return As5600L::readTwoBytes(0x0e, 0x0f) & 0x0FFF;
}

uint16_t As5600L::getMagnitue() {
  return As5600L::readTwoBytes(0x1b, 0x1c) & 0x0FFF;

}

uint8_t As5600L::getAgc() {
  return readOneByte(0x1a);

}

uint8_t As5600L::getMagnetStrength()
{
  int magStatus;
  int retVal = 0;
  /*0 0 MD ML MH 0 0 0*/
  /* MD high = AGC minimum overflow, Magnet to strong */
  /* ML high = AGC Maximum overflow, magnet to weak*/ 
  /* MH high = magnet detected*/ 
  magStatus = readOneByte(AMS_5600_STAT);
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
