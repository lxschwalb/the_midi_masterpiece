#ifndef buttons_h
#define buttons_h


#include <Arduino.h>
#include <Adafruit_NeoTrellisM4.h>
#include "accel.h"

class Latch{
  public:
    Latch();
    void begin(Adafruit_NeoTrellisM4 *x, long int on_color, long int off_color, byte location, byte message, bool start_state);
    void set_colors();
    void pressed();
    Adafruit_NeoTrellisM4 *trellis;
  private:
    long int _on_color;
    long int _off_color;
    byte _location;
    byte _message;
    bool _on;
};

class Toggle{
  public:
    Toggle();
    void begin(Adafruit_NeoTrellisM4 *x, long int on_color, long int off_color, byte location, byte message);
    void set_colors();
    void pressed();
    void released();
    Adafruit_NeoTrellisM4 *trellis;
  private:
    long int _on_color;
    long int _off_color;
    byte _location;
    byte _message;
};

class Var{
  public:
    Var();
    void begin(Adafruit_NeoTrellisM4 *x, long int color, byte location, byte message, byte *presets, byte *preset_locations);
    void pressed();
    void sendMIDI();
    Adafruit_NeoTrellisM4 *trellis;
  private:
    long int _color;
    byte _location;
    byte _message;
    byte *_presets;
    byte *_preset_locations;
    byte _mode;
};

class Multi{
  public:
    Multi();
    void begin(Adafruit_NeoTrellisM4 *x, long int *colors, byte *locations, byte message, byte *presets, byte len);
    void set_colors();
    void pressed(byte location);
    Adafruit_NeoTrellisM4 *trellis;
  private:
    long int *_colors;
    byte *_locations;
    byte _message;
    byte *_presets;
    byte _len;
    byte _active;
};

#endif
