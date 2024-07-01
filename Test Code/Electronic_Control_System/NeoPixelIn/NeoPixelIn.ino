#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>
#endif
#define PIN            6
#define NUMPIXELS      20

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

int delayValue;
int r, g, b;
int inc;
int res = 4; // 8, 16, 32, 64, 128, 256

void pixelUpdate(uint32_t c = 0, uint8_t g = 0, uint8_t b = 0);

void setup() {
  Serial.begin(115200);
  pixels.begin();
}

void loop() {
  switch (inc) {
    case 0: for (r = 0; r < res; r++) pixelUpdate(); break;
    case 1: for (r = 0; r < res; r++) for (g = 0; g < res; g++) pixelUpdate(); break;
    case 2: for (r = 0; r < res; r++) for (g = 0; g < res; g++) for (b = 0; b < res; b++) pixelUpdate(); break;
    case 3: for (r = 0; r < res; r++) for (b = 0; b < res; b++) pixelUpdate(); break;
    case 4: for (r = 0; r < res; r++) for (b = 0; b < res; b++) for (g = 0; g < res; g++) pixelUpdate(); break;
    case 5: for (g = 0; g < res; g++) pixelUpdate(); break;
    case 6: for (g = 0; g < res; g++) for (b = 0; b < res; b++) pixelUpdate(); break;
    case 7: for (g = 0; g < res; g++) for (b = 0; b < res; b++) for (r = 0; r < res; r++) pixelUpdate(); break;
    case 8: for (g = 0; g < res; g++) for (r = 0; r < res; r++) pixelUpdate(); break;
    case 9: for (g = 0; g < res; g++) for (r = 0; r < res; r++) for (b = 0; b < res; b++) pixelUpdate(); break;
    case 10: for (b = 0; b < res; b++) pixelUpdate(); break;
    case 11: for (b = 0; b < res; b++) for (r = 0; r < res; r++) pixelUpdate(); break;
    case 12: for (b = 0; b < res; b++) for (r = 0; r < res; r++) for (g = 0; g < res; g++) pixelUpdate(); break;
    case 13: for (b = 0; b < res; b++) for (g = 0; g < res; g++) pixelUpdate(); break;
    case 14: for (b = 0; b < res; b++) for (g = 0; g < res; g++) for (r = 0; r < res; r++) pixelUpdate(); break;
  }
  r = g = b = 0;
  if (Serial.available() > 0) {
    String serial = Serial.readString();
    if (serial.startsWith("#")) {
      serial = serial.substring(1);
      serial.toUpperCase();
      uint32_t value;
      for (int i = 0; i < 6; i++) {
        value *= 16;
        switch (serial.charAt(i)) {
          case 48: value += 0; break; //DEC
          case 49: value += 1; break;
          case 50: value += 2; break;
          case 51: value += 3; break;
          case 52: value += 4; break;
          case 53: value += 5; break;
          case 54: value += 6; break;
          case 55: value += 7; break;
          case 56: value += 8; break;
          case 57: value += 9; break;
          case 65: value += 10; break; //Upper Case
          case 66: value += 11; break;
          case 67: value += 12; break;
          case 68: value += 13; break;
          case 69: value += 14; break;
          case 70: value += 15; break;
        }
      }
      for (int i = 0; i < NUMPIXELS; i++)
        pixelUpdate(value);
    }
    else if (serial.startsWith("RGB:")) {
      if (serial.charAt(4) == 32)
        serial = serial.substring(5);
      else
        serial = serial.substring(4);
      if (serial.indexOf(",") != -1) serial.replace(",", "");
      int32_t rawValue;
      if (serial.length() == 9) rawValue =  serial.toInt();
      else rawValue = -1;
      if (rawValue != -1)
        for (int i = 0; i < NUMPIXELS; i++)
          pixelUpdate(rawValue / 100000, (rawValue % 100000) / 100, rawValue / 100);
    }
    else if (serial.startsWith("C:")) {
      uint32_t value;
      if (serial.charAt(2) == 32)
        serial = serial.substring(3);
      else
        serial = serial.substring(2);
      if (serial.length() < 9)
        if (serial.toInt() != -1)
          value = serial.toInt();
      for (int i = 0; i < NUMPIXELS; i++)
        pixelUpdate(value);
    }
    else Serial.println("INVALID");
  }
}

void pixelUpdate(uint32_t c, uint8_t d, uint8_t e) {
  for (int i = NUMPIXELS - 1; i >= 0; i--) pixels.setPixelColor(i, pixels.getPixelColor(i - 1));
  if (c == 0) {
    int red = map(r, 0, res, 0, 256); 
    int green = map(g, 0, res, 0, 256);
    int blue = map(b, 0, res, 0, 256);
    Serial.println("#" + String(pixels.Color(red, green, blue), HEX));
    pixels.setPixelColor(0, pixels.Color(red, green, blue));
  }
  else if (d == 0 || e == 0) {
    Serial.println("#" + String(c, HEX));
    pixels.setPixelColor(0, c);
  }
  else {
    Serial.println("#" + String(pixels.Color(c, d, e), HEX));
    pixels.setPixelColor(0, c, d, e);
  }
  pixels.show();
  delay(map(analogRead(A0), 0, 1023, 5, 20));
}

