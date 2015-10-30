#ifndef Switch_h
#define Switch_h
 
#include <inttypes.h>
#include "Arduino.h"


class Switch {
  
  public:
    static Switch* getInstance();

    void loop();
    void setup();
    
  private:
  const unsigned long TIME_INTERVAL = 3*1000L;
  static Switch* p_instance;
  Switch();
};

#endif
