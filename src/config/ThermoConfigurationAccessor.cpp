#include "Arduino.h"
#include "ThermoConfigurationAccessor.h"

ThermoConfigurationAccessor::ThermoConfigurationAccessor() {}; 

float ThermoConfigurationAccessor::getTemperatureTargetCelcius() {
    return DEFAULT_TEMPERATURE_TARGET_CELCIUS; 
}

float ThermoConfigurationAccessor::getTemperatureToleranceCelcius() {
    return DEFAULT_TEMPERATURE_TOLERANCE_CELCIUS; 
}