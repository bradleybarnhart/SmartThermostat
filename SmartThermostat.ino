#include <ArduinoJson.h> 

#include "src/TemperatureSensor.h"
#include "src/Led.h"
#include "src/ConfigStorageModule.h"
#include "src/IotModule.h"

const int SAMPLES_PER_CYCLE = 30; 
const unsigned long MIN_SAMPLE_PERIOD_MILLISECONDS = 1000UL;
const int SEATTLE_UTC_OFFSET_SECONDS = -8 * 3600;

unsigned long sampleCount; 
unsigned long lastSampleMillis; 

ConfigStorageModule configStorageModule;
IotModule iotModule("TemperatureMetrics", "TemperatureNews"); 

// 3.3V for NodeMCU
const float BOARD_SUPPLY_VOLTAGE = 3.3; 

const int NUM_TEMPERATURE_SENSORS = 2; 
// TODO currently we are using the NodeMCU esp8266 board which has only 1 analog pin
TemperatureSensor temperatureSensors[] = { 
  TemperatureSensor(A0, BOARD_SUPPLY_VOLTAGE), 
  TemperatureSensor(A0, BOARD_SUPPLY_VOLTAGE)
}; 
float temperatureSensorReadings[NUM_TEMPERATURE_SENSORS][SAMPLES_PER_CYCLE];

Led greenLed(D0);
Led redLed(D1); 

void setup() {
  Serial.begin(9600);
  sampleCount = 0;
  lastSampleMillis = millis();

  Serial.println("Connecting to WiFi"); 
  iotModule.connectToWifiAndSyncLocalTime(SEATTLE_UTC_OFFSET_SECONDS); 
  Serial.println("WiFi connected"); 

  Serial.println("Connecting to PubSub topics via AWS IoT"); 
  iotModule.connectToIot(); 
  Serial.println("IoT Connected"); 
}

void loop() {
  if (millis() - lastSampleMillis < MIN_SAMPLE_PERIOD_MILLISECONDS) {
    delay(10); 
    return; 
  }
  lastSampleMillis = millis();

  // perform certain jobs only once per cycle 
  int cycleIdx = sampleCount % SAMPLES_PER_CYCLE; 
  if (sampleCount != 0 && cycleIdx == 0) { 
    checkForConfigUpdates(); 
    postTemperatureMetrics(); 
    updateLedStatus(getAverageTemperatureOnActiveSensors()); 
  }

  // take temperature readings and maintain IoT connection for every loop iteration
  for (int i = 0; i < NUM_TEMPERATURE_SENSORS; i++) {
    temperatureSensorReadings[i][cycleIdx] = temperatureSensors[i].readTemperatureCelsius(); 
  }
  iotModule.keepAlive(); 

  sampleCount++;
}

void checkForConfigUpdates() {
  char payload[IotModule::MAX_MESSAGE_SIZE]; 
  iotModule.consumeLatestMessage(payload); 

  if (strlen(payload) > 0) {
    StaticJsonDocument<IotModule::MAX_MESSAGE_SIZE> doc;
    deserializeJson(doc, payload); 
    if (doc.containsKey("daytimeTarget")) {
      Serial.println("Updating config attribute 'daytimeTarget'");
      configStorageModule.putDaytimeTemperatureTargetCelsius(doc["daytimeTarget"]);
    }
    if (doc.containsKey("eveningTarget")) {
      Serial.println("Updating config attribute 'eveningTarget'");
      configStorageModule.putEveningTemperatureTargetCelsius(doc["eveningTarget"]);
    }
    if (doc.containsKey("nighttimeTarget")) {
      Serial.println("Updating config attribute 'nighttimeTarget'");
      configStorageModule.putNighttimeTemperatureTargetCelsius(doc["nighttimeTarget"]);
    }
    if (doc.containsKey("tolerance")) {
      Serial.println("Updating config attribute 'tolerance'");
      configStorageModule.putTemperatureToleranceCelsius(doc["tolerance"]);
    }
    if (doc.containsKey("activeSensorMask")) {
      Serial.println("Updating config attribute 'activeSensorMask'");
      configStorageModule.putActiveSensorMask(doc["activeSensorMask"]);
    }
  }
}

void postTemperatureMetrics() {
  StaticJsonDocument<IotModule::MAX_MESSAGE_SIZE> doc;
  for (int i = 0; i < NUM_TEMPERATURE_SENSORS; i++) {
    float sensorAvg = getAverage(temperatureSensorReadings[i], SAMPLES_PER_CYCLE); 
    String metricName = "IndoorTemperatureCelsius_Sensor" + String(i + 1); 
    doc[metricName] = sensorAvg; 
  }
  doc["TargetTemperatureCelsius"] = getCurrentTargetTemperature(); 
  char payload[IotModule::MAX_MESSAGE_SIZE];
  serializeJson(doc, payload);

  Serial.println("Publishing temperature metrics");
  iotModule.publishMessage(payload); 
}

void updateLedStatus(float temperatureCelsius) {
  float targetTemperatureCelsius = getCurrentTargetTemperature(); 
  float absoluteError = abs(temperatureCelsius - targetTemperatureCelsius); 
  boolean statusOk = absoluteError <= configStorageModule.getTemperatureToleranceCelsius(); 
  Serial.print("Current temperature (celsius): "); Serial.println(temperatureCelsius); 
  Serial.print("Target temperature (celsius):  "); Serial.println(targetTemperatureCelsius); 
  greenLed.setStatus(statusOk); 
  redLed.setStatus(!statusOk); 
}

float getAverageTemperatureOnActiveSensors() {
  int activeSensorMask = configStorageModule.getActiveSensorMask();
  float values[NUM_TEMPERATURE_SENSORS * SAMPLES_PER_CYCLE]; 
  int countSoFar = 0; 
  for (int i = 0; i < NUM_TEMPERATURE_SENSORS; i++) {
    if (activeSensorMask & (1 << i)) {
      memcpy(&values[countSoFar], temperatureSensorReadings[i], SAMPLES_PER_CYCLE * sizeof(float));
      countSoFar += SAMPLES_PER_CYCLE; 
    }
  }
  return getAverage(values, countSoFar); 
}

float getAverage(float values[], int size) {
  if (size == 0) { return 0.0; }

  float sum = 0.0; 
  int count = 0; 
  for (int i = 0; i < size; i++) {
    sum += values[i]; 
    count++; 
  }
  return sum / count; 
}

float getCurrentTargetTemperature() {
  time_t now = time(nullptr);
  int hour = localtime(&now)->tm_hour; 
  if (hour >= 6 && hour < 17) {
    return configStorageModule.getDaytimeTemperatureTargetCelsius(); 
  } else if (hour >= 17 && hour < 22) {
    return configStorageModule.getEveningTemperatureTargetCelsius(); 
  } else {
    return configStorageModule.getNighttimeTemperatureTargetCelsius(); 
  }
}

void printTime() {
  time_t now = time(nullptr); 
  Serial.print("Current time: "); Serial.println(asctime(localtime(&now)));
}