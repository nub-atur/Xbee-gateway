#include <DHT.h> 
#include <stdio.h>
#include <Arduino.h>
#include <string.h>
#include "SoftwareSerial.h"
#define RXp2 16  //choose UART2 chanel to connect with xbee  
#define TXp2 17
#define DHTPIN 21  //sensor pin
#define DHTTYPE DHT22  // sensor type
 
DHT dht(DHTPIN, DHTTYPE);

union{
  float Data4bytes;
  struct{
    char byte1;
    char byte2;
    char byte3;
    char byte4;
  }Byte;
}Data; // create a union of structures 

 
void setup()
{
  Serial.begin(115200);    
  Serial2.begin(9600, SERIAL_8N1, RXp2, TXp2);
  dht.begin();
}
 
void loop()
{
  delay(2000);
  //reading data 
  float h = dht.readHumidity();   
  float t = dht.readTemperature();

  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t)) {
   Serial.println("Failed to read from DHT sensor!");
    return;
  }

  //trans Humidity
  Data.Data4bytes = h;
  Serial2.write(Data.Byte.byte1); //send 4 bits each time
  Serial2.write(Data.Byte.byte2);
  Serial2.write(Data.Byte.byte3);
  Serial2.write(Data.Byte.byte4);
  Serial.print("Humidity:");
  Serial.print(h);
  Serial.println(F("%"));

  //trans Temp
  Data.Data4bytes = t;
  Serial2.write(Data.Byte.byte1);
  Serial2.write(Data.Byte.byte2);
  Serial2.write(Data.Byte.byte3);
  Serial2.write(Data.Byte.byte4);
  Serial.print("Temperature:");
  Serial.print(t);
  Serial.println(F("°C "));
}
