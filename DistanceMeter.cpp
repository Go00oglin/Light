#include "DistanceMeter.h"

#include <inttypes.h>
#include "Arduino.h"


DistanceMeter * DistanceMeter::getInstance() {
     if(!p_instance)           
           p_instance = new DistanceMeter();
       return p_instance;
   }

boolean DistanceMeter::isSomebodyNear() {
    long currentsMillis = millis();
    if ((currentsMillis - lastPresence < TIME_INTERVAL) && (lastPresence > 0)) {
      return true;
    } else {
      return false;
    }
}

void DistanceMeter::lookAround() {
      if (millis() - lastLooking > LOOKING_DELAY) {
        int duration, cm;
        digitalWrite(trigPin, LOW);
        delayMicroseconds(2);
        digitalWrite(trigPin, HIGH);
        delayMicroseconds(10);
        digitalWrite(trigPin, LOW);
        duration = pulseIn(echoPin, HIGH);
        if (duration == 0) {
          // Probably, sensor error
        } else {
          cm = duration / 58;
          if (cm <= MIN_DISTANCE) {
            lastPresence = millis();
          }
        }
        lastLooking = millis();
      }
}

void DistanceMeter::setup(int trigPin, int echoPin) {
  this->trigPin = trigPin;
  this->echoPin = echoPin; 
  pinMode(this->trigPin, OUTPUT);
  pinMode(this->echoPin, INPUT); 
  lastLooking = millis();
}


DistanceMeter::DistanceMeter() {
  lastPresence = 0;
  lastLooking = 0;
}

DistanceMeter* DistanceMeter::p_instance = 0;
