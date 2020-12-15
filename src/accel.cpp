#include "accel.h"

Accel *accel;

// floating point map
float ofMap(float value, float inputMin, float inputMax, float outputMin, float outputMax, bool clamp) {
    float outVal = ((value - inputMin) / (inputMax - inputMin) * (outputMax - outputMin) + outputMin);

    if (clamp) {
      if (outputMax < outputMin) {
        if (outVal < outputMax)  outVal = outputMax;
        else if (outVal > outputMin)  outVal = outputMin;
      } else {
        if (outVal > outputMax) outVal = outputMax;
        else if (outVal < outputMin)  outVal = outputMin;
      }
    }
    return outVal;
}

Accel::Accel(){
  accel = this;
}

void Accel::begin(Adafruit_NeoTrellisM4 *x){
  trellis = x;
  a.begin();
}

void Accel::run() {
  sensors_event_t event;
  a.getEvent(&event);


  yPos = ofMap(event.acceleration.y, 5.0, -10.0, 0, 255, true);
    
  if (yPos != prev_yPos) {
    trellis->controlChange(11, yPos);
    prev_yPos = yPos;
  }

  xPos = ofMap(event.acceleration.x, -10, 10.0, 0, 255, true);
  
  if (xPos != prev_xPos) {
    trellis->controlChange(10, xPos);
    prev_xPos = xPos;
  }
}

byte Accel::xVal() {
  sensors_event_t event;
  a.getEvent(&event);

  xPos = ofMap(event.acceleration.x, -10, 10.0, 0, 255, true);
  return xPos;
}

byte Accel::yVal() {
  sensors_event_t event;
  a.getEvent(&event);


  yPos = ofMap(event.acceleration.y, 5.0, -10.0, 0, 255, true);
  return yPos;
}
