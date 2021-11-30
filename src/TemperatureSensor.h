#ifndef TemperatureSensor_h
#define TemperatureSensor_h

#include "Arduino.h"

class TemperatureSensor {

  public:
    TemperatureSensor(int analogPin, float supplyVoltage); 
    float readTemperatureCelsius();

  private:
    int _analogPin; 
    float _supplyVoltage; 

    float readVoltage(); 
};

#endif
