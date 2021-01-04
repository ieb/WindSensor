
#ifndef _WINDSENSOR_H
#define _WINDSENSOR_H

#include <Arduino.h>
#define READBUFFER_LEN 1024

class Jdy40 {

    public:
        Jdy40(int dataEnablePin=4, uint16_t _baud=9600, Stream *_jdy40Stream=&Serial, Stream *_debugStream=&Serial);
        void startConfig();
        void endConfig();
        char *readLine();
        uint16_t writeLine(const char *output);
        void init();
        void setBaud(uint16_t baud);

        void setRFID(const char*  rfid);
        void setDeviceID(const char* dvid);
        void setChannel(const char* chan);
        int16_t checkCRC(const char *inputLine);


    private:
        void dumpHex(const char * str);
        int expect(const char *cmd, const char *response);
        uint16_t crc_ccitt (const uint8_t * str, unsigned int length);
        void setupJDY40();
        Stream * debugStream;
        Stream * jdy40Stream;
        int bufferPos;
        int dataEnPin;
        uint16_t baud;
        bool inConfig;
        char inputLine[READBUFFER_LEN];
};

#endif

