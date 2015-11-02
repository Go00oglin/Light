#include "LEDs.h"

#include <inttypes.h>
#include "Arduino.h" 

void LEDs::setup(int pin) {
  ledPin = pin;
  pinMode(ledPin, OUTPUT);
}

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

void LEDs::fade(int targetValue) {
  if (currentValue != targetValue) {
    currentValue = targetValue;
    lastFade = 0; //far far away
  }
}

void LEDs::loop() {
  if (runningValue == currentValue) {
    return;
  }
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


int LEDs::getLight() {
  return currentValue;
}

LEDs::LEDs() {
  currentValue = 0;
  runningValue = 0;
  ledPin = 0;
  lastFade = 0;
}


