#include "LightSensor.h"
#include "EspMQTTClient.h"
#include "credentials.h"

EspMQTTClient client(
  SSIDD,
  PASSWORD,
  BROKER_IP,
  CLIENT_NAME,
  BROKER_PORT
);

String Lux_topic = "Lux";

String LuxToPublish;
void setup()
{
  Serial.begin(115200);
  client.enableDebuggingMessages(); 
  client.enableHTTPWebUpdater(); 

  Wire.begin();
  pinMode(TSL2581_INT, INPUT);
  read_id();
  tsl.TSL2581_power_on();
  delay(2000);
  tsl.TSL2581_config();
}

void onConnectionEstablished()
{
}

void loop()
{
  client.loop();
  Output();
  LuxToPublish = String(Output());
  client.publish(Lux_topic,LuxToPublish);
}
