#include <Wire.h>
#include <Time.h>
#include <DS1307RTC.h>

#include "DistanceMeter.h"
#include "LEDs.h"
#include "IR.h"
#include "Switch.h"

/*
          +12V ---------- + LED STRIP        
          -GND       ---- - LED STRIP
               \   /
                | |
       +--------OUT---------+
       |                    |
       IR                   Distance
       |                    |
       |                    |
       -                    Switch
       |                    |
       |                    |
       +-----usb---power----+

       RJ-6            IR       Switch     Distance    
       +---------+
       | +-+  =====    -        -          GRD
     +-| | |  =====    DATA     DATA       ECHO
     +-| | |  =====    GND      GND        TRIG
       | +-+  =====    +5V      -          +5V
       +---------+   
*/

const int LED_TIMEOUT = 15;// 3 * 60; //sec

DistanceMeter * distanceMeter = new DistanceMeter();
LEDs * leds = new LEDs();
Switch * aSwitch = new Switch();
IR * ir = new IR(); // может быть, поставить два?

void setup() {
  // put your setup code here, to run once:
  Serial.begin (9600); 
  distanceMeter->setup(8 /*trig digital Pin*/, 9 /*echo digital Pin*/); 
  leds->setup(10); 
  aSwitch->setup(7);
  ir->setup(2);
}

Switch::SwitchValues lastSwitchState = Switch::OFF;

void loop() {
  // Test sensors
  distanceMeter->loop();
  aSwitch->loop();
  ir->loop();
  if (leds->getLight() == LEDs::OFF){
    if (ir->motionDetected()) {
      Serial.println("Movement");
      turnSwitchOn();
    }
    if (aSwitch->getState() == Switch::ONNEW) {
      Serial.println("Switch on");
      turnSwitchOn();
    }
  }
  else { // LEDs is ON
    if (aSwitch->getState() == Switch::LONGONNEW) {
        tone(12, 262, 200);
        Serial.println("Switch on forever");
        leds->fade(LEDs::MAX, 0);
    }
    else {
      if (leds->timerIsActive()) {
        // Prolong lihgting if somebody is inside
        if (distanceMeter->isSomebodyNear()) {
          turnSwitchOn();
          Serial.println("Near");
        }
        if (ir->motionDetected()) {
          turnSwitchOn();
          Serial.println("Motion");
        }
      }
    }
    if (aSwitch->getState() == Switch::ONNEW) {
      Serial.println("Switch off");
      ir->pause(5*1000L);
      leds->fade(LEDs::OFF, 0);
    }
  }
 
  // fade and countdown processing
  leds->loop();
}


void turnSwitchOn() {
  tmElements_t tm;
  boolean isNight = false;
  if (RTC.read(tm)) {
    if ((tm.Hour <= 6) || (tm.Hour >= 15)) {
      isNight = true;
    }
  }
  else {
    if (RTC.chipPresent()) {
      Serial.println("The DS1307 is stopped.  Please run the SetTime");
    } else {
      Serial.println("DS1307 read error!  Please check the circuitry.");
    }
  }
  if (isNight) {
    leds->fade(LEDs::SHADOW, LED_TIMEOUT);
  }
  else {
    leds->fade(LEDs::MAX, LED_TIMEOUT);
  } 
}

