#ifndef pitch_shifter_h
#define pitch_shifter_h


#include <Arduino.h>
#include <Adafruit_NeoTrellisM4.h>
#include "buttons.h"

class Pitch_Shifter{
  public:
    Pitch_Shifter();
    void run();
    void begin(Adafruit_NeoTrellisM4 *x);
    void restart();
    
    Adafruit_NeoTrellisM4 *trellis;
};
#endif
