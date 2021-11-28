#ifndef TemperatureSensor_h
#define TemperatureSensor_h

#include "Arduino.h"
#include "AveragingBuffer.h"

class TemperatureSensor {

  public:
    TemperatureSensor(int analogPin, int numSamplesToAverage); 
    void recordSample(); 
    float getAverageTemperatureCelsius(); 

  private:
    int _analogPin; 
    AveragingBuffer _averagingBuffer; 

    void init(); 
    float readVoltage(); 
    float readTemperatureCelsius(); 
};

#endif