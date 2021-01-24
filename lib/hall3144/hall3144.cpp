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
 * 
 * 
 * The device being used is a SS451A which is almost the same as a 3144, but operates
 * at 3v which should allow the sensor to run off a 3.7v LiPo with solar power and
 * in sleep mode in the future.
 * 
 * The current setup has 2 magnets diametrically apposed. Since each magnet is
 * slightly differnt strength the low pulse width varies between each magnet
 * which causes the time between pulses to toggle. The measured standard deviation of
 * the pulses is 0 measured by a scope. On that basis the mesurement mechanism needs to take account of this.
 * 
 * There are two approaches that could be used.
 * Average the pulses, or use 2 counters alternating on each pulse.
 * 
 */


volatile unsigned long lastEdge1 = micros();
volatile unsigned long lastEdge2 = micros();
volatile unsigned long period1 = 500000;
volatile unsigned long period2 = 500000;
volatile unsigned long edges = 0;
unsigned long edgescount = 0;

void Hall3144_countPulseInterruptHandler() {
    static unsigned long newEdge1 = micros();
    static unsigned long newEdge2 = micros();
    static uint8_t magnet_number = 0;
    if (magnet_number == 0) {
      magnet_number = 1;
      lastEdge1 = newEdge1;
      newEdge1 = micros();
      if ( newEdge1 > lastEdge1 ) {
        period1 = newEdge1 - lastEdge1;
      }
    } else {
      magnet_number = 0;
      lastEdge2 = newEdge2;
      newEdge2 = micros();
      if ( newEdge2 > lastEdge2 ) {
        period2 = newEdge2 - lastEdge2;
      }
    }
    edges++; 
}

Hall3144::Hall3144(uint8_t _pulsePin) {
  pulsePin = _pulsePin;
}

void Hall3144::begin() {
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
    // fetch the values out of voltile 
    // dont do any maths here to keep these operations as close
    // as possible together.
    unsigned long p1 = period1;
    unsigned long p2 = period2;
    unsigned long le1 = lastEdge1;
    unsigned long le2 = lastEdge2;
    edgescount = edges;


    
    if ( p1 > 64000000) p1 = 64000000;
    if ( p2 > 64000000) p2 = 64000000;
    // each period is for a full revolution of the magnet
    // hence period between magnets is sum/4.
    unsigned long p = (p2+p2)/4;
    unsigned long le = max(le1,le2);

    
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
