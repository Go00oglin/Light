#ifndef DistanceMeter_h
#define DistanceMeter_h
 
#include <inttypes.h>
#include "Arduino.h"


class DistanceMeter {
  
  public:
    static DistanceMeter* getInstance();

    boolean isSomebodyNear();
    void lookAround();
    void setup(int trigPin, int echoPin);
    
  private:
  const int MIN_DISTANCE = 50;
  const unsigned long TIME_INTERVAL = 3*1000L;
  const int LOOKING_DELAY = 100; // millisecons. Delay between looking around
  int trigPin;
  int echoPin;
  unsigned long lastPresence = 0;
  unsigned long lastLooking = 0;
  static DistanceMeter* p_instance;
  DistanceMeter();
};

#endif
