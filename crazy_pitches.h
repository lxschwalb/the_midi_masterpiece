#ifndef crazy_pitches_h
#define crazy_pitches_h

#include "buttons.h"

class Crazy_Pitches{
  public:
    Crazy_Pitches();
    void run();
    void begin(Adafruit_NeoTrellisM4 *x);
    void restart();
    
    Adafruit_NeoTrellisM4 *trellis;
  private:
    MultiCC shift;
    MultiCC cutoff;
    Latch muff;
    Latch dilay;
    Latch filt;
    Latch AB;
    Latch stuck;
    Toggle mute;
    
    long int c1 = 0xFF0088;
    long int c2 = 0x3300FF;
    
    long int shift_colors[20] = {c1, c2, c1, c1, c2, c1, c2, c1, c1, c2, c1, c2, c1, c2, c1, c1, c2, c1, c2, c1};
    byte shift_locations[20] = {24, 25, 26, 27, 28, 16, 17, 18, 19, 20, 8, 9, 10, 11, 12, 0, 1, 2, 3, 4};
    byte shift_presets[20] = {0, 6, 12, 18, 20, 24, 30, 36, 42, 48, 54, 60, 66, 69, 72, 78, 84, 90, 96, 102};
    
    long int cutoff_colors[20] = {0x00FF00, 0x00FF00, 0x00FF00, 0x00FF00, 0x00FF00, 0x00FF00};
    byte cutoff_locations[20] = {13, 14, 15, 21, 22, 23};
    byte cutoff_presets[20] = {0, 25, 50, 75, 100, 125};

};
#endif
