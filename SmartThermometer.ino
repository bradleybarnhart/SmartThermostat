#include "src/hardware/TemperatureSensor.h"
#include "src/hardware/Led.h"

const float TEMPERATURE_TARGET_CELCIUS = 21.0; 
const float TEMPERATURE_TOLERANCE_CELCIUS = 2.5; 

const int SAMPLES_PER_CYCLE = 60; 
const int MIN_SAMPLE_PERIOD_MILLISECONDS = 1000; 

unsigned long _sampleCounter; 

TemperatureSensor temperatureSensor1(A0, SAMPLES_PER_CYCLE); 
TemperatureSensor temperatureSensor2(A1, SAMPLES_PER_CYCLE); 
Led greenLed(13);
Led redLed(12); 

void setup() {
  Serial.begin(9600); 
  // perform important jobs immediately on first loop iteration
  _sampleCounter = SAMPLES_PER_CYCLE; 
}

void loop() {
  unsigned long startMillis = millis(); 

  temperatureSensor1.recordSample();  
  temperatureSensor2.recordSample(); 

  if (_sampleCounter == SAMPLES_PER_CYCLE) {
    float temperatureReading1 = temperatureSensor1.getAverageTemperatureCelcius(); 
    float temperatureReading2 = temperatureSensor2.getAverageTemperatureCelcius(); 
    printTemperatureReading(1, temperatureReading1); 
    printTemperatureReading(2, temperatureReading2); 

    float avgTemperatureReading = (temperatureReading1 + temperatureReading2) / 2; 
    updateLedStatus(avgTemperatureReading); 

    _sampleCounter = 0; 
  } else {
    _sampleCounter++; 
  }

  unsigned long stopMillis = millis(); 

  // delay if elapsed time < min sample period
  delay(max(0, MIN_SAMPLE_PERIOD_MILLISECONDS - (stopMillis - startMillis)));
}

void printTemperatureReading(int sensorId, float temperatureCelcius) {
  Serial.print("Temperature (celsius) for sensor "); 
  Serial.print(sensorId); 
  Serial.print(" = "); 
  Serial.println(temperatureCelcius); 
}

void updateLedStatus(float temperatureCelcius) {
  float absoluteError = abs(temperatureCelcius - TEMPERATURE_TARGET_CELCIUS); 
  boolean statusOk = absoluteError <= TEMPERATURE_TOLERANCE_CELCIUS; 
  greenLed.setStatus(statusOk); 
  redLed.setStatus(!statusOk); 
}