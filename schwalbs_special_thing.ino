#include <Adafruit_NeoTrellisM4.h>
#include "MIDIUSB.h"

#include "seq.h"
#include "basicMIDI.h"
#include "accel.h"
#include "pedalboard.h"
#include "pitch_shifter.h"

#define MIDI_CHANNEL     0  // default channel # is 0

Adafruit_NeoTrellisM4 trellis;

BasicMIDI mode1;
Seq mode2;
Pedalboard mode3;
Pitch_Shifter mode4;
Accel bends;

byte mode = 4;

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
  mode1.begin(&trellis);
  mode2.begin(&trellis);
  mode3.begin(&trellis);
  mode4.begin(&trellis);
  bends.begin(&trellis);

  mode4.restart();

}

void loop() {
  // put your main code here, to run repeatedly:
  trellis.tick();

  switch (mode){
        case 1:
          mode1.run();
          bends.run();
          break;
        case 2:
          mode2.run();
          bends.run();
          break;
        case 3:
          mode3.run();
          break;
        case 4:
          mode4.run();
          break;
  }
  
  midiEventPacket_t rx;
  do {
    rx = MidiUSB.read();
    if (rx.header != 0) {
      if(rx.header==0x0B){
        if (rx.byte2 <= 5){
          mode = rx.byte2;
          switch (mode){
            case 1:
              mode1.restart();
              break;
            case 2:
              mode2.restart();
              break;
            case 3:
              mode3.restart();
              break;
            case 4:
              mode4.restart();
              break;
          }
        } 
      }
    }
  } while (rx.header != 0);
}
