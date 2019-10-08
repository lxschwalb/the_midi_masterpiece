#ifndef pedalboard_h
#define pedalboard_h

#include "buttons.h"

class Pedalboard{
  public:
    Pedalboard();
    void run();
    void begin(Adafruit_NeoTrellisM4 *x);
    void restart();
    
    Adafruit_NeoTrellisM4 *trellis;

    private:
      Latch muff;
      Latch quack;
      Latch quack_drive;
      Latch phaser;
      Latch trem;
      Latch dilay;
      Latch reverb;
      Latch stuck;
      Toggle mute;
      Toggle poweroff1;
      Toggle poweroff2;
      Toggle tap;
      
      Knob quack_peak;
      Knob phase_rate;
      Knob phase_depth;
      Knob phase_spread;
      Knob phase_res;
      Knob trem_rate;
      Knob delay_blend;
      Knob delay_fb;
      Knob reverb_shimmer;
      Knob reverb_decay;
      Knob reverb_mix;
      Knob reverb_ratio;

      Binary bin;
      byte preset_pointer = 0;
      byte bin_locations[4] = {7, 15, 23, 31};
      byte default_presets[16] = {0, 7, 15, 23, 31, 39, 47, 55, 64, 73, 82, 91, 100, 109, 118, 127};
      byte reverb_presets[16] = {0, 9, 13, 21, 25, 28, 30, 34, 42, 59, 64, 70, 85, 98, 106, 127};
};
#endif
