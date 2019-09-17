#include <Adafruit_NeoTrellisM4.h>
#include "MIDIUSB.h"

#include "seq.h"
#include "basicMIDI.h"
#include "accel.h"
#include "pedalboard.h"

#define MIDI_CHANNEL     0  // default channel # is 0

Adafruit_NeoTrellisM4 trellis;

BasicMIDI mode1;
Seq mode2;
Pedalboard mode3;
Accel bends;

byte mode = 3;

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
  bends.begin(&trellis);

}

void loop() {
  // put your main code here, to run repeatedly:
  trellis.tick();
  if(mode == 1){
    mode1.run();
    bends.run();
  } else if (mode == 2){
    mode2.run();
    bends.run();
  } else if (mode == 3){
    mode3.run();
  }
  
  midiEventPacket_t rx;
  do {
    rx = MidiUSB.read();
    if (rx.header != 0) {
      if(rx.header==0x0B){
        if (rx.byte2 <= 3){
          mode = rx.byte2;
        } 
      }
    }
  } while (rx.header != 0);
}
