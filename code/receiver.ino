#include "SoftwareSerial.h" 
#include <Arduino.h>
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>
#include <BLE2902.h>
#include <string.h>
#include <stdio.h>

#define RXp2 16
#define TXp2 17
//Choose service for BLE
#define SERVICE_UUID        "6e400001-b5a3-f393-e0a9-e50e24dcca9e"
#define CHARACTERISTIC_UUID_TX "6e400001-b5a3-f393-e0a9-e50e24dcca9e"

union{
  float Data4bytes;
  struct{
    char byte1;
    char byte2;
    char byte3;
    char byte4;
  }Byte;
}txValue;

BLECharacteristic *pCharacteristic;
bool deviceConnected = false;

class MyServerCallbacks: public BLEServerCallbacks {
    void onConnect(BLEServer* pServer) {
      deviceConnected = true;
    };

    void onDisconnect(BLEServer* pServer) {
      deviceConnected = false;
    }
};

void setup() {
  Serial.begin(115200);//config serial chanel, UART1 to PC, UART2 to xbee
  Serial2.begin(9600, SERIAL_8N1, RXp2, TXp2);

  //Setup BLE
  Serial.println("Starting BLE work!");

  BLEDevice::init("TEST1"); //config hostname sever

  BLEServer *pServer = BLEDevice::createServer(); //create sever
  pServer->setCallbacks(new MyServerCallbacks());

  BLEService *pService = pServer->createService(SERVICE_UUID);

  pCharacteristic = pService->createCharacteristic(
                                         CHARACTERISTIC_UUID_TX,
                                         BLECharacteristic::PROPERTY_NOTIFY
                                       );
  pCharacteristic->addDescriptor(new BLE2902());

  pService->start();

  pServer->getAdvertising()->start();
  Serial.println("wait...");
}

void loop() {
    if (deviceConnected) {
      while(Serial2.available()){
        // receive humidity
        txValue.Byte.byte1 = Serial2.read();
        txValue.Byte.byte2 = Serial2.read();
        txValue.Byte.byte3 = Serial2.read();
        txValue.Byte.byte4 = Serial2.read();
        // Let's convert the value to a char array:
        char txString[8]; // make sure this is big enuffz
        dtostrf(txValue.Data4bytes, 1, 2, txString); // float_val, min_width, digits_after_decimal, char_buffer
    
        pCharacteristic->setValue(txString);
    
        pCharacteristic->notify(); // Send the value to the app!
        Serial.print("*** Humidity : ");
        Serial.print(txString);
        Serial.println(" % ***");

        //receive temp
        txValue.Byte.byte1 = Serial2.read(); 
        txValue.Byte.byte2 = Serial2.read();
        txValue.Byte.byte3 = Serial2.read();
        txValue.Byte.byte4 = Serial2.read();
        dtostrf(txValue.Data4bytes, 1, 2, txString);
        Serial.print("*** Temp : ");
        Serial.print(txString);
        Serial.println(" oC ***");
    }
  }
}
