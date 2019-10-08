#include "crazy_pitches.h"

Crazy_Pitches::Crazy_Pitches()
{
}

void Crazy_Pitches::begin(Adafruit_NeoTrellisM4 *x){
  trellis = x;
  
  shift.begin(x, shift_colors, shift_locations, 1, shift_presets, 20);
  cutoff.begin(x, cutoff_colors, cutoff_locations, 2, cutoff_presets, 6);
  muff.begin(x, 0xFF0000, 0x110000, 6, 6, 0);
  filt.begin(x, 0x00FF00, 0x001100, 5, 5, 0);
  dilay.begin(x, 0x0000FF, 0x000011, 7, 7, 0);
  AB.begin(x, 0xFFFF00, 0xFF0000, 30, 30, 0);
  stuck.begin(x, 0x0000FF, 0x000011, 31, 31, 0);
  mute.begin(x, 0x000000, 0xFFFFFF, 29, 29);
}

void Crazy_Pitches::restart(){
  shift.set_colors();
  cutoff.set_colors();
  muff.set_colors();
  filt.set_colors();
  dilay.set_colors();
  stuck.set_colors();
  mute.set_colors();
  AB.set_colors();
}

void Crazy_Pitches::run() {
  while (trellis->available()){
    keypadEvent e = trellis->read();
    int key = e.bit.KEY;

    // PROCESS BUTTON PRESSES
    if (e.bit.EVENT == KEY_JUST_PRESSED) {
        for(byte i=0; i<20; i++){
          if(key==shift_locations[i]){
            shift.pressed(i);
            break;
          }
        }
        for(byte i=0; i<6; i++){
          if(key==cutoff_locations[i]){
            cutoff.pressed(i);
            break;
          }
        }
        switch (key){
          case 6:
            muff.pressed();
            break;
          case 5:
            filt.pressed();
            break;
          case 7:
            dilay.pressed();
            break;
          case 31:
            stuck.pressed();
            break;
          case 29:
            mute.pressed();
            break;
          case 30:
            AB.pressed();
            break;

        }
      }
      else if (e.bit.EVENT == KEY_JUST_RELEASED){
        if(key==29){
          mute.released();
        }
      }
  }

  delay(10);
}
