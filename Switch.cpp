#include "Switch.h"

#include <inttypes.h>
#include "Arduino.h"


Switch * Switch::getInstance() {
     if(!p_instance)           
           p_instance = new Switch();
       return p_instance;
   }

void Switch::loop() {
  pinValue = digitalRead(swichPin);  // read input value HIGH or LOW
  if (pinValue == HIGH) {
    startPressing = millis(); // release time start
  }
}

void Switch::setup(int inPin) {
  swichPin = inPin;
  pinMode(swichPin, INPUT);    // declare pushbutton as input
}

Switch::SwitchValues Switch::getState() {
  if (pinValue == HIGH) {
    return Switch::OFF;
  }
  if (millis() - startPressing > LONG_PRESSING) {
    return Switch::LONGON;
  }
  return Switch::ON;
}

Switch::Switch() {
  swichPin = 0;
  startPressing = 0;
  pinValue = 0;
}

Switch* Switch::p_instance = 0;
