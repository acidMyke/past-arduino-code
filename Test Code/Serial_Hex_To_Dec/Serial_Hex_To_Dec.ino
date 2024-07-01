word value[3][16][8];

String serialData;

int oldmillis;

void setup() {
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);
}

void loop() {
  if (Serial.available() > 0) {
    serialData = Serial.readStringUntil('\n');
  }

  if (serialData != NULL) {
    oldmillis = millis();
    Serial.println("[" + String(millis()) + "]");
    Serial.println(serialData);
    for (int rgb = 0; rgb < 3 ; rgb++) {
      for (int x = 0; x < 16; x++) {
        for (int y = 0; y < 8; y++) {
          int i = (rgb * 128) + (x * 8) + y;
          //Serial.println(serialData.substring((i * 4) + 1, (i + 1) * 4 ));
          value[rgb][x][y] = strToValue(serialData.substring((i * 4) + 1, (i + 1) * 4 ));
        }
      }
    }
    //Serial.println("Value of rgb  :\n");
    for (int rgb = 0; rgb < 3 ; rgb++) {
      for (int x = 0; x < 16; x++) {
        for (int y = 0; y < 8; y++) {
          if(value[rgb][x][y] > 4905){
          Serial.println("Shit");
          digitalWrite(LED_BUILTIN, LOW);
          }
          //else
          //Serial.println(String(value[rgb][x][y]));
        }
      }
    }
    serialData.remove(0, 1538);
    Serial.println("Time taken to convert : " + String(millis() - oldmillis));
  }
}

word strToValue(String str) {
  word hex[3];
  for (int i = 0; i < 3; i++) {
    int buffer;
    switch (str.charAt(i)) {
      case 48: buffer = 0; break;
      case 49: buffer = 1; break;
      case 50: buffer = 2; break;
      case 51: buffer = 3; break;
      case 52: buffer = 4; break;
      case 53: buffer = 5; break;
      case 54: buffer = 6; break;
      case 55: buffer = 7; break;
      case 56: buffer = 8; break;
      case 57: buffer = 9; break;
      case 65: buffer = 10; break;
      case 66: buffer = 11; break;
      case 67: buffer = 12; break;
      case 68: buffer = 13; break;
      case 69: buffer = 14; break;
      case 70: buffer = 15; break;
    }
    hex[i] = buffer;
  }
  word decimal = (hex[0]*16*16) + (hex[1]*16) + (hex[2]);
  return decimal;
}
