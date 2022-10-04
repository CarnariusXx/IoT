#include <SPI.h>
#include <MFRC522.h>
#include "EspMQTTClient.h"

EspMQTTClient client(
  "",
  "",
  "",
  "ESP333",
  1883
);


int counter = 0;
/* 
 *  RST (Reset) <-> D0
    GND (Ground) <-> GND
    MISO (Master Input Slave Output) <-> D6
    MOSI (Master Output Slave Input) <-> D7
    SCK (Serial Clock) <-> D5
    SS/SDA (Slave select) <-> D8
 */
#define SS_PIN D8 //SDA
#define RST_PIN D0 
#define RELAY D1 //relay pin
#define ACCESS_DELAY 2000
#define DENIED_DELAY 1000

MFRC522 mfrc522(SS_PIN, RST_PIN);

int LockState = 0;
int MagnetState = 0;
void setup() 
{
  Serial.begin(115200);  
  SPI.begin();         
  mfrc522.PCD_Init();   
  pinMode(RELAY, OUTPUT);
  digitalWrite(RELAY, HIGH);
  pinMode(D3, INPUT_PULLUP);
  Serial.println("Put your card to the reader...");
  Serial.println();

  client.enableDebuggingMessages(); 
  client.enableHTTPWebUpdater(); 
}

void onConnectionEstablished(){}

void RFID()
{
  if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    return;
  }
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }
  
  Serial.print("UID tag :");
  String content= "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  content.toUpperCase();
  if ((content.substring(1) == "03 08 F3 A3")||(content.substring(1)=="5B AD 46 5B"))
  {
    LockState = 1;
    Serial.println("Authorized access");
    Serial.println();
    digitalWrite(RELAY, LOW);
    delay(ACCESS_DELAY);
    digitalWrite(RELAY, HIGH);
    LockState = 0;
  }
 else   {
    Serial.println(" Access denied");
    delay(DENIED_DELAY);
  }
}
void Reed()
{
  if(digitalRead(D3) == LOW )
  {
    client.publish("Reed", "0");
    }else if(digitalRead(D3) == HIGH)
  {
     client.publish("Reed", "1");
   }
}

void loop() 
{
  client.loop();
  RFID();
  Reed();
  delay(500);
}
