#ifndef StorageModule_h
#define StorageModule_h

class StorageModule { 

  public:
    StorageModule(); 
    float getDaytimeTemperatureTargetCelsius();
    float getEveningTemperatureTargetCelsius();
    float getNighttimeTemperatureTargetCelsius();
    float getDaytimeTemperatureTargetCelsius();
    float getTemperatureToleranceCelsius();
    void putDaytimeTemperatureTargetCelsius(float value);
    void putEveningTemperatureTargetCelsius(float value);
    void putNighttimeTemperatureTargetCelsius(float value);
    void putTemperatureToleranceCelsius(float value);
    void reset(); 

  private:
    static constexpr float DEFAULT_TEMPERATURE_TARGET_CELSIUS = 21.0; 
    static constexpr float DEFAULT_TEMPERATURE_TOLERANCE_CELSIUS = 2.0; 

    static const int DAYTIME_TEMPERATURE_TARGET_ADDRESS = 0; 
    static const int EVENING_TEMPERATURE_TARGET_ADDRESS = 4; 
    static const int NIGHTTIME_TEMPERATURE_TARGET_ADDRESS = 8; 
    static const int TEMPERATURE_TOLERANCE_ADDRESS = 12;

    float getOrDefault(int startAddress, float defaultValue); 
    void put(int startAddress, float value); 
};

#endif