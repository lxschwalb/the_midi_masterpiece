#ifndef basicMIDI_h
#define basicMIDI_h

#include "buttons.h"

class BasicMIDI{
  public:
    BasicMIDI();
    void run();
    void begin(Adafruit_NeoTrellisM4 *x);
    void restart();
  private:
    byte root;
    long int color_mod;
    byte color_counter;
    Adafruit_NeoTrellisM4 *trellis;
    byte note_mapping[32] = {29, 30, 31, 15, 16, 17, 18, 19, 26, 27, 28, 10, 11, 12, 13, 14, 23, 24, 25, 5, 6, 7, 8, 9, 20, 21, 22, 0, 1, 2, 3, 4};  
    byte   note_colors[32] = {1, 0, 1, 1, 0, 1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 0, 1, 0, 1, 1, 0, 1, 1, 0};
    byte color_speed = 1;
};

#endif
