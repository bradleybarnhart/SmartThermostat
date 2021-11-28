#include "src/TemperatureSensor.h"
#include "src/Led.h"
#include "src/ConfigStorageModule.h"

const int SAMPLES_PER_CYCLE = 30; 
const unsigned long MIN_SAMPLE_PERIOD_MILLISECONDS = 1000UL; 

unsigned long sampleCount; 
unsigned long lastSampleMillis; 

ConfigStorageModule storageModule; 

TemperatureSensor temperatureSensor1(A0, SAMPLES_PER_CYCLE); 
TemperatureSensor temperatureSensor2(A1, SAMPLES_PER_CYCLE); 
Led greenLed(13);
Led redLed(12); 

void setup() {
  Serial.begin(9600); 
  delay(5000); 
  sampleCount = 0; 
  lastSampleMillis = millis(); 
}

void loop() {
  if (millis() - lastSampleMillis < MIN_SAMPLE_PERIOD_MILLISECONDS) {
    delay(10); 
    return; 
  }
  lastSampleMillis = millis(); 

  if (sampleCount != 0 && sampleCount % SAMPLES_PER_CYCLE == 0) {
    float temperatureReading1 = temperatureSensor1.getAverageTemperatureCelsius(); 
    float temperatureReading2 = temperatureSensor2.getAverageTemperatureCelsius(); 
    printTemperatureReading(1, temperatureReading1); 
    printTemperatureReading(2, temperatureReading2); 

    float avgTemperatureReading = (temperatureReading1 + temperatureReading2) / 2; 
    updateLedStatus(avgTemperatureReading); 
  } 

  temperatureSensor1.recordSample(); 
  temperatureSensor2.recordSample(); 

  sampleCount++;
}

void printTemperatureReading(int sensorId, float temperatureCelsius) {
  Serial.print("Temperature (celsius) for sensor "); 
  Serial.print(sensorId); 
  Serial.print(" = "); 
  Serial.println(temperatureCelsius); 
}

void updateLedStatus(float temperatureCelsius) {
  float absoluteError = abs(temperatureCelsius - storageModule.getDaytimeTemperatureTargetCelsius()); 
  boolean statusOk = absoluteError <= storageModule.getTemperatureToleranceCelsius(); 
  greenLed.setStatus(statusOk); 
  redLed.setStatus(!statusOk); 
}