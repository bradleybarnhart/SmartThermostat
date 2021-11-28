#include "Arduino.h"
#include "AveragingBuffer.h"

AveragingBuffer::AveragingBuffer(int size) {
  _bufferSize = size; 
  _samples = new float[_bufferSize](); 
  _pos = 0; 
}

void AveragingBuffer::fill(float value) {
  for (int i = 0; i < _bufferSize; i++) {
    _samples[i] = value; 
  }
  _pos = 0; 
}

void AveragingBuffer::put(float value) {
  _samples[_pos] = value; 
  _pos = ++_pos % _bufferSize; 
}

float AveragingBuffer::getAverage() {
  float sum = 0.0; 
  for (int i = 0; i < _bufferSize; i++) {
    sum += _samples[i];  
  }
  return sum / _bufferSize; 
}

AveragingBuffer::~AveragingBuffer() {
  delete[] _samples; 
}
