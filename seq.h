#ifndef seq_h
#define seq_h

#include <Adafruit_NeoTrellisM4.h>

class Seq{
  public:
    Seq();
    void run();
    void begin(Adafruit_NeoTrellisM4 *x, bool *interupt_flag);
    void restart();
    void processNotes(int px);
    Adafruit_NeoTrellisM4 *trellis;
  private:
    byte root;
    byte note_memory[32];
    int beat;
    bool *_interupt_flag;
    long int colours[4] = {0x000000, 0xFF0000, 0x00FF00, 0x0000FF};
};


#endif
