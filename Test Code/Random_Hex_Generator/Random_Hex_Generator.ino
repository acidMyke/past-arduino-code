void setup() {
  Serial.begin(115200);
  while(!Serial) delay(1);
}

void loop() {
  for (int a = 0; a < 6; a++) {
    //Serial.println(" ");
    //for (int y = 0; y < 3; y++) {
    //for (int x = 0; x < 128; x++) {
    //for (int i = 0; i < 3; i++) {
    String buffer;
    switch (random(0, 15)) {
      case 0: buffer = "0"; break;
      case 1: buffer = "1"; break;
      case 2: buffer = "2"; break;
      case 3: buffer = "3"; break;
      case 4: buffer = "4"; break;
      case 5: buffer = "5"; break;
      case 6: buffer = "6"; break;
      case 7: buffer = "7"; break;
      case 8: buffer = "8"; break;
      case 9: buffer = "9"; break;
      case 10: buffer = "A"; break;
      case 11: buffer = "B"; break;
      case 12: buffer = "C"; break;
      case 13: buffer = "D"; break;
      case 14: buffer = "E"; break;
      case 15: buffer = "F"; break;
    }
    Serial.print(buffer);
    //}
    //Serial.print(" ");
    //}
    //}
  }
  delay(500);
}

