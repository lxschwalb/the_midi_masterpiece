#include "pedalboard.h"

Pedalboard *pedalboard;
Accel boogie;

Latch muff;
//Latch boost;
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
  boogie.begin(trellis);
  
//  boost.begin(x, 0xFF8800, 0x110A00, 24, 24, 1);
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
  if(start_state){
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
