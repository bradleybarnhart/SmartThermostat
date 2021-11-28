#include "Arduino.h"
#include "TemperatureSensor.h"

TemperatureSensor::TemperatureSensor(int analogPin, int windowSize) : _averagingBuffer(windowSize) {
  _analogPin = analogPin; 
  init(); 
}

void TemperatureSensor::init() {
  float initialReading = readTemperatureCelsius(); 
  _averagingBuffer.fill(initialReading); 
}

float TemperatureSensor::getAverageTemperatureCelsius() {
  return _averagingBuffer.getAverage(); 
}

void TemperatureSensor::recordSample() {
  float temperatureCelsius = readTemperatureCelsius();
  _averagingBuffer.put(temperatureCelsius);
}

float TemperatureSensor::readTemperatureCelsius() {
  float voltage = readVoltage(); 
  // https://kookye.com/2019/08/28/arduino-lesson-tmp36/
  return (voltage - 0.5) * 100;
}

float TemperatureSensor::readVoltage() {
  int sensorInput = analogRead(_analogPin); 
  return (double) sensorInput / 1023 * 5; 
}
