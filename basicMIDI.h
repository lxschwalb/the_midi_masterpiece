#ifndef basicMIDI_h
#define basicMIDI_h


#include <Arduino.h>
#include <Adafruit_NeoTrellisM4.h>

class BasicMIDI{
  public:
    BasicMIDI();
    void run();
    void begin(Adafruit_NeoTrellisM4 *x);
    byte root;
    
    int color_mod, color_counter;
    Adafruit_NeoTrellisM4 *trellis;

};

#endif
