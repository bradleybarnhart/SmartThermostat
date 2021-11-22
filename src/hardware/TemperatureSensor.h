#ifndef TemperatureSensor_h
#define TemperatureSensor_h

#include "Arduino.h"
#include "../utils/AveragingBuffer.h"

class TemperatureSensor {

  public:
    TemperatureSensor(int analogPin, int numSamplesToAverage); 
    void recordSample(); 
    float getAverageTemperatureCelcius(); 

  private:
    int _analogPin; 
    AveragingBuffer _averagingBuffer; 

    void init(); 
    float readVoltage(); 
    float readTemperatureCelcius(); 
};

#endif
