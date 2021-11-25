#include <EEPROM.h> 

#include "ThermoConfigurationAccessor.h"
#include "Arduino.h"

ThermoConfigurationAccessor::ThermoConfigurationAccessor() {}; 

float ThermoConfigurationAccessor::getTemperatureTargetCelcius() {
  return getOrDefault(TEMPERATURE_TARGET_ADDRESS, DEFAULT_TEMPERATURE_TARGET_CELCIUS); 
}

float ThermoConfigurationAccessor::getTemperatureToleranceCelcius() {
  return getOrDefault(TEMPERATURE_TOLERANCE_ADDRESS, DEFAULT_TEMPERATURE_TOLERANCE_CELCIUS); 
}

float ThermoConfigurationAccessor::getOrDefault(int startAddress, float defaultValue) {
  float value; 
  EEPROM.get(startAddress, value); 
  // cleared memory byte = 0, never written memory byte = 255
  return (value == 0x00000000 || value == 0xffffffff) ? defaultValue : value;  
}

void ThermoConfigurationAccessor::putTemperatureTargetCelcius(float value) {
  put(TEMPERATURE_TARGET_ADDRESS, value); 
}

void ThermoConfigurationAccessor::putTemperatureToleranceCelcius(float value) {
  put(TEMPERATURE_TOLERANCE_ADDRESS, value); 
}

void ThermoConfigurationAccessor::put(int startAddress, float value) {
  // eeprom memory has a specified life of 100,000 write/erase cycles
  // put only writes the value if it differs from the one already saved 
  EEPROM.put(startAddress, value); 
}

void ThermoConfigurationAccessor::reset() {
  for (int i = 0 ; i < EEPROM.length() ; i++) {
    EEPROM.write(i, 0);
  }
}