double add(String str);
double subtract(String str);
double mutiply(String str);
double divide(String str);
double bracket(String str);

double (*fxOrder[5])(String str) = {bracket, divide, mutiply, add, subtract};

String serial;
String ky[5] = {"(", "/", "*", "+", "-"};

void setup() {
  Serial.begin(115200);
}

void loop() {
  if (Serial.available() > 0) {
    serial = Serial.readString();
  }
  if (serial != NULL) {
    for (int i = 0; i < 5; i++)
      if (serial.indexOf(ky[i]) != -1) {
        (*fxOrder[i])(serial);
        serial.remove(0);
      }
  }
  delay(500);
}

double add(String str) {
  
}

double subtract(String str) {

}

double mutiply(String str) {

}

double divide(String str) {

}

double bracket(String str) {

}
