#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>
#endif
#define PIN            6
#define NUMPIXELS      20

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

int delayValue;
int r, g, b;
int h, q, e;
int inc;
int res = ; // 8, 16, 32, 64, 128, 256

void setup() {
  Serial.begin(115200);
  pixels.begin();
}

void loop() {
  for (int i = NUMPIXELS - 1; i >= 0; i--) {
    pixels.setPixelColor(i, pixels.getPixelColor(i - 1));
  }
  int red = map(r, 0, res, 0, 255);
  int green = map(g, 0, res, 0, 255);
  int blue = map(b, 0, res, 0, 255);
  pixels.setPixelColor(0, red, green, blue);
  pixels.show();
  delay(map(analogRead(A0), 0, 1023, 5, 50));
  switch (inc) {
    case 0: r++; break;
    case 1: g++; break;
    case 2: b++; break;
    case 3: r++; g++; break;
    case 4: g++; b++; break;
    case 5: b++; r++; break;
    case 6: r++; g++; b++; break;
    case 7: h++; break;
    case 8: q++; break;
    case 9: e++; break;
    case 10: inc = 0; break;
  }
  switch (h) {
    
    default: h = 0; inc++; break;
  }
  if (r == res || g == res || b == res) {
    r = 0;
    g = 0;
    b = 0;
    inc++;
  }
}
