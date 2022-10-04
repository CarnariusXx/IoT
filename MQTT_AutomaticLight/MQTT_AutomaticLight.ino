#include "EspMQTTClient.h"
#include "credentials.h"

#define PIR_Lights D7
#define PIR_Camera D8

EspMQTTClient client(
  SSIDD,
  PASSWORD,
  BROKER_IP,
  CLIENT_NAME,
  BROKER_PORT
);

EspMQTTClient client2(
  "",
  "",
  "",
  "esp8266_332",
  1883
);

String PIRSensrorTopic = "MotionSensor";


void setup() {
    Serial.begin(115200);
    pinMode(PIR_Lights, INPUT);
    pinMode(PIR_Camera, INPUT);
    client.enableDebuggingMessages(); 
    client.enableHTTPWebUpdater(); 
    client2.enableDebuggingMessages(); 
    client2.enableHTTPWebUpdater(); 
}

void onConnectionEstablished(){ 
}

void loop() {
    client.loop();
    client2.loop();
    PIRSensorOutput();
    PIRSensorOutput2();
    delay(2000);
}

void PIRSensorOutput()
{
  int val = digitalRead(PIR_Lights);  
  if (val == HIGH) {
    Serial.println("Motion detected!");
    client.publish(PIRSensrorTopic, "1");
    delay(10000);
    }
  else {
    Serial.println("No Motion detected!");
    client.publish(PIRSensrorTopic, "0");
    }
  
}

void PIRSensorOutput2()
{
  int val = digitalRead(PIR_Camera);  
  if (val == HIGH) {
    Serial.println("Motion detected!");
    client2.publish("MotionSensor2", "1");
    delay(100);
    }
  else {
    Serial.println("No Motion detected!");
    client2.publish("MotionSensor2", "0");
    }
  
}
