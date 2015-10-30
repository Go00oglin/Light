#include "IR.h"

#include <inttypes.h>
#include "Arduino.h"


IR * IR::getInstance() {
     if(!p_instance)           
           p_instance = new IR();
       return p_instance;
   }


void IR::loop() {
}

void IR::setup() {
  
}


IR::IR() {
}

IR* IR::p_instance = 0;
