#ifndef IotModule_h
#define IotModule_h

#include <WiFiClientSecure.h> 
#include <PubSubClient.h>

class IotModule {

    public:
      static const int MAX_MESSAGE_SIZE = 512; 

      IotModule(const char* pubTopic, const char* subTopic); 
      ~IotModule(); 

      void publishMessage(char* message); 
      void readLatestMessage(char* buffer); 
      void consumeLatestMessage(char* buffer); 
      void connectToWifiAndSyncLocalTime(int utcOffsetSeconds); 
      void connectToIot(); 
      void keepAlive(); 
      long getNtpTimeMillis();

    private:
      void receiveMessageHandler(char* topic, byte* payload, unsigned int length);
      void syncTime(int utcOffsetSeconds);

      char _latestMessage[MAX_MESSAGE_SIZE];
      char* _subTopic; 
      char* _pubTopic; 

      WiFiClientSecure _wiFiClient; 
      PubSubClient _pubSubClient; 
      BearSSL::X509List _clientCertificate; 
      BearSSL::PrivateKey _clientKey; 
      BearSSL::X509List _rootCert; 
}; 

#endif 