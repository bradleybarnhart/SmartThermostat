### Setting up AWS Resources

**Create an AWS IoT Device.** 

1. Follow the "Creating an AWS IoT device," "Installing and configuring the Arduino IDE," and "Configuring and flashing an ESP32 IoT device" steps from https://aws.amazon.com/blogs/compute/building-an-aws-iot-core-device-using-aws-serverless-and-an-esp32/, replacing "ESP32" with "ESP8266" where appropriate.
    * Add Security.h file in src folder. See resources/aws/iot/SecurityTemplate.h for an example.

**Create IoT rules to publish temperature metrics to CloudWatch.** 

1. Create an IAM role called CloudWatchWriteOnly and configure it with CloudWatch WriteOnly access. 

2. Use the AWS CLI to deploy the rules from resources/aws/iot/rules. 
```
aws iot create-topic-rule --rule-name <rule> --topic-rule-payload file://<rule>.json
```

### Installing Additional Packages
**Install external packages using the Arduino IDE or a similar tool.**
* ArduinoJson
* PubSubClient
* MQTT



