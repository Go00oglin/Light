#include "IR.h"

#include <inttypes.h>
#include "Arduino.h"

boolean IR::motionDetected() {
  if (millis() > this->pauseExpirationTime) {
    return (digitalRead(this->pirPin) == HIGH);
  } else {
    return false;
  }
}

void IR::pause(long interval) {
  this->pauseExpirationTime = millis() + interval;
}

void IR::loop() {
}

void IR::setup(int pin) {
  this->pirPin = pin;
  pinMode(this->pirPin, INPUT);
  //give the sensor some time to calibrate
  pause(TIME_CALIBRATION);
}


IR::IR() {
  this->pirPin = 0;
  this->pauseExpirationTime = 0;
}


