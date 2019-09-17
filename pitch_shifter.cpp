#include "pitch_shifter.h"

Pitch_Shifter *pitch_shifter;

Multi up;
Multi down;

long int red = 0xFF3300;
long int blue = 0x00FFAA;

long int up_colors[20] = {red, 0, red, red, 0, red, 0, red, red, 0, red, 0, red, 0, red, red, 0, red, 0, red};
byte up_locations[20] = {24, 25, 26, 27, 28, 16, 17, 18, 19, 20, 8, 9, 10, 11, 12, 0, 1, 2, 3, 4};
byte up_presets[20] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19};

long int down_colors[12] = {0, blue, 0, blue, blue, 0, blue, 0, blue, blue, 0, blue};
byte down_locations[12] = {7, 6, 5, 15, 14, 13, 23, 22, 21, 31, 30, 29};
byte down_presets[12] = {11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0};

Pitch_Shifter::Pitch_Shifter()
{
  pitch_shifter = this;
}

void Pitch_Shifter::begin(Adafruit_NeoTrellisM4 *x){
  trellis = x;
  
  up.begin(x, up_colors, up_locations, 1, up_presets, 20); 
  down.begin(x, down_colors, down_locations, 2, down_presets, 12); 
}

void Pitch_Shifter::restart(){
  up.set_colors(); 
  down.set_colors(); 
}

void Pitch_Shifter::run() {
  while (trellis->available()){
    keypadEvent e = trellis->read();
    int key = e.bit.KEY;

    // PROCESS BUTTON PRESSES
    if (e.bit.EVENT == KEY_JUST_PRESSED) {
      for(byte i=0; i<20; i++){
        if(key==up_locations[i]){
          up.pressed(i);
          break;
        }
      }
      for(byte i=0; i<12; i++){
        if(key==down_locations[i]){
          down.pressed(i);
          break;
        }
      }
    }
  }

  delay(10);
}
