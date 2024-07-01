#include "ParseData.h"

void setup(){
  Serial.begin(115200);
  delay(100);
  Data.begin(generate);
}

void loop(){
  switch (random(0, 5)){
    case 0: 
      Serial.println("Byte: " + String(Data.toByte()));
    break;
    
    case 1: 
      Serial.println("Char: " + String(Data.toChar()));
    break;
    
    case 2: 
      Serial.println("Unsigned Int: " + String(Data.toUInt()));
    break;
    
    case 3: 
      Serial.println("Int: " + String(Data.toInt()));
    break;
    
    case 4: 
      Serial.println("Unsigned Long: " + String(Data.toULong()));
    break;

    case 5: 
      Serial.println("Long: " + String(Data.toLong()));
    break;
  }
  delay(1000);
}

int generate(){
  byte num = random(0, 255);
  Serial.println("Generate: " + Byte(num));
  return (int)num;
}

String Byte(byte b){
  String str = String(b, BIN);
  switch (str.length()){
    case 1: str = "0000000" + str; break;
    case 2: str = "000000" + str; break;
    case 3: str = "00000" + str; break;
    case 4: str = "0000" + str; break;
    case 5: str = "000" + str; break;
    case 6: str = "00" + str; break;
    case 7: str = "0" + str; break;
    case 8: str = str; break;
  }
  return str;
}

