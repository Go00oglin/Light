#ifndef IR_h
#define IR_h
 
#include <inttypes.h>
#include "Arduino.h"


class IR {
  
  public:
    IR();
    boolean motionDetected();
    void loop();
    void setup(int pin);
    void pause(long interval);
    
  private:
  const unsigned long TIME_CALIBRATION = 30*1000L; //30 sec
  int pirPin;
  unsigned int pauseExpirationTime;  
};

#endif
