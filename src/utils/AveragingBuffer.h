#ifndef AveragingBuffer_h
#define AveragingBuffer_h

#include "Arduino.h"

class AveragingBuffer {

  public:
    AveragingBuffer(int size); 
    ~AveragingBuffer(); 
    void fill(float value); 
    void put(float value); 
    float getAverage(); 

  private:
    float* _samples;
    int _bufferSize; 
    int _pos; 
};

#endif
