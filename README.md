# A Gateway using Xbee

In this repository, I create a communication between two microcontrollers using XBee protocol, then sending frames to phone through Bluetooth Low Energy (BLE).

![image](https://github.com/nub-atur/simple-xbee-gateway/assets/136115054/38464109-f88d-4a5b-aa67-736b78088385)

Components:
  - NODEMCU ESP32 (I used the Arduino IDE to program esp32, so you may need this link [How to Program ESP32 with Arduino IDE? ](https://www.electronicshub.org/esp32-arduino-ide/#:~:text=In%20Windows%20OS%2C%20go%20to,and%20click%20on%20Upload%20button.))
  - module XBee S2C (with module board base shield for easily serial connecting)
  - DHT22 Sensor Module 
  - A phone has been installed [nRF Connect](https://play.google.com/store/apps/details?id=no.nordicsemi.android.mcp&hl=en_US&pli=1)

# Configuration
Install [XCTU](http://www.digi.com/products/wireless-wired-embedded-solutions/zigbee-rf-modules/xctu). Use `XCTU` for installing the firmware to the `XBee®` devices. `XBee® ZigBee` network must have only one `Coordinator`. All other devices in the network must be `XBee® ZigBee End Device` or `XBee® ZigBee Router`. Here, the second xbee is configured as a router. 

  XBee® ZigBee Coordinator:
  - Coordinator must have the firmware with `ZigBee Coordinator API` functional set.
  - Use XCTU to set `PAN ID`, `Coordinator Enable`.
  - Use XCTU to set `BD` (Baud Rate) to `9600`.

  XBee® ZigBee Router:
  - Devices must have the firmware with `ZigBee Router` functional set.
  - Use XCTU to set `PAN ID`. It must be equal with Coordinator.
  - Use XCTU to set `DH` and `DL` to 0x0 (send data to Coordinator).

Next, we will connect each Esp32 to each Xbee by using serial protocol (Rx->Tx, Tx->Rx). The one with xbee coordinator is called receiver, the other one is called transmitter.

Then we connect DHT22 sensor to Esp32 (transmitter) like this:
![image](https://github.com/nub-atur/simple-xbee-gateway/assets/136115054/049b4091-1648-41f0-a9f4-c6658d9ee935)

#Usage
- Install all necessary libraries
- Upload code to Esp32 board
- Turn on your Bluetooth, connect to BLE server in receiver, and get result.



