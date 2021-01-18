
#ifndef _AS5600_H
#define _AS5600_H

#include <Arduino.h>

#ifdef UNIT_TEST
class FakeWire {
    public:
      char read();
      void write(uint8_t reg);
      void beginTransmission(uint8_t address);
      uint8_t endTransmission();
      void requestFrom(uint8_t address, uint8_t reg);
      uint8_t available();
      void begin();
      uint8_t getWriteError();
};
FakeWire Wire;

#else
#include <Wire.h>
#endif

// the AS5600L (low power) responds on 0x40 not 0x36, see page 27 in the datasheet.
#define AMS_5600L_ADDRESS 0x40
#define AMS_5600_ADDRESS 0x36

class As5600L {

    public:
        As5600L(int _i2c_addr=0x40);
        void setDebugStream(Stream *_debugStream=&Serial, bool _verbose=false);
        void begin(void);
        uint16_t getRawAngle();
        uint16_t getAngle();
        uint16_t getMagnitue();
        uint8_t getAgc();
        uint8_t getMagnetStrength();
    private:
        uint16_t readTwoBytes( int in_adr_hi, int in_adr_lo);
        void reportTransmission(uint8_t e);
        uint8_t readOneByte(int in_adr);
        Stream * debugStream;
        int i2c_addr;
        bool verbose;
};

#endif