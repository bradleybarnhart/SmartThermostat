#ifndef ThermoConfigurationAccessor_h
#define ThermoConfigurationAccessor_h

class ThermoConfigurationAccessor { 

  public:
    ThermoConfigurationAccessor(); 
    float getTemperatureTargetCelsius();
    float getTemperatureToleranceCelsius();
    void putTemperatureTargetCelsius(float value);
    void putTemperatureToleranceCelsius(float value);
    void reset(); 

  private:
    static constexpr float DEFAULT_TEMPERATURE_TARGET_CELSIUS = 21.0; 
    static constexpr float DEFAULT_TEMPERATURE_TOLERANCE_CELSIUS = 2.0; 

    static const int TEMPERATURE_TARGET_ADDRESS = 0; 
    static const int TEMPERATURE_TOLERANCE_ADDRESS = 256;

    float getOrDefault(int startAddress, float defaultValue); 
    void put(int startAddress, float value); 
};

#endif