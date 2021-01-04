#include "hall3144.h"

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


volatile unsigned long lastEdge = micros();
volatile unsigned long period = 500000;
volatile unsigned long edges = 0;
unsigned long edgescount = 0;

void Hall3144_countPulseInterruptHandler() {
    static unsigned long newEdge = micros();
    lastEdge = newEdge;
    newEdge = micros();
    if (newEdge > lastEdge) {
      period = newEdge - lastEdge;
    }
    edges++; 
}

Hall3144::Hall3144(int _pulsePin) {
  pulsePin = _pulsePin;
  pinMode(pulsePin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(pulsePin), Hall3144_countPulseInterruptHandler, FALLING);
}


/**
 * Get the period and last edge from the volatile longs updated by the interrupt 
 * handler. If the last edge was before the previous observation
 * then no new edges have been seen and period must be at least 
 * the measured period and the time between the last edge and now.
 * 
 * Finally if the period is > 32s, then we assume its 32s
 */ 
unsigned long Hall3144::getPeriod() {
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

unsigned long Hall3144::getEdgesCount() {
    return edgescount;
}
