#include "Switch.h"

#include <inttypes.h>
#include "Arduino.h"


Switch * Switch::getInstance() {
     if(!p_instance)           
           p_instance = new Switch();
       return p_instance;
   }

void Switch::loop() {
      
}

void Switch::setup() {

}


Switch::Switch() {
}

Switch* Switch::p_instance = 0;
