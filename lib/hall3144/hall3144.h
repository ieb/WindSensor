
#ifndef _HALL3144_H
#define _HALL3144_H

#include <Arduino.h>

class Hall3144 {

    public:
        Hall3144(int interrupPin);
        unsigned long getPeriod();
        unsigned long getEdgesCount();
    private:
        int pulsePin;

};


#endif

