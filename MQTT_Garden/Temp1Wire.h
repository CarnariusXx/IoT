#include <OneWire.h>
#include <DallasTemperature.h>

#define DataPin D8

OneWire oneWire(DataPin);         
DallasTemperature tempSensor(&oneWire); 

float Temp;    

float TempRead()
{
  tempSensor.requestTemperatures();            
  Temp = tempSensor.getTempCByIndex(0);  // read temperature in Celsius
  Serial.println(Temp); 

  return Temp;
}
