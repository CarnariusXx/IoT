#include "DHT.h"
#include "EspMQTTClient.h"
#include "credentials.h"

#define LED D3
#define FAN D4
#define DHTPIN D1   
#define DHTTYPE DHT22  

DHT dht(DHTPIN, DHTTYPE);

EspMQTTClient client(
  SSIDD,
  PASSWORD,
  BROKER_IP,
  CLIENT_NAME,
  BROKER_PORT
);

String UserHeatTopic = "Heat/UserChage";
String TempReadTopic = "Heat/TemperatureRead";
String HumidReadTopic = "Heat/HumidityRead";

String UserFanTopic = "Heat/UserFanTemp";
String FanStateTopic = "Heat/FanState";
String HeatStateTopic = "Heat/HeatState";

float Temp;
float Humid;
String TempChoice;

int Flag = 0;
int FanFlag = 0;

void setup() {
  Serial.begin(115200);
  pinMode(D3,OUTPUT);
  pinMode(FAN, OUTPUT);
  dht.begin();
  client.enableDebuggingMessages(); 
  client.enableHTTPWebUpdater(); 
}

void onConnectionEstablished()
{
  client.subscribe(UserHeatTopic, [](const String & UserTemp){
  HeatControl(UserTemp);
  });   

  client.subscribe(FanStateTopic, [](const String & State){
  FanStateFunc(State);
  });

  client.subscribe(HeatStateTopic, [](const String & HeatState){
  HeatStateFunc(HeatState);
  });

  client.subscribe(FanStateTopic, [](const String & State){
  FanStateFunc(State);
  });

  client.subscribe(testtopic, [](const String & payload){
  Serial.println(payload);
  });
}


void loop() {
  client.loop();
  Temp = dht.readTemperature();
  Humid = dht.readHumidity();

  client.publish(TempReadTopic,String(Temp,DEC));
  client.publish(HumidReadTopic,String(Humid,DEC));
  Serial.println(Flag);
  delay(1000);
}

void HeatStateFunc(String HeatState)
{
  if(HeatState == "1")
  {
    //Flag = 1;
    digitalWrite(D3,HIGH);
  }
  else if(HeatState == "0")
  {
    //Flag = 0;
    digitalWrite(D3,LOW);
  }
}

void HeatControl(String UserTemp)
{
  if(UserTemp.toInt() > Temp)
    {
       Flag = 1;
       digitalWrite(D3,HIGH);
    }else{
       Flag = 0;
       digitalWrite(D3,LOW);
    }
}

void FanStateFunc(String State)
{
  if(State == "1")
  {
     FanFlag = 1;
     digitalWrite(FAN,HIGH);
  }else if(State == "0")
  {
     FanFlag = 0;
     digitalWrite(FAN,LOW);
  }
}
void FanControl(String UserFanTemp)
{
  if(UserFanTemp.toInt() <= Temp)
    {
    //  client.publish(FanStateFunc, "1");
      FanFlag = 1;
      digitalWrite(FAN,HIGH);
    }else{
      // client.publish(FanStateFunc, "0");
       FanFlag = 0;
       digitalWrite(FAN,LOW);
    }
}
