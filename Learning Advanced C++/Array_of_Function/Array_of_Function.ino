void fx1();
void fx2();
void fx3();
void fx4();
void fx5();

void (*fx[5])() = {fx1, fx2, fx3, fx4, fx5};

String serial;
String keyword[5] = {"fx1", "fx2", "fx3", "fx4", "fx5"};

void setup() {
  Serial.begin(115200);
}

void loop() {
  if (Serial.available() > 0) {
    serial = Serial.readString();
  }
  if (serial != NULL) {
    for (int i = 0; i < 5; i++)
      if (serial.indexOf(keyword[i]) != -1){
        
        (*fx[i])();
      }
    serial.remove(0);
  }
  delay(500);
}

void fx1() {
  Serial.println("[" + String(millis()) +  "]" + "fx 1 is executed");
}

void fx2() {
  Serial.println("[" + String(millis()) +  "]" + "fx 2 is executed");
}

void fx3() {
  Serial.println("[" + String(millis()) +  "]" + "fx 3 is executed");
}

void fx4() {
  Serial.println("[" + String(millis()) +  "]" + "fx 4 is executed");
}

void fx5() {
  Serial.println("[" + String(millis()) +  "]" + "fx 5 is executed");
}
