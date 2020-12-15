#include "MIDIUSB.h"
#include "buttons.h"

#define MIDI_CHANNEL     0  // default channel # is 0

Adafruit_NeoTrellisM4 trellis;

MultiCC shift;
MultiCC cutoff;
Latch muff;
Latch dilay;
Latch filt;
Latch AB;
Latch stuck;
Toggle mute;

long int c1 = 0xFF0088;
long int c2 = 0x3300FF;

long int shift_colors[20] = {c1, c2, c1, c1, c2, c1, c2, c1, c1, c2, c1, c2, c1, c2, c1, c1, c2, c1, c2, c1};
byte shift_locations[20] = {24, 25, 26, 27, 28, 16, 17, 18, 19, 20, 8, 9, 10, 11, 12, 0, 1, 2, 3, 4};
byte shift_presets[20] = {0, 6, 12, 18, 20, 24, 30, 36, 42, 48, 54, 60, 66, 69, 72, 78, 84, 90, 96, 102};

long int cutoff_colors[20] = {0x00FF00, 0x00FF00, 0x00FF00, 0x00FF00, 0x00FF00, 0x00FF00};
byte cutoff_locations[20] = {13, 14, 15, 21, 22, 23};
byte cutoff_presets[20] = {0, 25, 50, 75, 100, 125};


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

  shift.begin(&trellis, shift_colors, shift_locations, 1, shift_presets, 20);
  cutoff.begin(&trellis, cutoff_colors, cutoff_locations, 2, cutoff_presets, 6);
  muff.begin(&trellis, 0xFF0000, 0x110000, 6, 6, 0);
  filt.begin(&trellis, 0x00FF00, 0x001100, 5, 5, 0);
  dilay.begin(&trellis, 0x0000FF, 0x000011, 7, 7, 0);
  AB.begin(&trellis, 0xFFFF00, 0xFF0000, 30, 30, 0);
  stuck.begin(&trellis, 0x0000FF, 0x000011, 31, 31, 0);
  mute.begin(&trellis, 0x000000, 0xFFFFFF, 29, 29);
}

void loop() {
  // put your main code here, to run repeatedly:
  trellis.tick();

   while (trellis.available())
   {
    keypadEvent e = trellis.read();
    int key = e.bit.KEY;

    // PROCESS BUTTON PRESSES
    if (e.bit.EVENT == KEY_JUST_PRESSED)
    {
      for(byte i=0; i<20; i++)
      {
        if(key==shift_locations[i])
        {
          shift.pressed(i);
          break;
        }
      }

      for(byte i=0; i<6; i++)
      {
        if(key==cutoff_locations[i])
        {
          cutoff.pressed(i);
          break;
        }
      }

      switch (key)
      {
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
    else if (e.bit.EVENT == KEY_JUST_RELEASED)
    {
      if(key==29)
      {
        mute.released();
      }
    }
  }

  delay(10);
}
