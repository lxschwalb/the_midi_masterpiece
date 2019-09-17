#ifndef seq_h
#define seq_h

#include <Arduino.h>
#include <Adafruit_NeoTrellisM4.h>
#include <SAMD51_InterruptTimer.h>

class Seq{
  public:
    Seq();
    void run();
    void begin(Adafruit_NeoTrellisM4 *x);
    Adafruit_NeoTrellisM4 *trellis;
    byte root;
    byte note_memory[32];
    int beat;  
};


#endif
