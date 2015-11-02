#include "DistanceMeter.h"
#include "LEDs.h"
#include "IR.h"
#include "Switch.h"

DistanceMeter * distanceMeter = new DistanceMeter();
LEDs * leds = new LEDs();
Switch * aSwitch = new Switch();

void setup() {
  // put your setup code here, to run once:
  Serial.begin (9600); 
  distanceMeter->setup(8 /*trig digital Pin*/, 9 /*echo digital Pin*/); 
  leds->setup(10); 
  aSwitch->setup(7);
}

Switch::SwitchValues lastSwitchState = Switch::OFF;

void loop() {
  // put your main code here, to run repeatedly:
  distanceMeter->lookAround();
  aSwitch->loop();
  boolean q = distanceMeter->isSomebodyNear();
  //Serial.println(q);
  if (q) {
    leds->fade(LEDs::MAX);
  }
  else {
    leds->fade(LEDs::OFF);
  }
  leds->loop();

  Switch::SwitchValues state = aSwitch->getState();
  if (state == Switch::ONNEW) {
      Serial.println("ON");
  }
  if (state == Switch::LONGONNEW) {
      Serial.println("LONGON");
  }
  
  lastSwitchState = state; //?
  
}


