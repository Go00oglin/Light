#ifndef IR_h
#define IR_h
 
#include <inttypes.h>
#include "Arduino.h"


class IR {
  
  public:
    IR();
    boolean isSomebodyNear();
    void loop();
    void setup();
    
  private:
  const unsigned long TIME_INTERVAL = 3*60*1000L;
  unsigned long lastPresence = 0;
};

#endif
