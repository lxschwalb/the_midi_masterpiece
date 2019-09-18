#include "pitch_shifter.h"

Pitch_Shifter *pitch_shifter;

Multi up;
Multi les;

Latch muff2;
Latch quack2;
Latch leslie;

Latch stuck2;
Toggle mute2;

long int c1 = 0xFF0055;
long int c2 = 0x5500FF;

long int up_colors[20] = {c1, c2, c1, c1, c2, c1, c2, c1, c1, c2, c1, c2, c1, c2, c1, c1, c2, c1, c2, c1};
byte up_locations[20] = {24, 25, 26, 27, 28, 16, 17, 18, 19, 20, 8, 9, 10, 11, 12, 0, 1, 2, 3, 4};
byte up_presets[20] = {0, 6, 12, 18, 20, 24, 30, 36, 42, 48, 54, 60, 66, 69, 72, 78, 84, 90, 96, 102};

long int les_colors[20] = {0x00FF00, 0x00CC33, 0x009966, 0x006699, 0x0033CC, 0x0000FF};
byte les_locations[20] = {13, 14, 15, 21, 22, 23};
byte les_presets[20] = {0, 25, 50, 75, 100, 125};

Pitch_Shifter::Pitch_Shifter()
{
}

void Pitch_Shifter::begin(Adafruit_NeoTrellisM4 *x){
  trellis = x;
  
  up.begin(x, up_colors, up_locations, 1, up_presets, 20);
  les.begin(x, les_colors, les_locations, 2, les_presets, 6);

  muff2.begin(x, 0xFF0000, 0x110000, 5, 5, 0);
  leslie.begin(x, 0x00AAAA, 0x001111, 6, 6, 0);
  quack2.begin(x, 0x8800FF, 0x080011, 7, 7, 0);
  
  stuck2.begin(x, 0x00FF22, 0x001108, 31, 31, 0);
  mute2.begin(x, 0x000000, 0xFF8888, 29, 29);
}

void Pitch_Shifter::restart(){
  up.set_colors();
  les.set_colors();
  muff2.set_colors();
  leslie.set_colors();
  quack2.set_colors();
  stuck2.set_colors();
  mute2.set_colors(); 
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
        for(byte i=0; i<6; i++){
          if(key==les_locations[i]){
            les.pressed(i);
            break;
          }
        }
        switch (key){
          case 5:
            muff2.pressed();
            break;
          case 6:
            leslie.pressed();
            break;
          case 7:
            quack2.pressed();
            break;
          case 31:
            stuck2.pressed();
            break;
          case 29:
            mute2.pressed();
            break;

        }
      }
      else if (e.bit.EVENT == KEY_JUST_RELEASED){
        if(key==29){
          mute2.released();
        }
      }
  }

  delay(10);
}
