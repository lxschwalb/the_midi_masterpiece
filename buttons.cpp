#include "buttons.h"

Accel boogie;

long int Wheel(byte WheelPos, float b, Adafruit_NeoTrellisM4 *x) {
//  Adafruit_NeoTrellisM4 *trellis = basicMIDI->trellis;
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
    return x->Color((255-WheelPos*3)*b, 0, WheelPos*3*b);
  }
  if(WheelPos < 170) {
    WheelPos -= 85;
    return x->Color(0, WheelPos*3*b, (255-WheelPos*3)*b);
  }
  WheelPos -= 170;
  return x->Color(WheelPos*3*b, (255-WheelPos*3)*b, 0);
}

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

Knob::Knob()
{
}

void Knob::begin(Adafruit_NeoTrellisM4 *x, long int color, byte location, byte message, byte *presets, byte *preset_selector){
  _color = color;
  _location = location;
  _message = message;
  _presets = presets;
  _preset_selector = preset_selector;
  _mode=0;
  _val = 0;
  trellis = x;
  boogie.begin(trellis);
}

void Knob::pressed(){
  _mode += 1;
  if(_mode>3){  
          _mode=0;
  }
}

void Knob::sendMIDI(){
   switch (_mode){
        case 0:
          trellis->setPixelColor(_location, scale_color(_color, 10));
          break;
        case 1:
          _val = boogie.yVal();
          trellis->controlChange(_message, _val);
          trellis->setPixelColor(_location, scale_color(_color, _val));
          break;
        case 2:
          _val = boogie.xVal();
          trellis->controlChange(_message, _val);
          trellis->setPixelColor(_location, scale_color(0xFFFFFF-_color, _val));
          break;
        case 3:
          _val = _presets[*_preset_selector];
          trellis->setPixelColor(_location, scale_color(0xFFFFFF, _val));
          trellis->controlChange(_message, _val);
          break;
      }
}

long int Knob::scale_color(long int color, int den){
  int r = ((color >> 16) & 0xFF) *den/127.0;
  int g = ((color >> 8) & 0xFF) *den/127.0;
  int b = ((color) & 0xFF) *den/127.0;
  return trellis->Color(r, g, b);
}

MultiCC::MultiCC()
{
}

void MultiCC::begin(Adafruit_NeoTrellisM4 *x, long int *colors, byte *locations, byte message, byte *presets, byte len){
  _colors = colors;
  _locations = locations;
  _message = message;
  _presets = presets;
  _len = len;
  _active=0;
  
  trellis = x;
}

void MultiCC::set_colors(){
  for(byte i=0; i<_len; i++){
    trellis->setPixelColor(_locations[i], _colors[i]);
  }
  trellis->setPixelColor(_locations[_active], 0xFFFFFF);
}

void MultiCC::pressed(byte number){
  trellis->setPixelColor(_locations[_active], _colors[_active]);
  _active=number;   
  trellis->setPixelColor(_locations[number], 0xFFFFFF);
  trellis->controlChange(_message, _presets[number]);
}

Binary::Binary()
{
}

void Binary::begin(Adafruit_NeoTrellisM4 *x, long int color, byte *locations, byte len){
  _color = color;
  _locations = locations;
  _len = len;
  
  trellis = x;
}

void Binary::set_colors(){
  for(byte i=0; i<_len; i++){
    if(_bits[i]){
      trellis->setPixelColor(_locations[i], _color);
    }
  }
}

void Binary::pressed(byte number){
  _bits[number] = !_bits[number];
  if(_bits[number]){
    trellis->setPixelColor(_locations[number], _color);
  } else{
    trellis->setPixelColor(_locations[number], 0x000000);
  }
}

byte Binary::evaluate(){
  byte value = 0;
  byte pow_of_2[8] = {1, 2, 4, 8, 16, 32, 64, 128};
  for(byte i=0; i<_len; i++){
    if(_bits[i]){
      value += pow_of_2[i];
    }
  }
  return value;
}
