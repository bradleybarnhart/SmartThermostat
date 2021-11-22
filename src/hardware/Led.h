#ifndef Led_h
#define Led_h

#include "Arduino.h"

class Led {

  public:
    Led(int digitalPin); 
    void setStatus(boolean status); 

  private:
    int _digitalPin; 
};

#endif