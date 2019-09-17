#ifndef pedalboard_h
#define pedalboard_h


#include <Arduino.h>
#include <Adafruit_NeoTrellisM4.h>
#include "accel.h"

class Pedalboard{
  public:
    Pedalboard();
    void run();
    void begin(Adafruit_NeoTrellisM4 *x);
    
    Adafruit_NeoTrellisM4 *trellis;

};

class Latch{
  public:
    Latch();
    void begin(Adafruit_NeoTrellisM4 *x, long int on_color, long int off_color, byte location, byte message, bool start_state);
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

#endif
