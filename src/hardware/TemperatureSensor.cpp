#include "Arduino.h"
#include "TemperatureSensor.h"

TemperatureSensor::TemperatureSensor(int analogPin, int windowSize) : _averagingBuffer(windowSize) {
  _analogPin = analogPin; 
  init(); 
}

void TemperatureSensor::init() {
  float initialReading = readTemperatureCelcius(); 
  _averagingBuffer.fill(initialReading); 
}

float TemperatureSensor::getAverageTemperatureCelcius() {
  return _averagingBuffer.getAverage(); 
}

void TemperatureSensor::recordSample() {
  float temperatureCelcius = readTemperatureCelcius();
  _averagingBuffer.put(temperatureCelcius);
}

float TemperatureSensor::readTemperatureCelcius() {
  float voltage = readVoltage(); 
  // https://kookye.com/2019/08/28/arduino-lesson-tmp36/
  return (voltage - 0.5) * 100;
}

float TemperatureSensor::readVoltage() {
  int sensorInput = analogRead(_analogPin); 
  return (double) sensorInput / 1023 * 5; 
}
