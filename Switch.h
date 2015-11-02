#ifndef Switch_h
#define Switch_h
 
#include <inttypes.h>
#include "Arduino.h"


class Switch {
  
  public:
    
    enum SwitchValues {
      OFF = 0,
      ONNEW = 1,
      ON = 2,
      LONGONNEW = 3,
      LONGON = 4
    };
    
    Switch();
    void loop();
    void setup(int inPin);
    SwitchValues getState();
    
  private:
    int swichPin;
    SwitchValues currentState;
    unsigned long lastOff;
    unsigned long lastOn;
    const unsigned long TIME_INTERVAL = 3*1000L;
    const long LONG_PRESSING = 1000L;
    const long BOUNCE_REDUCTION = 50;
};

#endif
