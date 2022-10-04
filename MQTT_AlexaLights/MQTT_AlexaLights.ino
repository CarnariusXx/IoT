#include <AceButton.h>
#include "EspMQTTClient.h"
#include "credentials.h"

using namespace ace_button;

#define Lamp_1 2 //D23
#define Lamp_2 4 //D22
#define Lamp_3 5 //D21
#define Lamp_4 18 //D19
#define Lamp_5 19 //D18
#define Lamp_6 21 //D5
#define Lamp_7 22 //D4
#define Lamp_8 23 //D2

#define Switch_1 13 //D13
#define Switch_2 12 //D12
#define Switch_3 14 //D14
#define Switch_4 27 //D27
#define Switch_5 26 //D26
#define Switch_6 25 //D25
#define Switch_7 33 //D33
#define Switch_8 32 //D32

ButtonConfig config1;
AceButton button1(&config1);

ButtonConfig config2;
AceButton button2(&config2);

ButtonConfig config3;
AceButton button3(&config3);

ButtonConfig config4;
AceButton button4(&config4);

ButtonConfig config5;
AceButton button5(&config5);

ButtonConfig config6;
AceButton button6(&config6);

ButtonConfig config7;
AceButton button7(&config7);

ButtonConfig config8;
AceButton button8(&config8);

void handleEvent1(AceButton*, uint8_t, uint8_t);
void handleEvent2(AceButton*, uint8_t, uint8_t);
void handleEvent3(AceButton*, uint8_t, uint8_t);
void handleEvent4(AceButton*, uint8_t, uint8_t);
void handleEvent5(AceButton*, uint8_t, uint8_t);
void handleEvent6(AceButton*, uint8_t, uint8_t);
void handleEvent7(AceButton*, uint8_t, uint8_t);
void handleEvent8(AceButton*, uint8_t, uint8_t);

EspMQTTClient client(
  SSIDD,
  PASSWORD,
  BROKER_IP,
  CLIENT_NAME,
  BROKER_PORT
);

String Light1Topic = "Lights/Light1";
String Light2Topic = "Lights/Light2";
String Light3Topic = "Lights/Light3";
String Light4Topic = "Lights/Light4";
String Light5Topic = "Lights/Light5";
String Light6Topic = "Lights/Light6";
String Light7Topic = "Lights/Light7";
String Light8Topic = "Lights/Light8";

void setup() {
    Serial.begin(115200);
    pinMode(Lamp_1, OUTPUT);
    pinMode(Lamp_2, OUTPUT);
    pinMode(Lamp_3, OUTPUT);
    pinMode(Lamp_4, OUTPUT);
    pinMode(Lamp_5, OUTPUT);
    pinMode(Lamp_6, OUTPUT);
    pinMode(Lamp_7, OUTPUT);
    pinMode(Lamp_8, OUTPUT);

    pinMode(Switch_1, INPUT_PULLUP);
    pinMode(Switch_2, INPUT_PULLUP);
    pinMode(Switch_3, INPUT_PULLUP);
    pinMode(Switch_4, INPUT_PULLUP);
    pinMode(Switch_5, INPUT_PULLUP);
    pinMode(Switch_6, INPUT_PULLUP);
    pinMode(Switch_7, INPUT_PULLUP);
    pinMode(Switch_8, INPUT_PULLUP);
    
  config1.setEventHandler(button1Handler);
  config2.setEventHandler(button2Handler);
  config3.setEventHandler(button3Handler);
  config4.setEventHandler(button4Handler);
  config5.setEventHandler(button5Handler);
  config6.setEventHandler(button6Handler);
  config7.setEventHandler(button7Handler);
  config8.setEventHandler(button8Handler);

  button1.init(Switch_1);
  button2.init(Switch_2);
  button3.init(Switch_3);
  button4.init(Switch_4);
  button5.init(Switch_5);
  button6.init(Switch_6);
  button7.init(Switch_7);
  button8.init(Switch_8);

  client.enableDebuggingMessages(); 
  client.enableHTTPWebUpdater(); 
}

void onConnectionEstablished()
{
  client.subscribe(Light1Topic, [](const String & Light1State){
  Light1Control(Light1State);
  });

  client.subscribe(Light2Topic, [](const String & Light2State){
  Light2Control(Light2State);
  });

  client.subscribe(Light3Topic, [](const String & Light3State){
  Light3Control(Light3State);
  });

  client.subscribe(Light4Topic, [](const String & Light4State){
  Light4Control(Light4State);
  });

  client.subscribe(Light5Topic, [](const String & Light5State){
  Light5Control(Light5State);
  });

  client.subscribe(Light6Topic, [](const String & Light6State){
  Light6Control(Light6State);
  });

  client.subscribe(Light7Topic, [](const String & Light7State){
  Light7Control(Light7State);
  }); 

  client.subscribe(Light8Topic, [](const String & Light8State){
  Light8Control(Light8State);
  });           
}

void loop() {
    client.loop();
    button1.check();
    button2.check();
    button3.check();
    button4.check();
    button5.check();
    button6.check();
    button7.check();
    button8.check();
    //delay(500);
}

