#include <SAMD51_InterruptTimer.h>
// #include "MIDIUSB.h"

#include "buttons.h"

#define MIDI_CHANNEL     0  // default channel # is 0

class Cell{
  public:
    Cell();
    void begin(Cell *b0, Cell *b1, Cell *b2, Cell *b3, Cell *b4, Cell *b5, Cell *b6, Cell *b7);
    void find_next_state();
    byte numBuddies();
    
    bool alive = false;
    bool change_state = false;
    Cell *buddies[8];
};

Cell::Cell(){
}

void Cell::begin(Cell *b0, Cell *b1, Cell *b2, Cell *b3, Cell *b4, Cell *b5, Cell *b6, Cell *b7){
  buddies[0]=b0;
  buddies[1]=b1;
  buddies[2]=b2;
  buddies[3]=b3;
  buddies[4]=b4;
  buddies[5]=b5;
  buddies[6]=b6;
  buddies[7]=b7;
}

byte Cell::numBuddies (){
  byte num_buddies = 0;

  for (byte i=0; i<8; i++)
  {
    if (buddies[i]->alive)
    {
      num_buddies++;
    }
  }

  return num_buddies;
}

void Cell::find_next_state(){
  byte num_buddies = numBuddies();  

  change_state=false;
  if (!alive)
  {
    if (num_buddies==3)
    {
      change_state=true;
    }
  }
  else if (alive)
  {
    if (num_buddies>3 || num_buddies<2)
    {
       change_state=true;
    }
  }
}

Adafruit_NeoTrellisM4 trellis;
Cell cells[32];

void isr(){
  for (byte i=0; i<32; i++)
  {
    cells[i].find_next_state();
  }
  
  for (byte i=0; i<32; i++)
  {
    if (cells[i].change_state)
    {
      cells[i].alive=!cells[i].alive;
    }

    if (cells[i].alive)
    {
      trellis.setPixelColor(i, 0xFF00FF);
    }
    else
    {
      trellis.setPixelColor(i, 0x000000);
    }
  }
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

  for(int i=0; i<32; i++)
  {
    int t=i+8;
    int tl=i+7;
    int tr=i+9;
    int r=i+1;
    int l=i-1;
    int b=i-8;
    int bl=i-9;
    int br=i-7;

    if (t>=32)
    {
      t-=32;
      tl-=32;
      tr-=32;
    }
    else if (b<=-1)
    {
      b+=32;
      bl+=32;
      br+=32;
    }

    if (r==8 || r==16 || r==24 || r==32)
    {
      r-=8;
      tr-=8;
      br-=8;
    }
    else if (l==-1 || l==7 || l==15 || l==23 )
    {
      l+=8;
      tl+=8;
      bl+=8;
    }
    
    cells[i].begin(&cells[t], &cells[tl], &cells[tr], &cells[l], &cells[r], &cells[b], &cells[bl], &cells[br]);
  }

  TC.startTimer(500000, isr);
}

void loop() {
  // put your main code here, to run repeatedly:
  trellis.tick();
  while (trellis.available())
  {
    keypadEvent e = trellis.read();
    int butt = e.bit.KEY;

    if (e.bit.EVENT == KEY_JUST_PRESSED)
    {
      cells[butt].alive=!cells[butt].alive;
      
      if (cells[butt].alive)
      {
        trellis.setPixelColor(butt, 0xFFFF00);
      }
      else
      {
        trellis.setPixelColor(butt, 0x000000);
      }
    }
  }
  
  // trellis.sendMIDI(); // send any pending MIDI messages
  delay(10);
}
