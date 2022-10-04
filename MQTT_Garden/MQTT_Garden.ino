#include "EspMQTTClient.h"
#include "credentials.h"
#include "Temp1Wire.h"
#include <OneWire.h>
#include <DallasTemperature.h>

#define DataPin D8

#define soil_humidity A0
#define pump D5

#define AirValue 1024
#define WaterValue 573

EspMQTTClient client(
  SSIDD,
  PASSWORD,
  BROKER_IP,
  CLIENT_NAME,
  BROKER_PORT
);


String soil_humidity_topic = "Garden/SoilMoisture";
String temeprature_control = "Garden/TemperatureState";

String PumpControlTopic = "Garden/PumpState";

int current_soil_humidity;
int last_soil_humidity = -1;


int FlagPump1;

void setup()
{
  pinMode(soil_humidity, INPUT);
  pinMode(pump, OUTPUT);
  Serial.begin(115200);
  tempSensor.begin();
  client.enableDebuggingMessages(); 
  client.enableHTTPWebUpdater();
}

void onConnectionEstablished()
{
  client.subscribe(PumpControlTopic, [](const String & PumpState){
  PumpControl(PumpState);
  });
}

void loop()
{
  client.loop();
  current_soil_humidity = analogRead(soil_humidity);
  client.publish(temeprature_control, String(TempRead(), DEC));
  Serial.print(analogRead(soil_humidity));
  client.publish(soil_humidity_topic, String(current_soil_humidity, DEC));
  last_soil_humidity = current_soil_humidity;
  Serial.println();
  delay(1000);
}

void PumpControl(String PumpState)
{
  Serial.println(PumpState);
  if(PumpState[0] == '0')
  {
     digitalWrite(pump,LOW);
  }else if(PumpState[0] == '1')
  {
     digitalWrite(pump,HIGH);
  }
}
