#include <Arduino.h>
#include <HardwareSerial.h>
#include <WS2812.h>

const unsigned short CONTROLLER_PIN = PIND2;
WS2812 *LED = nullptr;
long lastNumberOfLeds = 0;

void initLed(long numberOfLeds, short pin) {
  delete LED;

  LED = new WS2812(numberOfLeds);
  LED->setOutput(pin);
}

void setup() {
  Serial.begin(115200);
}

void loop() {
  // Nothing, only serial events
}

int process(const String &data) {
  // @0#000f0f
  const int colorStart = data.indexOf('#');
  long index = data
    .substring(1, colorStart)
    .toInt();
  const String rgbHexString = data.substring(3);
  const long referredNumber = index + 1;

  if (referredNumber > lastNumberOfLeds) {
    initLed(referredNumber, CONTROLLER_PIN);
    lastNumberOfLeds = referredNumber;
  }

  const String red = rgbHexString.substring(0, 2);
  const String green = rgbHexString.substring(2, 4);
  const String blue = rgbHexString.substring(4, 6);

  char *ptr;

  cRGB color = {
    (uint8_t) strtoul(green.begin(), &ptr, 16),
    (uint8_t) strtoul(red.begin(), &ptr, 16),
    (uint8_t) strtoul(blue.begin(), &ptr, 16)
  };

  LED->set_crgb_at(index, color);
  LED->sync();

  return colorStart + 7; // Total number of consumed chars
}

void serialEvent() {
  String data = Serial.readStringUntil('\n');

  // @0#00000f@1#000f00@2#0f0000
  while (data.indexOf('@') > -1) {
    data = data.substring(data.indexOf('@'));
    data = data.substring(process(data));
  }
}