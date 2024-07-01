/*************************************************************
  Download latest Blynk library here:
    https://github.com/blynkkk/blynk-library/releases/latest

  Blynk is a platform with iOS and Android apps to control
  Arduino, Raspberry Pi and the likes over the Internet.
  You can easily build graphic interfaces for all your
  projects by simply dragging and dropping widgets.

    Downloads, docs, tutorials: http://www.blynk.cc
    Sketch generator:           http://examples.blynk.cc
    Blynk community:            http://community.blynk.cc
    Follow us:                  http://www.fb.com/blynkapp
                                http://twitter.com/blynk_app

  Blynk library is licensed under MIT license
  This example code is in public domain.

 *************************************************************

  This sketch shows how to read values from Virtual Pins

  App project setup:
    Slider widget (0...100) on Virtual Pin V1
 *************************************************************/
#define personalWiFi
/* Comment this out to disable prints and save space */
#define BLYNK_PRINT Serial

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <WiFiPassword.h>

#define forward V1
#define reversed V2
#define rotateLeft V3
#define rotateRight V4
#define extra1 V5
#define extra2 V6
#define terminalPin V10

int digitalPins[] = {14, 12, 13, 15};
int encodePin[] = {0, 16, 2};
//int encodeSqu[] = {{1, 0, 0}, {1, 1, 1}}
int pinValue[] = {0, 0, 0, 0, 0, 0};
int prePinValue[] = {0, 0, 0, 0, 0, 0};
int speed = 200;

String terminalRequest;

String functionKey[] = {"swap", "pin", "speed", "reset", "latch", "test"};
int function[] = {0, 0, 0, 0};
String pin[] = {"for", "rev", "left", "right"};
int pinRequest[] = {0, 0, 0, 0};

WidgetTerminal terminal(V10);

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "45824bcb16e5411ca021ef5539ff0076";

// This function will be called every time Slider Widget
// in Blynk app writes values to the Virtual Pin V1
BLYNK_WRITE(forward)
{
  pinValue[0] = param.asInt();
}

BLYNK_WRITE(reversed)
{
  pinValue[1] = param.asInt();
}

BLYNK_WRITE(rotateLeft)
{
  pinValue[2] = param.asInt();
}

BLYNK_WRITE(rotateRight)
{
  pinValue[3] = param.asInt();
}

BLYNK_WRITE(extra1)
{
  pinValue[4] = param.asInt();
}

BLYNK_WRITE(extra2)
{
  pinValue[5] = param.asInt();
}

BLYNK_WRITE(terminalPin)
{
  terminalRequest = param.asStr();
}
void setup()
{
  Serial.begin(115200);
  Blynk.begin(auth, ssid, password);
  for (int i = 0; i < 4; i++) {
    pinMode(digitalPins[i], OUTPUT);
    digitalWrite(digitalPins[i], LOW);
  }
}

void loop()
{
  Blynk.run();
  for (int i = 0; i < 4; i++) {
    digitalWrite(digitalPins[i], pinValue[i]);
    //analogWrite(digitalPins[i], map(pinValue[i], 0, 1, 0, speed));
  }
  for (int i = 0; i < 4; i++) {
    if (pinValue[i] != prePinValue[i]) {
      prePinValue[i] = pinValue[i];
      String state = "LOW";
      if (pinValue[i] == 1) {
        state = "HIGH";
      }
      if (pinValue[i] == 0) {
        state = "LOW";
      }
      Serial.println(pin[i] + " is " + state);
    }
  }
  if (terminalRequest != NULL)
    terminalRespone();
}

void terminalRespone() {
  String terminalBuffer = terminalRequest;
  Serial.println("Before Processing : " + terminalBuffer);
  terminalBuffer.toLowerCase();
  terminalBuffer.trim();
  Serial.println("After Processing : " + terminalBuffer);
  for (int i = 0; i < 4; i++) {
    if (terminalBuffer.indexOf(functionKey[i]) != -1) {
      function[i] = 1;
    }
  }
  if (function[0] == 1) {
    int x = 0;
    Serial.println("Function requested : " + functionKey[0]);
    for (int i = 0; i < 4; i++) {
      if (terminalBuffer.indexOf(pin[i]) != -1) {
        pinRequest[i] = 1;
        x++;
      }
      else {
        pinRequest[i] = 0;
      }
    }
    if (x == 2) {
      for (int i = 0; i < 4; i++) {
        if (pinRequest[i] == 1) {
          Serial.println("Pin Request : " + pin[i]);
          int pinBuffer = digitalPins[i];
          for (int a = i + 1; a < 4; a++ ) {
            if (pinRequest[a] == 1) {
              Serial.println("Pin Request : " + pin[a]);
              digitalPins[i] = digitalPins[a];
              digitalPins[a] = pinBuffer;
              function[0] = 0;
              terminalRequest.remove(0);
              return;
            }
          }
        }
      }
    }
    else {
      terminal.println("\nPlease only key in 2 pins");
      terminal.println("Please only key in 2 pins");
    }
  }
  if (function[1] == 1) {
    int x = 0;
    Serial.println("Function requested : " + functionKey[1]);
    for (int i = 0; i < 4; i++) {
      if (terminalBuffer.indexOf(pin[i]) != -1) {
        pinRequest[i] = 1;
        x++;
      }
      else {
        pinRequest[i] = 0;
      }
    }
    if (x == 1) {
      for (int i = 0; i < 4; i++) {
        if (pinRequest[i] == 1) {
          Serial.println("Pin Request : " + pin[i]);
          terminal.println(pin[i] + " is declared as " + String(digitalPins[i]) );
          Serial.println(pin[i] + " is declared as " + String(digitalPins[i]) );
          function[1] = 0;
          terminalRequest.remove(0);
          return;
        }
      }
    }
  }
  if(function[2] == 1){
    
  }
  delay(100);
}

