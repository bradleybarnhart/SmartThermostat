#ifndef ThermoConfigurationAccessor_h
#define ThermoConfigurationAccessor_h

#include "Arduino.h"

class ThermoConfigurationAccessor {
  static const float DEFAULT_TEMPERATURE_TARGET_CELCIUS = 21.0; 
  static const float DEFAULT_TEMPERATURE_TOLERANCE_CELCIUS = 2.0; 

  public:
    ThermoConfigurationAccessor(); 
    float getTemperatureTargetCelcius();
    float getTemperatureToleranceCelcius();

  private:
    int _digitalPin; 
};

#endif