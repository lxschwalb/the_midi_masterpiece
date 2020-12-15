#include "MIDIUSB.h"
#include "buttons.h"

#define MIDI_CHANNEL     0  // default channel # is 0

Adafruit_NeoTrellisM4 trellis;

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
Toggle tap;

Knob quack_peak;
Knob phase_rate;
Knob phase_depth;
Knob phase_spread;
Knob phase_res;
Knob trem_rate;
Knob delay_blend;
Knob delay_fb;
Knob reverb_shimmer;
Knob reverb_decay;
Knob reverb_mix;
Knob reverb_ratio;

Binary bin;

byte preset_pointer = 0;
byte bin_locations[4] = {7, 15, 23, 31};
byte default_presets[16] = {0, 7, 15, 23, 31, 39, 47, 55, 64, 73, 82, 91, 100, 109, 118, 127};
byte reverb_presets[16] = {0, 9, 13, 21, 25, 28, 30, 34, 42, 59, 64, 70, 85, 98, 106, 127};

void setup(){
  Serial.begin(9600);
    
  trellis.begin();
  trellis.setBrightness(80);

  // USB MIDI messages sent over the micro B USB port
  Serial.println("Enabling MIDI on USB");
  trellis.enableUSBMIDI(true);
  trellis.setUSBMIDIchannel(MIDI_CHANNEL);
  // UART MIDI messages sent over the 4-pin STEMMA connector (3.3V logic)
  Serial.println("Enabling MIDI on UART");
  trellis.enableUARTMIDI(true);
  trellis.setUARTMIDIchannel(MIDI_CHANNEL);
  
  muff.begin(&trellis, 0xFF0000, 0x110000, 24, 24, 0);
  quack.begin(&trellis, 0x8800FF, 0x080011, 25, 25, 0);
  quack_drive.begin(&trellis, 0xCC00CC, 0x110011, 26, 26, 0);
  quack_peak.begin(&trellis, 0x8800FF, 27, 27, default_presets, &preset_pointer);
  mute.begin(&trellis, 0x000000, 0xFF8888, 28, 28);
  poweroff1.begin(&trellis, 0x000000, 0x8888FF, 29, 29);
  poweroff2.begin(&trellis, 0x000000, 0x88FF88, 30, 30);
  
  phaser.begin(&trellis, 0x00FF00, 0x001100, 16, 16, 0);
  phase_rate.begin(&trellis, 0x00FF00, 17, 17, default_presets, &preset_pointer);
  phase_depth.begin(&trellis, 0x00FF00, 18, 18, default_presets, &preset_pointer);
  phase_spread.begin(&trellis, 0x00FF00, 19, 19, default_presets, &preset_pointer);
  phase_res.begin(&trellis, 0x00FF00, 20, 20, default_presets, &preset_pointer);
  trem.begin(&trellis, 0xFF3300, 0x110500, 21, 21, 0);
  trem_rate.begin(&trellis, 0xFF3300, 22, 22, default_presets, &preset_pointer);

  
  dilay.begin(&trellis, 0x0000FF, 0x000011, 8, 8, 0);
  delay_blend.begin(&trellis, 0x0000FF, 9, 9, default_presets, &preset_pointer);
  delay_fb.begin(&trellis, 0x0000FF, 10, 10, default_presets, &preset_pointer);
  tap.begin(&trellis, 0xFFFF00, 0x000FF, 11, 11);

  
  reverb.begin(&trellis, 0x00FF66, 0x001111, 0, 0, 0);
  reverb_shimmer.begin(&trellis, 0x00FF66, 1, 1, default_presets, &preset_pointer);
  reverb_decay.begin(&trellis, 0x00FF66, 2, 2, default_presets, &preset_pointer);
  reverb_mix.begin(&trellis, 0x00FF66, 3, 3, default_presets, &preset_pointer);
  reverb_ratio.begin(&trellis, 0x00FF66, 4, 4, reverb_presets, &preset_pointer);
  stuck.begin(&trellis, 0x00FF22, 0x001108, 5, 5, 0);

  bin.begin(&trellis, 0xFFFFFF, bin_locations, 4);
}

void loop(){
  // put your main code here, to run repeatedly:
  trellis.tick();

  preset_pointer = bin.evaluate();

  while (trellis.available())
  {
    keypadEvent e = trellis.read();
    int key = e.bit.KEY;

    // PROCESS BUTTON PRESSES
    if (e.bit.EVENT == KEY_JUST_PRESSED)
    {
      switch (key)
      {
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
          trellis.setPixelColor(6, 0xFFFFFF);
          break;
        case 7:
          bin.pressed(0);
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
        case 11:
          tap.pressed();
          break;

          
        case 15:
          bin.pressed(1);
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
        case 23:
          bin.pressed(2);
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
        case 31:
          bin.pressed(3);
          break;
      }
    }

    // RELEASE FOR TOGGLE BUTTONS
    else if (e.bit.EVENT == KEY_JUST_RELEASED)
    {
      switch (key)
      {
        case 6:
          trellis.setPixelColor(6, 0x000000);
          break;
        case 11:
          tap.released();
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
  if (!trellis.isPressed(6))
  {
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
    trellis.sendMIDI();
  }

  delay(10);
}
