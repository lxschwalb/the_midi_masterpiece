#include "seq.h"

Seq::Seq(){
  root = 32;
}

void Seq::processNotes(int px){
  byte shift = note_memory[px];
  byte note;
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

  
  trellis->setPixelColor(last_px, colours[note_memory[last_px]]);  
  trellis->setPixelColor(px, 0xFFFFFF - colours[shift]);
  if(shift != 0){
    trellis->noteOn(note, 100);
  } 
}

void Seq::begin(Adafruit_NeoTrellisM4 *x, bool *interupt_flag){
  trellis = x;
  beat = 0;
  _interupt_flag = interupt_flag;
}

void Seq::restart(){
  beat=0;
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
  if(*_interupt_flag){
    *_interupt_flag = false;
    beat += 1;
    if(beat>7){
      beat = 0;
    }
    trellis->controlChange(123, 123);
    processNotes(beat);
    processNotes(beat+8);
    processNotes(beat+16);
    processNotes(beat+24);
    trellis->sendMIDI(); // send any pending MIDI messages
  }
  
  delay(10);
}
