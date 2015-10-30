#ifndef Switch_h
#define Switch_h
 
#include <inttypes.h>
#include "Arduino.h"


class Switch {
  
  public:
    
    enum SwitchValues {
      OFF = 0,
      ON = 1,
      LONGON = 2
    };
    
    static Switch* getInstance();

    void loop();
    void setup(int inPin);
    SwitchValues getState();
    
  private:
  int swichPin;
  int pinValue;
  unsigned long startPressing;
  const unsigned long TIME_INTERVAL = 3*1000L;
  const long LONG_PRESSING = 1000L;
  static Switch* p_instance;
  Switch();
};

#endif
