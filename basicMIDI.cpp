#include "basicMIDI.h"

BasicMIDI::BasicMIDI()
{
  root = 33;  
  color_mod = 0x000000;
  color_counter = 0;
}

void BasicMIDI::begin(Adafruit_NeoTrellisM4 *x){
  trellis = x;
}

void BasicMIDI::restart(){
  trellis->controlChange(123, 123);
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
  color_mod = Wheel(color_counter, 1, trellis);

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
