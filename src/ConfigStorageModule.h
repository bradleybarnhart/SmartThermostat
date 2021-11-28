#ifndef ConfigStorageModule_h
#define ConfigStorageModule_h

class ConfigStorageModule { 

  public:
    ConfigStorageModule(); 
    float getDaytimeTemperatureTargetCelsius();
    float getEveningTemperatureTargetCelsius();
    float getNighttimeTemperatureTargetCelsius();
    float getTemperatureToleranceCelsius();
    int getActiveSensorMask(); 
    void putDaytimeTemperatureTargetCelsius(float value);
    void putEveningTemperatureTargetCelsius(float value);
    void putNighttimeTemperatureTargetCelsius(float value);
    void putTemperatureToleranceCelsius(float value);
    void putActiveSensorMask(int value); 
    void reset(); 

  private:
    static constexpr float DEFAULT_TEMPERATURE_TARGET_CELSIUS = 21.0; 

    static const int DAYTIME_TEMPERATURE_TARGET_ADDRESS = 0; 
    static const int EVENING_TEMPERATURE_TARGET_ADDRESS = 4; 
    static const int NIGHTTIME_TEMPERATURE_TARGET_ADDRESS = 8; 
    static const int TEMPERATURE_TOLERANCE_ADDRESS = 12;
    static const int ACTIVE_SENSOR_MASK_ADDRESS = 16;

    float getOrDefaultFloat(int startAddress, float defaultValue); 
    int getOrDefaultInt(int startAddress, int defaultValue);
    void putFloat(int startAddress, float value); 
    void putInt(int startAddress, int value); 
};

#endif