// NeoPixel Ring simple sketch (c) 2013 Shae Erisson
// released under the GPLv3 license to match the rest of the AdaFruit NeoPixel library

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>
#endif

// Which pin on the Arduino is connected to the NeoPixels?
#define PIN            6

// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS      20

// When we setup the NeoPixel library, we tell it how many pixels, and which pin to use to send signals.
// Note that for older NeoPixel strips you might need to change the third parameter--see the strandtest
// example for more information on possible values.
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

int delayval = 10; // delay for half a second
int bright;

void setup() {
  Serial.begin(115200);
  // This is for Trinket 5V 16MHz, you can remove these three lines if you are not using a Trinket
#if defined (__AVR_ATtiny85__)
  if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
#endif
  // End of trinket special code

  pixels.begin(); // This initializes the NeoPixel library.
}

void loop() {

  // For a set of NeoPixels the first NeoPixel is 0, second is 1, all the way up to the count of pixels minus one.
  /*
    for(int i=0;i<NUMPIXELS;i++){

      // pixels.Color takes RGB values, from 0,0,0 up to bright,bright,bright
      pixels.setPixelColor(i, pixels.Color(150,0,0)); // Moderately bright green color.

      pixels.show(); // This sends the updated pixel color to the hardware.

      delay(delayval); // Delay for a period of time (in milliseconds).

    }

    for(int i=0;i<NUMPIXELS;i++){

      // pixels.Color takes RGB values, from 0,0,0 up to bright,bright,bright
      pixels.setPixelColor(i, pixels.Color(0,150,0)); // Moderately bright green color.

      pixels.show(); // This sends the updated pixel color to the hardware.

      delay(delayval); // Delay for a period of time (in milliseconds).

    }

    for(int i=0;i<NUMPIXELS;i++){

      // pixels.Color takes RGB values, from 0,0,0 up to bright,bright,bright
      pixels.setPixelColor(i, pixels.Color(0,0,150)); // Moderately bright green color.

      pixels.show(); // This sends the updated pixel color to the hardware.

      delay(delayval); // Delay for a period of time (in milliseconds).

    }

    for(int i=0;i<NUMPIXELS;i++){

      // pixels.Color takes RGB values, from 0,0,0 up to bright,bright,bright
      pixels.setPixelColor(i, pixels.Color(150,150,0)); // Moderately bright green color.

      pixels.show(); // This sends the updated pixel color to the hardware.

      delay(delayval); // Delay for a period of time (in milliseconds).

    }
    for(int i=0;i<NUMPIXELS;i++){

      // pixels.Color takes RGB values, from 0,0,0 up to bright,bright,bright
      pixels.setPixelColor(i, pixels.Color(0,150,150)); // Moderately bright green color.

      pixels.show(); // This sends the updated pixel color to the hardware.

      delay(delayval); // Delay for a period of time (in milliseconds).

    }
    for(int i=0;i<NUMPIXELS;i++){

      // pixels.Color takes RGB values, from 0,0,0 up to bright,bright,bright
      pixels.setPixelColor(i, pixels.Color(150,0,150)); // Moderately bright green color.

      pixels.show(); // This sends the updated pixel color to the hardware.

      delay(delayval); // Delay for a period of time (in milliseconds).

    }
    for(int i=0;i<NUMPIXELS;i++){

      // pixels.Color takes RGB values, from 0,0,0 up to bright,bright,bright
      pixels.setPixelColor(i, pixels.Color(150,150,150)); // Moderately bright green color.

      pixels.show(); // This sends the updated pixel color to the hardware.

      delay(delayval); // Delay for a period of time (in milliseconds).

    }*/
  bright = map(analogRead(A0), 0, 1023, 50, 150 );
  delayval = map(analogRead(A1), 0, 1023, 5, 100);

  for (int i = 0; i < NUMPIXELS; i++) {
    // pixels.Color takes RGB values, from 0,0,0 up to bright,bright,bright
    pixels.setPixelColor(i, pixels.Color(bright, 0, 0)); // Moderately bright green color.
    pixels.show(); // This sends the updated pixel color to the hardware.
    delay(delayval); // Delay for a period of time (in milliseconds).
  }
  bright = map(analogRead(A0), 0, 1023, 50, 150 );
  delayval = map(analogRead(A1), 0, 1023, 5, 100);
  for (int i = 0; i < NUMPIXELS; i++) {
    // pixels.Color takes RGB values, from 0,0,0 up to bright,bright,bright
    pixels.setPixelColor(i, pixels.Color(0, bright, 0)); // Moderately bright green color.
    pixels.show(); // This sends the updated pixel color to the hardware.
    delay(delayval); // Delay for a period of time (in milliseconds).
  }
  bright = map(analogRead(A0), 0, 1023, 50, 150 );
  delayval = map(analogRead(A1), 0, 1023, 5, 100);
  for (int i = 0; i < NUMPIXELS; i++) {
    // pixels.Color takes RGB values, from 0,0,0 up to bright,bright,bright
    pixels.setPixelColor(i, pixels.Color(0, 0, bright)); // Moderately bright green color.
    pixels.show(); // This sends the updated pixel color to the hardware.
    delay(delayval); // Delay for a period of time (in milliseconds).
  }
  bright = map(analogRead(A0), 0, 1023, 50, 150 );
  delayval = map(analogRead(A1), 0, 1023, 5, 100);
  for (int i = 0; i < NUMPIXELS; i++) {
    // pixels.Color takes RGB values, from 0,0,0 up to bright,bright,bright
    pixels.setPixelColor(i, pixels.Color(bright, bright, 0)); // Moderately bright green color.
    pixels.show(); // This sends the updated pixel color to the hardware.
    delay(delayval); // Delay for a period of time (in milliseconds).
  }
  bright = map(analogRead(A0), 0, 1023, 50, 150 );
  delayval = map(analogRead(A1), 0, 1023, 5, 100);
  for (int i = 0; i < NUMPIXELS; i++) {
    // pixels.Color takes RGB values, from 0,0,0 up to bright,bright,bright
    pixels.setPixelColor(i, pixels.Color(bright, 0, bright)); // Moderately bright green color.
    pixels.show(); // This sends the updated pixel color to the hardware.
    delay(delayval); // Delay for a period of time (in milliseconds).
  }
  bright = map(analogRead(A0), 0, 1023, 50, 150 );
  delayval = map(analogRead(A1), 0, 1023, 5, 100);
  for (int i = 0; i < NUMPIXELS; i++) {
    // pixels.Color takes RGB values, from 0,0,0 up to bright,bright,bright
    pixels.setPixelColor(i, pixels.Color(0, bright, bright)); // Moderately bright green color.
    pixels.show(); // This sends the updated pixel color to the hardware.
    delay(delayval); // Delay for a period of time (in milliseconds).
  }
  bright = map(analogRead(A0), 0, 1023, 50, 150 );
  delayval = map(analogRead(A1), 0, 1023, 5, 100);
  for (int i = 0; i < NUMPIXELS; i++) {
    // pixels.Color takes RGB values, from 0,0,0 up to bright,bright,bright
    pixels.setPixelColor(i, pixels.Color(bright, bright, bright)); // Moderately bright green color.
    pixels.show(); // This sends the updated pixel color to the hardware.
    delay(delayval); // Delay for a period of time (in milliseconds).
  }
  if (Serial.available() > 0) {
    String serial = Serial.readString();
    Serial.println(serial);
    int r = serial.substring(serial.indexOf("r:") + 2, serial.indexOf("g:")).toInt(), g = serial.substring(serial.indexOf("g:") + 2, serial.indexOf("b:")).toInt(), b = serial.substring(serial.indexOf("b:") + 2).toInt();
    if (r != -1 && g != -1 && b != -1)
      for (int i = 0; i < NUMPIXELS; i++) {
        // pixels.Color takes RGB values, from 0,0,0 up to bright,bright,bright
        pixels.setPixelColor(i, pixels.Color(r, g, b)); // Moderately bright green color.
        pixels.show(); // This sends the updated pixel color to the hardware.
        delay(delayval); // Delay for a period of time (in milliseconds).
      }
      else
        Serial.println("Invalid!!!!");
    delay(5000);
  }

}
