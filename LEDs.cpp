#include "LEDs.h"

#include <inttypes.h>
#include "Arduino.h" 

void LEDs::setup(int pin) {
  ledPin = pin;
  pinMode(ledPin, OUTPUT);
}

/*
void LEDs::setLight(int value) {
  if (value < 0) value = 0;
  if (value > 255) value = 255;
  if (currentValue != value) {
    currentValue = value;
    analogWrite(ledPin, value);
  }
  runningValue = value;
  lastFade = 0; //far far away
}
*/

void LEDs::fade(int targetValue, long timeout) {
  if (targetValue < 0) targetValue = 0;
  if (targetValue > 255) targetValue = 255;
  if (currentValue != targetValue) {
    currentValue = targetValue;
    lastFade = 0; //far far away
  }
  this->timeout = timeout*1000;
  lightTimer = millis();
  goOff = false;
  Serial.print("fade:");
  Serial.print(targetValue);
  Serial.print(",");
  Serial.println(timeout);
}

void LEDs::loop() {
  if (timeout > 0) {
    // process timeout
    if (millis() - lightTimer > timeout) {
      Serial.println("loop timeout");
      Serial.println(goOff);
      if (!goOff) {
        fade(currentValue / 3, 10);
        goOff = true;
      }
      else {
        fade(OFF,0);
      }
    }
  }
  if (runningValue != currentValue) {
    if (millis() - lastFade > FADE_DELAY) {
      if (runningValue < currentValue) {
        runningValue++;
      }
      if (runningValue > currentValue) {
        runningValue--;
      }
      analogWrite(ledPin, runningValue);
      lastFade = millis();
    }
  }
}

boolean LEDs::timerIsActive() {
  return (timeout > 0);
}

int LEDs::getLight() {
  return currentValue;
}

LEDs::LEDs() {
  currentValue = 0;
  runningValue = 0;
  ledPin = 0;
  lastFade = 0;
  timeout = 0;
  lightTimer = 0;
  goOff = false;
}


