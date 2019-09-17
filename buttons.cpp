#include "buttons.h"

Accel boogie;

Latch::Latch()
{
}

void Latch::begin(Adafruit_NeoTrellisM4 *x, long int on_color, long int off_color, byte location, byte message, bool start_state){
  _on_color = on_color;
  _off_color = off_color;
  _location = location;
  _message = message;
  _on = start_state;
  trellis = x;
}

void Latch::set_colors(){
  if(_on){
    trellis->setPixelColor(_location, _on_color);
  } else{
    trellis->setPixelColor(_location, _off_color);
  }
}

void Latch::pressed(){
  _on = !_on;
  if(_on){
    trellis->setPixelColor(_location, _on_color);
    trellis->controlChange(_message, 127);
  } else{
    trellis->setPixelColor(_location, _off_color);
    trellis->controlChange(_message, 0);
  }
}

Toggle::Toggle()
{
}

void Toggle::begin(Adafruit_NeoTrellisM4 *x, long int on_color, long int off_color, byte location, byte message){
  _on_color = on_color;
  _off_color = off_color;
  _location = location;
  _message = message;
  trellis = x;
}

void Toggle::set_colors(){
  trellis->setPixelColor(_location, _off_color);
}

void Toggle::pressed(){
  trellis->setPixelColor(_location, _on_color);
  trellis->controlChange(_message, 127);
}

void Toggle::released(){
  trellis->setPixelColor(_location, _off_color);
  trellis->controlChange(_message, 0);
}

Var::Var()
{
}

void Var::begin(Adafruit_NeoTrellisM4 *x, long int color, byte location, byte message, byte *presets, byte *preset_locations){
  _color = color;
  _location = location;
  _message = message;
  _presets = presets;
  _preset_locations = preset_locations;
  _mode=0;
  trellis = x;
  boogie.begin(trellis);
}

void Var::pressed(){
   switch (_mode){
        case 0:
          trellis->setPixelColor(_location, _color);
          _mode=1;
          break;
        case 1:
          trellis->setPixelColor(_location, 0xFFFFFF-_color);
          _mode=2;
          break;
        case 2:
          trellis->setPixelColor(_location, 0xFFFFFF);
          _mode=3;
          break;
        case 3:
          trellis->setPixelColor(_location, 0x000000);
          _mode=0;
          break;
      }
}

void Var::sendMIDI(){
   switch (_mode){
        case 0:
          break;
        case 1:
          trellis->controlChange(_message, boogie.yVal());
          break;
        case 2:
          trellis->controlChange(_message, boogie.xVal());
          break;
        case 3:
          if(trellis->isPressed(_preset_locations[0])){
            trellis->controlChange(_message, _presets[0]);
          } else if(trellis->isPressed(_preset_locations[1])){
            trellis->controlChange(_message, _presets[1]);
          } else if(trellis->isPressed(_preset_locations[2])){
            trellis->controlChange(_message, _presets[2]);
          }else if(trellis->isPressed(_preset_locations[3])){
            trellis->controlChange(_message, _presets[3]);
          }
          break;
      }
}

Multi::Multi()
{
}

void Multi::begin(Adafruit_NeoTrellisM4 *x, long int *colors, byte *locations, byte message, byte *presets, byte len){
  _colors = colors;
  _locations = locations;
  _message = message;
  _presets = presets;
  _len = len;
  _active=0;
  
  trellis = x;
}

void Multi::set_colors(){
  for(byte i=0; i<_len; i++){
    trellis->setPixelColor(_locations[i], _colors[i]);
  }
  trellis->setPixelColor(_locations[_active], 0xFFFFFF);
}

void Multi::pressed(byte number){
  trellis->setPixelColor(_locations[_active], _colors[_active]);
  _active=number;   
  trellis->setPixelColor(_locations[number], 0xFFFFFF);
  trellis->controlChange(_message, _presets[number]);
}
