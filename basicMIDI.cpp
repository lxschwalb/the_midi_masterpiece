#include "basicMIDI.h"

BasicMIDI *basicMIDI;

byte note_mapping[32] = {29, 30, 31, 15, 16, 17, 18, 19, 26, 27, 28, 10, 11, 12, 13, 14, 23, 24, 25, 5, 6, 7, 8, 9, 20, 21, 22, 0, 1, 2, 3, 4};  
byte   note_colors[32] = {1, 0, 1, 1, 0, 1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 0, 1, 0, 1, 1, 0, 1, 1, 0};
byte color_speed = 1;

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
// b is brightness. value between 0 and 1
uint32_t Wheel(byte WheelPos, float b) {
  Adafruit_NeoTrellisM4 *trellis = basicMIDI->trellis;
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
    return trellis->Color((255-WheelPos*3)*b, 0, WheelPos*3*b);
  }
  if(WheelPos < 170) {
    WheelPos -= 85;
    return trellis->Color(0, WheelPos*3*b, (255-WheelPos*3)*b);
  }
  WheelPos -= 170;
  return trellis->Color(WheelPos*3*b, (255-WheelPos*3)*b, 0);
}
 
BasicMIDI::BasicMIDI()
{
  
  root = 33;
  basicMIDI = this;
  
  color_mod = 0x000000;
  color_counter = 0;
}

void BasicMIDI::begin(Adafruit_NeoTrellisM4 *x){
  trellis = x;
}

void BasicMIDI::run() {
  while (trellis->available()){
    keypadEvent e = trellis->read();
    int butt = e.bit.KEY;
    int key = note_mapping[butt];

    if (e.bit.EVENT == KEY_JUST_PRESSED) {
      trellis->noteOn(root+key, 64);
    }
    else if (e.bit.EVENT == KEY_JUST_RELEASED) {
      trellis->noteOff(root+key, 64);
    }
  }

  if(color_counter < 255){
    color_counter+=color_speed;
  }
  else{
    color_counter = 0;
  }
  color_mod = Wheel(color_counter, 1);

  for (int i = 0; i <= 31; i++) {
    if(trellis->isPressed(i)){
      trellis->setPixelColor(i, color_mod);
    } else{
      trellis->setPixelColor(i, note_colors[i]*0x111111);
    }
  }
  trellis->sendMIDI();

  delay(10);
}
