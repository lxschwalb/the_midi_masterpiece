#ifndef game_of_life_h
#define game_of_life_h

#include "buttons.h"

class Cell{
  public:
    Cell();
    void begin(Cell *b0, Cell *b1, Cell *b2, Cell *b3, Cell *b4, Cell *b5, Cell *b6, Cell *b7);
    void find_next_state();
    
    bool alive;
    bool change_state;
    Cell *buddies[8];
};

class GameOfLife{
  public:
    GameOfLife();
    void run();
    void begin(Adafruit_NeoTrellisM4 *x, bool *interupt_flag);
    void restart();
    Adafruit_NeoTrellisM4 *trellis;
  private:
    bool *_interupt_flag;    
    Binary bins[8];
    byte bin_locations[8][4] = {{0, 8, 16, 24},{1, 9, 17, 25},{2, 10, 18, 26},{3, 11, 19, 27},{4, 12, 20, 28},{5, 13, 21, 29},{6, 14, 22, 30},{7, 15, 23, 31}};
    Cell cells[32];
};
#endif
