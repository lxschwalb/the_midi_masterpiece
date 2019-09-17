#include "seq.h"

Seq *seq;
int colours[] = {0x000000, 0xFF0000, 0x00FF00, 0x0000FF};
bool beatFlag = false;

Seq::Seq(){
  root = 32;
  seq = this;
}

void processNotes(int px){
  Adafruit_NeoTrellisM4 *trellis = seq->trellis;
  byte root= seq->root;
  byte shift = seq->note_memory[px];
  byte note = 0;
  int last_px = px-1;
  if (last_px==-1 || last_px==7 || last_px==15 || last_px==23){
    last_px+=8;
  }

  if(px<8){
    note = root+shift;
  }else if (px<16){
    note = root+shift+3;
  }else if (px<24){
    note = root+shift+6;    
  }else{
    note = root+shift+9;    
  }

  
  trellis->setPixelColor(last_px, colours[seq->note_memory[last_px]]);  
  trellis->setPixelColor(px, 0xFFFFFF - colours[shift]);
  if(shift != 0){
    trellis->noteOn(note, 100);
  } 
}

void newBeat(){
  beatFlag = true;
  seq->beat += 1;
  if(seq->beat>7){
    seq->beat = 0;
  }
}

void Seq::begin(Adafruit_NeoTrellisM4 *x){
  trellis = x;
  beat = 0;
  TC.startTimer(100000, newBeat);
}

void Seq::run() {
  
  while (trellis->available()){
    keypadEvent e = trellis->read();
    int butt = e.bit.KEY;

    if (e.bit.EVENT == KEY_JUST_PRESSED) {
      if(note_memory[butt]==0){
        note_memory[butt]=1;
      } else if(note_memory[butt]==1){
        note_memory[butt]=2;
      }else if(note_memory[butt]==2){
        note_memory[butt]=3;
      }else if(note_memory[butt]==3){
        note_memory[butt]=0;
      }
      trellis->setPixelColor(butt, colours[note_memory[butt]]);
    }
  }
  if(beatFlag){
    beatFlag = false;
    trellis->controlChange(123, 123);
    processNotes(beat);
    processNotes(beat+8);
    processNotes(beat+16);
    processNotes(beat+24);
    trellis->sendMIDI(); // send any pending MIDI messages
  }
  
  delay(10);
}
