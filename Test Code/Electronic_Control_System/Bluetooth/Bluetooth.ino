#include <SoftwareSerial.h>

SoftwareSerial BT(2, 3);

int Default = 0; //0: Serial, 1: Bluetooth
String serial;

void setup() {
  Serial.begin(115200);
  BT.begin(9600);
  BT.print("AT\r\n");
  int oldMillis = millis() + 5000;
  while (BT.available() == 0 && oldMillis > millis()) delay(1);
  if (!(BT.available() == 0 && BT.readString().indexOf("OK") )) return;
  else Serial.println("Wrong bluetooth settings");
}

void loop() {
  
}

void UARTCom(){
  if (Serial.available()) {
    String str = Serial.readString();
    Serial.println("Serial: " + str);
    if (str == "Default: 1") Default = 1;
    else if (str == "Default: 0") Default = 0;
    else if (!Default)
      if (str.startsWith("BT: ")) BT.println(str.substring(4));
      else serial = str;
    else if (Default)
      if (str.startsWith("String")) serial = str;
      else BT.println(str.substring(4));
  }
  if (BT.available()){
    String str = Serial.readString();
    Serial.println("BT-> " + str);
    if (str.startsWith("Serial: ")) Serial.println(str.substring(8));
    else commands(str);
  }
}

void commands(String str){
  if (str == "Button 1");
  else if (str == "Button 2");
  else if (str == "Button 3");
  else if (str == "Button 4");
  else if (str == "Button 5");
  else ;
}


