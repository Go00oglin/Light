#include "DistanceMeter.h"
#include "LEDs.h"
#include "IR.h"
#include "Switch.h"


void setup() {
  // put your setup code here, to run once:
  Serial.begin (9600); 
  DistanceMeter::getInstance() -> setup(8 /*trig digital Pin*/, 9 /*echo digital Pin*/); 
  LEDs::getInstance() -> setup(10); 
  
}

void loop() {
  // put your main code here, to run repeatedly:
  DistanceMeter::getInstance() -> lookAround();
  boolean q = DistanceMeter::getInstance() -> isSomebodyNear();
  Serial.println(q);
  if (q) {
    LEDs::getInstance() -> fade(LEDs::MAX);
  }
  else {
    LEDs::getInstance() -> fade(LEDs::OFF);
  }
  LEDs::getInstance() -> loop();
  
}


