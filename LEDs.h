#ifndef LEDs_h
#define LEDs_h
 
#include <inttypes.h>
#include "Arduino.h"



class LEDs {
  
  public:
  
    enum LEDValues {
      MAX = 255,
      SHADOW = 64,
      OFF = 0
    };
    LEDs();    
    void setup(int pin);
    //void setLight(int value); // 0 - 255
    int getLight(); 
    void loop();
    void fade(int targetValue, long timeout); //0 for forever
    boolean timerIsActive();
    
  private:
  int ledPin;
  int currentValue;
  int runningValue;
  long timeout;
  bool goOff;
  unsigned long lightTimer;
  unsigned long lastFade;
  const int FADE_DELAY = 5;

};

#endif
