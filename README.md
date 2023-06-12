# A Gateway using Xbee

In this repository, I make a communication between two microcontrollers using XBee protocol, then sending frames to phone through Bluetooth Low Energy (BLE). 

![image](https://github.com/nub-atur/simple-xbee-gateway/assets/136115054/38464109-f88d-4a5b-aa67-736b78088385)

Components:
  - NODEMCU ESP32
  - module XBee S2C (with module board base shield for easily serial connecting)
  - DHT22 Sensor Module 
  - A phone has been installed [nRF Connect](https://play.google.com/store/apps/details?id=no.nordicsemi.android.mcp&hl=en_US&pli=1)

# XBee® ZigBee Network Configuration
- Install [XCTU](http://www.digi.com/products/wireless-wired-embedded-solutions/zigbee-rf-modules/xctu).
- Use `XCTU` for installing the firmware to the `XBee®` devices.
- `XBee® ZigBee` network must have only one `Coordinator`.
- All other devices in the network must be `XBee® ZigBee End Device` or `XBee® ZigBee Router`. Here, the second xbee is configured as a router.

