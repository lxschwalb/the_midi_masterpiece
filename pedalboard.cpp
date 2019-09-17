#include "pedalboard.h"

Pedalboard *pedalboard;

Latch muff;
Latch quack;
Latch quack_drive;
Latch phaser;
Latch trem;
Latch dilay;
Latch reverb;
Latch stuck;
Toggle mute;
Toggle poweroff1;
Toggle poweroff2;

Var quack_peak;
Var phase_rate;
Var phase_depth;
Var phase_spread;
Var phase_res;
Var trem_rate;
Var delay_blend;
Var delay_fb;
Var reverb_shimmer;
Var reverb_decay;
Var reverb_mix;
Var reverb_ratio;


byte preset_locations[4] = {7, 15, 23, 31};
byte default_presets[4] = {0, 42, 85, 127};

Pedalboard::Pedalboard()
{
  pedalboard = this;
}

void Pedalboard::begin(Adafruit_NeoTrellisM4 *x){
  trellis = x;
  
  muff.begin(x, 0xFF0000, 0x110000, 24, 24, 0);
  quack.begin(x, 0x8800FF, 0x080011, 25, 25, 0);
  quack_drive.begin(x, 0xCC00CC, 0x110011, 26, 26, 0);
  quack_peak.begin(x, 0x8800FF, 27, 27, default_presets, preset_locations);
  mute.begin(x, 0x000000, 0xFF8888, 28, 28);
  poweroff1.begin(x, 0x000000, 0x8888FF, 29, 29);
  poweroff2.begin(x, 0x000000, 0x88FF88, 30, 30);
  
  phaser.begin(x, 0x00FF00, 0x001100, 16, 16, 0);
  phase_rate.begin(x, 0x00FF00, 17, 17, default_presets, preset_locations);
  phase_depth.begin(x, 0x00FF00, 18, 18, default_presets, preset_locations);
  phase_spread.begin(x, 0x00FF00, 19, 19, default_presets, preset_locations);
  phase_res.begin(x, 0x00FF00, 20, 20, default_presets, preset_locations);
  trem.begin(x, 0xFF3300, 0x110500, 21, 21, 0);
  trem_rate.begin(x, 0xFF3300, 22, 22, default_presets, preset_locations);

  
  dilay.begin(x, 0x0000FF, 0x000011, 8, 8, 0);
  delay_blend.begin(x, 0x0000FF, 9, 9, default_presets, preset_locations);
  delay_fb.begin(x, 0x0000FF, 10, 10, default_presets, preset_locations);

  
  reverb.begin(x, 0x00FF66, 0x001111, 0, 0, 0);
  reverb_shimmer.begin(x, 0x00FF66, 1, 1, default_presets, preset_locations);
  reverb_decay.begin(x, 0x00FF66, 2, 2, default_presets, preset_locations);
  reverb_mix.begin(x, 0x00FF66, 3, 3, default_presets, preset_locations);
  reverb_ratio.begin(x, 0x00FF66, 4, 4, default_presets, preset_locations);
  stuck.begin(x, 0x00FF22, 0x001108, 5, 5, 0);  
}

void Pedalboard::restart(){
  muff.set_colors();
  quack.set_colors();
  quack_drive.set_colors();
  mute.set_colors();
  poweroff1.set_colors();
  poweroff2.set_colors();
  
  phaser.set_colors();
  trem.set_colors();

  dilay.set_colors();
  
  reverb.set_colors();
  stuck.set_colors();  
}

void Pedalboard::run() {
  while (trellis->available()){
    keypadEvent e = trellis->read();
    int key = e.bit.KEY;

    // PROCESS BUTTON PRESSES
    if (e.bit.EVENT == KEY_JUST_PRESSED) {
      switch (key){
        case 0:
          reverb.pressed();
          break;
        case 1:
          reverb_shimmer.pressed();
          break;
        case 2:
          reverb_decay.pressed();
          break;
        case 3:
          reverb_mix.pressed();
          break;
        case 4:
          reverb_ratio.pressed();
          break;
        case 5:
          stuck.pressed();
          break;
        case 6:
          trellis->setPixelColor(6, 0xFFFFFF);
          break;
          
        case 8:
          dilay.pressed();
          break;
         case 9:
          delay_blend.pressed();
          break;
         case 10:
          delay_fb.pressed();
          break;

        case 16:
          phaser.pressed();
          break;
        case 17:
          phase_rate.pressed();
          break;
        case 18:
          phase_depth.pressed();
          break;
        case 19:
          phase_spread.pressed();
          break;
        case 20:
          phase_res.pressed();
          break;
        case 21:
          trem.pressed();
          break;
        case 22:
          trem_rate.pressed();
          break;
          
        case 24:
          muff.pressed();
          break; 
        case 25:
          quack.pressed();
          break;
        case 26:
          quack_drive.pressed();
          break; 
        case 27:
          quack_peak.pressed();
          break; 
        case 28:
          mute.pressed();
          break; 
        case 29:
          poweroff1.pressed();
          break; 
        case 30:
          poweroff2.pressed();
          break; 
      }
    }

    // RELEASE FOR TOGGLE BUTTONS
    else if (e.bit.EVENT == KEY_JUST_RELEASED) {
      switch (key){
        case 6:
          trellis->setPixelColor(6, 0x000000);
          break;
        case 28:
          mute.released();
          break;
        case 29:
          poweroff1.released();
          break;
        case 30:
          poweroff2.released();
          break;
      }
    }
  }
  if(!trellis->isPressed(6)){
    quack_peak.sendMIDI();
    phase_rate.sendMIDI();
    phase_depth.sendMIDI();
    phase_spread.sendMIDI();
    phase_res.sendMIDI();
    trem_rate.sendMIDI();
    delay_blend.sendMIDI();
    delay_fb.sendMIDI();
    reverb_shimmer.sendMIDI();
    reverb_decay.sendMIDI();
    reverb_mix.sendMIDI();
    reverb_ratio.sendMIDI();
    trellis->sendMIDI();
  }

  delay(10);
}
