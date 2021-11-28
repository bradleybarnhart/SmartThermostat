#include <EEPROM.h> 

#include "ConfigStorageModule.h"
#include "Arduino.h"

ConfigStorageModule::ConfigStorageModule() {}; 

float ConfigStorageModule::getDaytimeTemperatureTargetCelsius() {
  return getOrDefault(DAYTIME_TEMPERATURE_TARGET_ADDRESS, DEFAULT_TEMPERATURE_TARGET_CELSIUS); 
}

float ConfigStorageModule::getEveningTemperatureTargetCelsius() {
  return getOrDefault(EVENING_TEMPERATURE_TARGET_ADDRESS, DEFAULT_TEMPERATURE_TARGET_CELSIUS); 
}

float ConfigStorageModule::getNighttimeTemperatureTargetCelsius() {
  return getOrDefault(NIGHTTIME_TEMPERATURE_TARGET_ADDRESS, DEFAULT_TEMPERATURE_TARGET_CELSIUS); 
}

float ConfigStorageModule::getTemperatureToleranceCelsius() {
  return getOrDefault(TEMPERATURE_TOLERANCE_ADDRESS, DEFAULT_TEMPERATURE_TOLERANCE_CELSIUS); 
}

float ConfigStorageModule::getOrDefault(int startAddress, float defaultValue) {
  float value; 
  EEPROM.get(startAddress, value); 
  // cleared memory byte = 0, never written memory byte = 255
  return (value == 0x00000000 || value == 0xffffffff) ? defaultValue : value;
}

void ConfigStorageModule::putDaytimeTemperatureTargetCelsius(float value) {
  put(DAYTIME_TEMPERATURE_TARGET_ADDRESS, value); 
}

void ConfigStorageModule::putEveningTemperatureTargetCelsius(float value) {
  put(EVENING_TEMPERATURE_TARGET_ADDRESS, value); 
}

void ConfigStorageModule::putNighttimeTemperatureTargetCelsius(float value) {
  put(NIGHTTIME_TEMPERATURE_TARGET_ADDRESS, value); 
}

void ConfigStorageModule::putTemperatureToleranceCelsius(float value) {
  put(TEMPERATURE_TOLERANCE_ADDRESS, value); 
}

void ConfigStorageModule::put(int startAddress, float value) {
  // eeprom memory has a specified life of 100,000 write/erase cycles
  // put only writes the value if it differs from the one already saved 
  EEPROM.put(startAddress, value); 
}

void ConfigStorageModule::reset() {
  for (int i = 0 ; i < EEPROM.length() ; i++) {
    EEPROM.write(i, 0);
  }
}