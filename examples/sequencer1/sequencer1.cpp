#include <SAMD51_InterruptTimer.h>
#include "MIDIUSB.h"

#include "buttons.h"

#define MIDI_CHANNEL     0  // default channel # is 0

Adafruit_NeoTrellisM4 trellis;

Accel bends; //measures accelorometers
const byte root = 32; //lowest possible not is 32+1=33=A2
byte note_memory[32]; //holds the sate of all buttons
int beat = 0; //keeps track of beat
const long int colours[4] = {0x000000, 0xFF0000, 0x00FF00, 0x0000FF};

void processNotes(int px) {
  byte shift = note_memory[px];
  byte note;
  int last_px = px-1;

  if (last_px==-1 || last_px==7 || last_px==15 || last_px==23)
  {
    last_px+=8;
  }

  note = root + shift + (px/8)*3;
  
  trellis.setPixelColor(last_px, colours[note_memory[last_px]]);  
  trellis.setPixelColor(px, 0xFFFFFF - colours[shift]);
  if (shift != 0)
  {
    trellis.noteOn(note, 100);
  } 
}

void isr() {
  beat += 1;
  beat %= 8;
  trellis.controlChange(123, 123); // end all the notes of previous step
  processNotes(beat);
  processNotes(beat+8);
  processNotes(beat+16);
  processNotes(beat+24);
  trellis.sendMIDI(); // send any pending MIDI messages
}

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
  
  TC.startTimer(100000, isr);
}

void loop() {
  // put your main code here, to run repeatedly:
  trellis.tick();
  bends.run();

  while (trellis.available())
  {
    keypadEvent e = trellis.read();
    int butt = e.bit.KEY;

    if (e.bit.EVENT == KEY_JUST_PRESSED)
    {
      note_memory[butt] += 1;
      note_memory[butt] %= 4;
      trellis.setPixelColor(butt, colours[note_memory[butt]]);
    }
  }
  delay(10);
}
