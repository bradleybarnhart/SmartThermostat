#include "src/hardware/TemperatureSensor.h"

TemperatureSensor temperatureSensor1(A0, 60); 
TemperatureSensor temperatureSensor2(A1, 60); 

void setup() {
  Serial.begin(9600); 
}

void loop() {
  delay(1000); 

  temperatureSensor1.recordSample();  
  temperatureSensor2.recordSample(); 

  float temperatureReading1 = temperatureSensor1.getAverageTemperatureCelcius(); 
  float temperatureReading2 = temperatureSensor2.getAverageTemperatureCelcius(); 

  printTemperatureReading(1, temperatureReading1); 
  printTemperatureReading(2, temperatureReading2); 
}

void printTemperatureReading(int sensorId, float value) {
  Serial.print("Temperature (celsius) for sensor "); 
  Serial.print(sensorId); 
  Serial.print(" = "); 
  Serial.println(value); 
}