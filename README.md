# Addressable LED strip Wi-Fi controller

## NodeMCU

* Build and upload to ESP8266: https://nodemcu.readthedocs.io/en/master/build/
* Upload `init.lua` using https://github.com/andidittrich/NodeMCU-Tool:
  ```bash
  nodemcu-tool --port=/dev/tty.usbserial-1420 upload init.lua
  ```
  
## Arduino

* Change the PIN
* Compile and upload via PlatformIO

## Wi-Fi Configuration

* Add the power source
* Connect to an access point with the name starting as `LEDStripController`
* Set target AP settings
* Check that you have a new connected device

## Commands format

* Connect to the device: `telnet IP 22`
* Every command is in format `@123#00ffaa` where:
  * `@123` is the LED's number, starting from 0
  * `#00ffaa` is the desired color
* Batch mode is supported, e.g. `@0#00000f@1#000f00@2#0f0000`