/*
  Keyboard test

  For the Arduino Leonardo, Micro or Due

  Reads a byte from the serial port, sends a keystroke back.
  The sent keystroke is one higher than what's received, e.g.
  if you send a, you get b, send A you get B, and so forth.

  The circuit:
   none

  created 21 Oct 2011
  modified 27 Mar 2012
  by Tom Igoe

  This example code is in the public domain.

  http://www.arduino.cc/en/Tutorial/KeyboardSerial
*/

#include "Keyboard.h"

String request;
String text;
unsigned long timer;
int timerEn;

void setup() {
  // open the serial port:
  Serial.begin(115200);
  // initialize control over the keyboard:
  Keyboard.begin();
  delay(1000);
  Serial.println("Ready");
}

void loop() {
  // check for incoming serial data
  if (Serial.available() > 0) {
    // read incoming serial data:
    request = Serial.readString();
    // Type the next ASCII value from what you received:
  }
  if (request != NULL) {
    Serial.println("RAW : " + request);
    request.trim();
    int index = request.lastIndexOf("\"");
    Serial.println("Text end at " + String(index));
    if (index != 0)
      text = request.substring(1, index);
    //Serial.println("Text to keyin is \"" + text + "\"" );
    request.remove(0, index + 1);
    //Serial.println("After removal of text " + request);
    request.trim();
    timer = request.toInt();
    Serial.println("Timer is " + String(timer));
    if (timer != 0) {
      timerEn = 1;
    }
    request.remove(0);
  }

  if (text != NULL) {
    if (timer != 0) {
      if (millis() % 10 == 0) {
        Serial.println("Timer : " + String(timer));
        timer--;
      }
    } else {
      if (timerEn == 1) {
        Serial.println("Ready");
        Keyboard.print(text);
        text.remove(0);
        timerEn = 0;
      } else if (timerEn == 0) {
        Serial.println("Please specify the time ...");
        while (Serial.available() == 0) {
          delay(10);
        }
      }
    }
  }
}

