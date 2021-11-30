#include <ESP8266WiFi.h>

#include "IotModule.h"
#include "Security.h"

IotModule::IotModule(const char* pubTopic, const char* subTopic) : 
  _clientCertificate(AWS_CERT_CRT), 
  _clientKey(AWS_CERT_PRIVATE),
  _rootCert(AWS_CERT_CA),
  _wiFiClient(),
  _pubSubClient(
    AWS_IOT_ENDPOINT,
    8883, 
    [=](char* topic, byte* payload, unsigned int length){ this->receiveMessageHandler(topic, payload, length); }, 
    _wiFiClient) 
{
  _pubTopic = strdup(pubTopic); 
  _subTopic = strdup(subTopic); 
}; 

IotModule::~IotModule() {
  free(_pubTopic); 
  free(_subTopic); 
}

void IotModule::publishMessage(char* message) {
  _pubSubClient.publish(_pubTopic, message); 
}

void IotModule::consumeLatestMessage(char* buffer) {
  readLatestMessage(buffer); 
  memset(_latestMessage, '\0', MAX_MESSAGE_SIZE);
}

void IotModule::readLatestMessage(char* buffer) {
  strcpy(buffer, _latestMessage); 
}

void IotModule::receiveMessageHandler(char* topic, byte* payload, unsigned int length) {
  if (length > MAX_MESSAGE_SIZE) {
    Serial.print("[ERROR] maximum message size exceeded. Message size: "); Serial.println(length); 
    return; 
  }

  memset(_latestMessage, '\0', MAX_MESSAGE_SIZE);
  memcpy(_latestMessage, payload, length);
}

void IotModule::connectToWifiAndSyncLocalTime(int utcOffsetSeconds) {
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  WiFi.waitForConnectResult();

  // sync current time so certificates are not flagged as expired
  syncTime(utcOffsetSeconds);

  _wiFiClient.setClientRSACert(&_clientCertificate, &_clientKey);
  _wiFiClient.setTrustAnchors(&_rootCert);
}

void IotModule::keepAlive() {
  bool connected = _pubSubClient.loop(); 
  if (!connected) {
    connectToIot();
  }
}

void IotModule::connectToIot() {
  while (!_pubSubClient.connect(DEVICE_NAME)) {
    delay(50); 
  }
  while (!_pubSubClient.subscribe(_subTopic)) {
    delay(50); 
  }
}

void IotModule::syncTime(int utcOffsetSeconds) {
  configTime(utcOffsetSeconds, 0, "pool.ntp.org", "time.nist.gov");
  while (time(nullptr) < 24 * 60 * 60) {
    delay(500);
  }
}