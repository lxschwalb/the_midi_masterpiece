#include "MIDIUSB.h"
#include "buttons.h"

#define MIDI_CHANNEL     0  // default channel # is 0

Adafruit_NeoTrellisM4 trellis;

byte root = 33; // lowest note is 33=A2
byte note_mapping[32] = {29, 30, 31, 15, 16, 17, 18, 19, 26, 27, 28, 10, 11, 12, 13, 14, 23, 24, 25, 5, 6, 7, 8, 9, 20, 21, 22, 0, 1, 2, 3, 4};  
byte note_colors[32] = {1, 0, 1, 1, 0, 1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 0, 1, 0, 1, 1, 0, 1, 1, 0};
byte color_speed = 1;
long int color_mod = 0x000000;
byte color_counter = 0;

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
}

void loop(){
  // put your main code here, to run repeatedly:
  trellis.tick();

  while (trellis.available())
  {
    keypadEvent e = trellis.read();
    int butt = e.bit.KEY;
    int key = note_mapping[butt];

    if (e.bit.EVENT == KEY_JUST_PRESSED)
    {
      trellis.noteOn(root+key, 64);
    }
    else if (e.bit.EVENT == KEY_JUST_RELEASED)
    {
      trellis.noteOff(root+key, 64);
    }
  }

  color_counter += color_speed;
  color_counter %= 255;
  color_mod = Wheel(color_counter, 1, &trellis);

  for (int i = 0; i <= 31; i++)
  {
    if(trellis.isPressed(i))
    {
      trellis.setPixelColor(i, color_mod);
    }
    else
    {
      trellis.setPixelColor(i, note_colors[i]*0x111111);
    }
  }

  trellis.sendMIDI();
  delay(10);
}
