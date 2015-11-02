#include "Switch.h"

#include <inttypes.h>
#include "Arduino.h"

void Switch::setup(int inPin) {
  swichPin = inPin;
  pinMode(swichPin, INPUT);    // declare pushbutton as input
}

void Switch::loop() {
  int pinValue = digitalRead(swichPin);  // read input value HIGH or LOW
  if (pinValue == HIGH) { //OFF
    if (millis() - lastOn > BOUNCE_REDUCTION) {
      currentState = Switch::OFF;
      lastOff = millis(); // release time start
    }
  } else {
    if (millis() - lastOff > LONG_PRESSING) {
      if (currentState == ON) {
        currentState = LONGONNEW;
      }
      else {
        currentState = LONGON;
      }
    }
    else {
      if (currentState == OFF) {
        currentState = ONNEW;
      }
      else {
        currentState = ON;
      }
    }
    lastOn = millis();
  }
}

Switch::SwitchValues Switch::getState() {
  return currentState;
}

Switch::Switch() {
  swichPin = 0;
  lastOff = 0;
  lastOn = 0;
  currentState = OFF;
}