void Light1Control(String Light1State)
{
    Serial.println(Light1State);
  if(Light1State[0] == '0')
  {
     digitalWrite(Lamp_1,HIGH);
  }else if(Light1State[0] == '1')
  {
     digitalWrite(Lamp_1,LOW);
  }
}
void Light2Control(String Light2State)
{
      Serial.println(Light2State);
  if(Light2State[0] == '0')
  {
     digitalWrite(Lamp_2,HIGH);
  }else if(Light2State[0] == '1')
  {
     digitalWrite(Lamp_2,LOW);
  }
}
void Light3Control(String Light3State)
{
      Serial.println(Light3State);
  if(Light3State[0] == '0')
  {
     digitalWrite(Lamp_3,HIGH);
  }else if(Light3State[0] == '1')
  {
     digitalWrite(Lamp_3,LOW);
  }
}
void Light4Control(String Light4State)
{
      Serial.println(Light4State);
  if(Light4State[0] == '0')
  {
     digitalWrite(Lamp_4,HIGH);
  }else if(Light4State[0] == '1')
  {
     digitalWrite(Lamp_4,LOW);
  }
}
void Light5Control(String Light5State)
{
      Serial.println(Light5State);
  if(Light5State[0] == '0')
  {
     digitalWrite(Lamp_5,HIGH);
  }else if(Light5State[0] == '1')
  {
     digitalWrite(Lamp_5,LOW);
  }
}
void Light6Control(String Light6State)
{
      Serial.println(Light6State);
  if(Light6State[0] == '0')
  {
     digitalWrite(Lamp_6,HIGH);
  }else if(Light6State[0] == '1')
  {
     digitalWrite(Lamp_6,LOW);
  }
}
void Light7Control(String Light7State)
{
      Serial.println(Light7State);
  if(Light7State[0] == '0')
  {
     digitalWrite(Lamp_7,HIGH);
  }else if(Light7State[0] == '1')
  {
     digitalWrite(Lamp_7,LOW);
  }
}
void Light8Control(String Light8State)
{
      Serial.println(Light8State);
  if(Light8State[0] == '0')
  {
     digitalWrite(Lamp_8,HIGH);
  }else if(Light8State[0] == '1')
  {
     digitalWrite(Lamp_8,LOW);
  }
}


void button1Handler(AceButton* button, uint8_t eventType, uint8_t buttonState) {
  switch (eventType) {
    case AceButton::kEventPressed:
      Serial.println("kEventPressed");
      digitalWrite(Lamp_1, LOW);
      client.publish("ManualSwitch1","on");
      break;
    case AceButton::kEventReleased:
      Serial.println("kEventReleased");
      digitalWrite(Lamp_1, HIGH);
      client.publish("ManualSwitch1","off");
      break;
  }
}

void button2Handler(AceButton* button, uint8_t eventType, uint8_t buttonState) {
  switch (eventType) {
    case AceButton::kEventPressed:
      Serial.println("kEventPressed");
      digitalWrite(Lamp_2, LOW);
      client.publish("ManualSwitch2","on");
      break;
    case AceButton::kEventReleased:
     // Serial.println("kEventReleased");
      digitalWrite(Lamp_2, HIGH);
      client.publish("ManualSwitch2","off");
      break;
  }
}

void button3Handler(AceButton* button, uint8_t eventType, uint8_t buttonState) {
  switch (eventType) {
    case AceButton::kEventPressed:
      Serial.println("kEventPressed");
      digitalWrite(Lamp_3, LOW);
      client.publish("ManualSwitch3","on");
      break;
    case AceButton::kEventReleased:
      Serial.println("kEventReleased");
      digitalWrite(Lamp_3, HIGH);
      client.publish("ManualSwitch3","off");
      break;
  }
}

void button4Handler(AceButton* button, uint8_t eventType, uint8_t buttonState) {
  switch (eventType) {
    case AceButton::kEventPressed:
      Serial.println("kEventPressed");
      digitalWrite(Lamp_4, LOW);
      client.publish("ManualSwitch4","on");
      break;
    case AceButton::kEventReleased:
      Serial.println("kEventReleased");
      digitalWrite(Lamp_4, HIGH);
      client.publish("ManualSwitch4","off");
      break;
  }
}

void button5Handler(AceButton* button, uint8_t eventType, uint8_t buttonState) {
  switch (eventType) {
    case AceButton::kEventPressed:
      Serial.println("kEventPressed");
      digitalWrite(Lamp_5, LOW);
      client.publish("ManualSwitch5","on");
      break;
    case AceButton::kEventReleased:
      Serial.println("kEventReleased");
      digitalWrite(Lamp_5, HIGH);
      client.publish("ManualSwitch5","off");
      break;
  }
}

void button6Handler(AceButton* button, uint8_t eventType, uint8_t buttonState) {
  switch (eventType) {
    case AceButton::kEventPressed:
      Serial.println("kEventPressed");
      digitalWrite(Lamp_6, LOW);
      client.publish("ManualSwitch6","on");
      break;
    case AceButton::kEventReleased:
     // Serial.println("kEventReleased");
      digitalWrite(Lamp_6, HIGH);
      client.publish("ManualSwitch6","off");
      break;
  }
}

void button7Handler(AceButton* button, uint8_t eventType, uint8_t buttonState) {
  switch (eventType) {
    case AceButton::kEventPressed:
      Serial.println("kEventPressed");
      digitalWrite(Lamp_7, LOW);
      client.publish("ManualSwitch7","on");
      break;
    case AceButton::kEventReleased:
      Serial.println("kEventReleased");
      digitalWrite(Lamp_7, HIGH);
      client.publish("ManualSwitch7","off");
      break;
  }
}

void button8Handler(AceButton* button, uint8_t eventType, uint8_t buttonState) {
  switch (eventType) {
    case AceButton::kEventPressed:
      Serial.println("kEventPressed");
      digitalWrite(Lamp_8, LOW);
      client.publish("ManualSwitch8","on");
      break;
    case AceButton::kEventReleased:
      Serial.println("kEventReleased");
      digitalWrite(Lamp_8, HIGH);
      client.publish("ManualSwitch8","off");
      break;
  }
}
