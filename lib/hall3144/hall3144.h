
#ifndef _HALL3144_H
#define _HALL3144_H

#include <Arduino.h>

class Hall3144 {

    public:
        Hall3144(uint8_t interrupPin=2);
        void begin(void);
        unsigned long getPeriod();
        unsigned long getEdgesCount();
    private:
        uint8_t pulsePin;

};


#endif

