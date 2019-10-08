#ifndef buttons_h
#define buttons_h

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

class Knob{
  public:
    Knob();
    void begin(Adafruit_NeoTrellisM4 *x, long int color, byte location, byte message, byte *presets, byte *preset_selector);
    void pressed();
    void sendMIDI();
    long int scale_color(long int color, int den);
    Adafruit_NeoTrellisM4 *trellis;
  private:
    long int _color;
    byte _location;
    byte _message;
    byte *_presets;
    byte *_preset_selector;
    byte _mode;
    byte _val;
};

class MultiCC{
  public:
    MultiCC();
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

class Binary{
  public:
    Binary();
    void begin(Adafruit_NeoTrellisM4 *x, long int color, byte *locations, byte len);
    void set_colors();
    void pressed(byte location);
    byte evaluate();
    Adafruit_NeoTrellisM4 *trellis;
  private:
    long int _color;
    byte *_locations;
    byte _len;
    bool _bits[8];
};

long int Wheel(byte WheelPos, float b, Adafruit_NeoTrellisM4 *x);
#endif
