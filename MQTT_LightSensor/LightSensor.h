#include <Wire.h>
#include "TSl2581.h"

WaveShare_TSL2581 tsl = WaveShare_TSL2581();
const int TSL2581_INT = D0;

void read_id(void)
{
  int   id;
  int a;
  id = tsl.TSL2581_Read_ID();
  a = id & 0xf0;      //The lower four bits are the silicon version number
  if (!(a == 144))    //ID = 90H = 144D
  {
    Serial.println("false ");
  } else {
    Serial.print("I2C DEV is working ,id = ");
    Serial.println(id);
    delay(500);
  }
}

void Read_gpio_interrupt(uint16_t mindata, uint16_t maxdata)
{
  tsl.SET_Interrupt_Threshold(mindata, maxdata);
  int val = digitalRead(TSL2581_INT);
  if (val == 1)
  {
    //Serial.print("interrupt = 1 \n");
  } else {
    //Serial.print("interrupt = 0 \n");
    tsl.Reload_register();
  }
}

int Output()
{
  unsigned int Lux;
  tsl.TSL2581_Read_Channel();
  Lux = tsl.calculateLux(2, NOM_INTEG_CYCLE);
 // Serial.print("Lux = " );
  Serial.println(Lux);
  Read_gpio_interrupt(2000, 50000);

  return Lux;
}
