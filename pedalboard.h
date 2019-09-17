#ifndef pedalboard_h
#define pedalboard_h


#include <Arduino.h>
#include <Adafruit_NeoTrellisM4.h>
#include "buttons.h"

class Pedalboard{
  public:
    Pedalboard();
    void run();
    void begin(Adafruit_NeoTrellisM4 *x);
    void restart();
    
    Adafruit_NeoTrellisM4 *trellis;
};
#endif
