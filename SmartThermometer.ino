#include "src/TemperatureSensor.h"
#include "src/Led.h"
#include "src/ConfigStorageModule.h"

const int SAMPLES_PER_CYCLE = 30; 
const unsigned long MIN_SAMPLE_PERIOD_MILLISECONDS = 1000UL;

unsigned long sampleCount; 
unsigned long lastSampleMillis; 

ConfigStorageModule configStorageModule; 

const int NUM_TEMPERATURE_SENSORS = 2; 
TemperatureSensor temperatureSensors[] = {
  TemperatureSensor(A0, SAMPLES_PER_CYCLE), 
  TemperatureSensor(A1, SAMPLES_PER_CYCLE)
}; 
float temperatureSensorReadings[NUM_TEMPERATURE_SENSORS][SAMPLES_PER_CYCLE]; 

Led greenLed(13);
Led redLed(12); 

void setup() {
  Serial.begin(9600);
  sampleCount = 0;
  lastSampleMillis = millis();
}

void loop() {
  if (millis() - lastSampleMillis < MIN_SAMPLE_PERIOD_MILLISECONDS) {
    delay(10); 
    return; 
  }
  lastSampleMillis = millis();

  int cycleIdx = sampleCount % SAMPLES_PER_CYCLE; 
  if (sampleCount != 0 && cycleIdx == 0) { 
    performEndOfCycleJobs(); 
  }

  for (int i = 0; i < NUM_TEMPERATURE_SENSORS; i++) {
    temperatureSensorReadings[i][cycleIdx] = temperatureSensors[i].readTemperatureCelsius(); 
  } 

  sampleCount++;
}

void performEndOfCycleJobs() {
  int temperatureSensorBitMask = configStorageModule.getActiveSensorMask();
  for (int i = 0; i < NUM_TEMPERATURE_SENSORS; i++) {
    float sensorAvg = getAverageTemperatureSensorReading(1 << i); 
    Serial.print("Temperature (celsius) for sensor "); Serial.print(i + 1); Serial.print(" = "); Serial.println(sensorAvg);
  }
  float activeSensorAvg = getAverageTemperatureSensorReading(temperatureSensorBitMask); 
  updateLedStatus(activeSensorAvg); 
}

void updateLedStatus(float temperatureCelsius) {
  float absoluteError = abs(temperatureCelsius - configStorageModule.getDaytimeTemperatureTargetCelsius()); 
  boolean statusOk = absoluteError <= configStorageModule.getTemperatureToleranceCelsius(); 
  greenLed.setStatus(statusOk); 
  redLed.setStatus(!statusOk); 
}

float getAverageTemperatureSensorReading(int sensorBitMask) {
  float sum = 0.0; 
  int count = 0; 
  for (int i = 0; i < NUM_TEMPERATURE_SENSORS; i++) {
    if (!(sensorBitMask & (1 << i))) {
      continue; 
    }

    for (int j = 0; j < SAMPLES_PER_CYCLE; j++) {
      sum += temperatureSensorReadings[i][j]; 
      count++; 
    }
  }

  return count == 0 ? 0.0 : sum / count; 
}