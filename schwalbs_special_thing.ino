#include <SAMD51_InterruptTimer.h>
#include "MIDIUSB.h"

#include "seq.h"
#include "basicMIDI.h"
#include "pedalboard.h"
#include "crazy_pitches.h"
#include "game_of_life.h"

#define MIDI_CHANNEL     0  // default channel # is 0

Adafruit_NeoTrellisM4 trellis;

GameOfLife mode0;
BasicMIDI mode1;
Seq mode2;
Pedalboard mode3;
Crazy_Pitches mode4;
Accel bends;

byte mode = 0;
bool interupt_flag = false;

void set_interrupt_flag(){
  interupt_flag = true;
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
  
  mode0.begin(&trellis, &interupt_flag);
  mode1.begin(&trellis);
  mode2.begin(&trellis, &interupt_flag);
  mode3.begin(&trellis);
  mode4.begin(&trellis);
  bends.begin(&trellis);

  mode0.restart();


  
  TC.startTimer(1000000, set_interrupt_flag);
}

void loop() {
  // put your main code here, to run repeatedly:
  trellis.tick();

  switch (mode){
        case 0:
          mode0.run();
          break;
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
            case 0:
              mode0.restart();
              break;
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
