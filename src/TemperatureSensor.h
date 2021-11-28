#ifndef TemperatureSensor_h
#define TemperatureSensor_h

#include "Arduino.h"

class TemperatureSensor {

  public:
    TemperatureSensor(int analogPin, int numSamplesToAverage); 
    float readTemperatureCelsius();

  private:
    int _analogPin; 

    float readVoltage(); 
};

#endif
