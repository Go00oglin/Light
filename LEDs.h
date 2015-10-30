#ifndef LEDs_h
#define LEDs_h
 
#include <inttypes.h>
#include "Arduino.h"



class LEDs {
  
  public:
  
    enum LEDValues {
      MAX = 255,
      HALF = 127,
      SHADOW = 64,
      OFF = 0
    };
    
    static LEDs* getInstance();
    void setup(int pin);
    void setLight(int value); // 0 - 255
    int getLight(); 
    void loop();
    void fade(int targetValue);
    
  private:
  int ledPin;
  static LEDs* p_instance;
  int currentValue;
  int runningValue;
  unsigned long lastFade;
  const int FADE_DELAY = 5;
  LEDs();
};

#endif
