#include <EEPROM.h> 

#include "ConfigStorageModule.h"
#include "Arduino.h"

// TODO this class is currently disabled since the NodeMCU ESP8266 does not have a genuine EEPROM
// rather than rewriting the code we use default values for now
ConfigStorageModule::ConfigStorageModule() {}; 

float ConfigStorageModule::getDaytimeTemperatureTargetCelsius() {
  return getOrDefaultFloat(DAYTIME_TEMPERATURE_TARGET_ADDRESS, DEFAULT_TEMPERATURE_TARGET_CELSIUS); 
}

float ConfigStorageModule::getEveningTemperatureTargetCelsius() {
  return getOrDefaultFloat(EVENING_TEMPERATURE_TARGET_ADDRESS, DEFAULT_TEMPERATURE_TARGET_CELSIUS); 
}

float ConfigStorageModule::getNighttimeTemperatureTargetCelsius() {
  return getOrDefaultFloat(NIGHTTIME_TEMPERATURE_TARGET_ADDRESS, DEFAULT_TEMPERATURE_TARGET_CELSIUS); 
}

float ConfigStorageModule::getTemperatureToleranceCelsius() {
  return getOrDefaultFloat(TEMPERATURE_TOLERANCE_ADDRESS, 2.0); 
}

int ConfigStorageModule::getActiveSensorMask() {
  return (int) getOrDefaultInt(ACTIVE_SENSOR_MASK_ADDRESS, 0xffffffff);
}

float ConfigStorageModule::getOrDefaultFloat(int startAddress, float defaultValue) {
  // float value; 
  // EEPROM.get(startAddress, value); 
  // // never-written memory byte = 255
  // return (value == 0xffffffff) ? defaultValue : value;
  return defaultValue; 
}

int ConfigStorageModule::getOrDefaultInt(int startAddress, int defaultValue) {
  // int value; 
  // EEPROM.get(startAddress, value); 
  // // never-written memory byte = 255
  // return (value == 0xffffffff) ? defaultValue : value;
  return defaultValue; 
}

void ConfigStorageModule::putDaytimeTemperatureTargetCelsius(float value) {
  putFloat(DAYTIME_TEMPERATURE_TARGET_ADDRESS, value); 
}

void ConfigStorageModule::putEveningTemperatureTargetCelsius(float value) {
  putFloat(EVENING_TEMPERATURE_TARGET_ADDRESS, value); 
}

void ConfigStorageModule::putNighttimeTemperatureTargetCelsius(float value) {
  putFloat(NIGHTTIME_TEMPERATURE_TARGET_ADDRESS, value); 
}

void ConfigStorageModule::putTemperatureToleranceCelsius(float value) {
  putFloat(TEMPERATURE_TOLERANCE_ADDRESS, value); 
}

void ConfigStorageModule::putActiveSensorMask(int value) {
  putInt(ACTIVE_SENSOR_MASK_ADDRESS, value); 
}

void ConfigStorageModule::putFloat(int startAddress, float value) {
  // eeprom memory has a specified life of 100,000 write/erase cycles
  // put only writes the value if it differs from the one already saved 
  // EEPROM.put(startAddress, value); 
}

void ConfigStorageModule::putInt(int startAddress, int value) {
  // eeprom memory has a specified life of 100,000 write/erase cycles
  // put only writes the value if it differs from the one already saved 
  // EEPROM.put(startAddress, value); 
}


void ConfigStorageModule::reset() {
  for (int i = 0 ; i < EEPROM.length() ; i++) {
    EEPROM.write(i, 0xff);
  }
}