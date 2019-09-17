#ifndef accel_h
#define accel_h

#include <Arduino.h>
#include <Adafruit_NeoTrellisM4.h>
#include <Adafruit_ADXL343.h>
#include <Adafruit_Sensor.h>


class Accel{
  public:
    Accel();
    void begin(Adafruit_NeoTrellisM4 *x);
    void run();
    byte xVal();
    byte yVal();
    Adafruit_NeoTrellisM4 *trellis;
    Adafruit_ADXL343 a = Adafruit_ADXL343(123, &Wire1);
    int xPos;
    int yPos;
    int prev_xPos;
    int prev_yPos;
    
};


#endif
