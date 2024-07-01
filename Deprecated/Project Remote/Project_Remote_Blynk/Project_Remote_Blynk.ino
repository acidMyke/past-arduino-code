/**************************************************************
   Blynk is a platform with iOS and Android apps to control
   Arduino, Raspberry Pi and the likes over the Internet.
   You can easily build graphic interfaces for all your
   projects by simply dragging and dropping widgets.

     Downloads, docs, tutorials: http://www.blynk.cc
     Sketch generator:           http://examples.blynk.cc
     Blynk community:            http://community.blynk.cc
     Social networks:            http://www.fb.com/blynkapp
                                 http://twitter.com/blynk_app

   Blynk library is licensed under MIT license
   This example code is in public domain.

 **************************************************************
   This example runs directly on ESP8266 chip.

   Note: This requires ESP8266 support package:
     https://github.com/esp8266/Arduino

   Please be sure to select the right ESP8266 module
   in the Tools -> Board menu!

   Change WiFi ssid, pass, and Blynk auth token to run :)

 **************************************************************/

#define BLYNK_PRINT Serial


#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <IRremoteESP8266.h>

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "bfe048b3904049a7992a21f356b0dbdb";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "Yong";
char pass[] = "yong1020";

boolean button1 = false;
boolean button2 = false;
boolean button3 = false;
boolean button4 = false;
boolean mouseActive = false;
boolean shiftActive = false;

int onOnce = 0;
IRsend irsend(14);

void setup(){
  Serial.begin(115200);
  Blynk.begin(auth, ssid, pass);
  pinMode(14, OUTPUT);
}
void loop(){
  Blynk.run();
  if(mouseActive == false && shiftActive == false){
    while(onOnce == 1){irsend.sendNEC(0x2FF2AD5, 32); onOnce = 0; Serial.println("Mouse OFF");}
    onOnce = 0;
    if(button1 == true){
      irsend.sendNEC(0x2FFB24D, 32); //Power
      Serial.println("Power");
    }else if(button2 == true){
      irsend.sendNEC(0x2FFA857, 32); // Vol Up
      Serial.println("Vol Up");
    }else if(button3 == true){
      irsend.sendNEC(0x2FF38C7, 32); //Vol Down  
      Serial.println("Vol Down");
    }else if(button4 == true){
      irsend.sendNEC(0x2FFB04F, 32); //OK
      Serial.println("OK");
    }
  }else if(mouseActive == true && shiftActive == false){
    while(onOnce == 0){irsend.sendNEC(0x2FF2AD5, 32); onOnce = 1; Serial.println("Mouse ON");}
    if(button1 == true){
      irsend.sendNEC(0x2FFD02F, 32); //Up
      Serial.println("Mouse Up");
    }else if(button2 == true){
      irsend.sendNEC(0x2FF708F, 32); //Down
      Serial.println("Mouse Down");
    }else if(button3 == true){
      irsend.sendNEC(0x2FF08F7, 32); //Left
      Serial.println("Mouse Left");
    }else if(button4 == true){
      irsend.sendNEC(0x2FF8877, 32); //Right
      Serial.println("Mouse Right");
    }
  }else if(mouseActive == false && shiftActive == true){
    while(onOnce == 1){irsend.sendNEC(0x2FF2AD5, 32); onOnce = 0; Serial.println("Mouse OFF");}
    if(button1 == true){
      irsend.sendNEC(0x2FF58A7, 32); // Home
      Serial.println("Home");
    }else if(button2 == true){
      irsend.sendNEC(0x2FF22DD, 32); //Settings
      Serial.println("Settings");
    }else if(button3 == true){
      irsend.sendNEC(0x2FFA25D, 32); //Menu
      Serial.println("Menu");
    }else if(button4 == true){
      irsend.sendNEC(0x2FF42BD, 32); //Return
      Serial.println("Return");
    }
  }else if(mouseActive == true && shiftActive == true){
    while(onOnce == 1){irsend.sendNEC(0x2FF2AD5, 32); onOnce = 0; Serial.println("Mouse OFF");}
    if(button1 == true){
      irsend.sendNEC(0x2FFD02F, 32); //Up
      Serial.println("Up");
    }else if(button2 == true){
      irsend.sendNEC(0x2FF708F, 32); //Down
      Serial.println("Down");
    }else if(button3 == true){
      irsend.sendNEC(0x2FF08F7, 32); //Left
      Serial.println("Left");
    }else if(button4 == true){
      irsend.sendNEC(0x2FF8877, 32); //Right
      Serial.println("Right");
    }
  }
  delay(100);
}

BLYNK_WRITE(V1)
{
  button1 = param.asInt(); // assigning incoming value from pin V1 to a variable
  // You can also use:
  // String i = param.asStr();
  // double d = param.asDouble();
  Serial.print("V1 Slider value is: ");
  Serial.println(button1);
}
BLYNK_WRITE(V2)
{
  button2 = param.asInt(); // assigning incoming value from pin V1 to a variable
  // You can also use:
  // String i = param.asStr();
  // double d = param.asDouble();
  Serial.print("V2 Slider value is: ");
  Serial.println(button2);
}
BLYNK_WRITE(V3)
{
  button3 = param.asInt(); // assigning incoming value from pin V1 to a variable
  // You can also use:
  // String i = param.asStr();
  // double d = param.asDouble();
  Serial.print("V3 Slider value is: ");
  Serial.println(button3);
}
BLYNK_WRITE(V4)
{
  button4 = param.asInt(); // assigning incoming value from pin V1 to a variable
  // You can also use:
  // String i = param.asStr();
  // double d = param.asDouble();
  Serial.print("V4 Slider value is: ");
  Serial.println(button4);
}
BLYNK_WRITE(V5)
{
  mouseActive = param.asInt(); // assigning incoming value from pin V1 to a variable
  // You can also use:
  // String i = param.asStr();
  // double d = param.asDouble();
  Serial.print("V5 Slider value is: ");
  Serial.println(mouseActive);
}
BLYNK_WRITE(V6)
{
  shiftActive = param.asInt(); // assigning incoming value from pin V1 to a variable
  // You can also use:
  // String i = param.asStr();
  // double d = param.asDouble();
  Serial.print("V6 Slider value is: ");
  Serial.println(shiftActive);
}





















