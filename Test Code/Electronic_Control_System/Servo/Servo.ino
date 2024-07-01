#include <Servo.h>

Servo s1, s2;

const String input;

void setup() {
  Serial.begin(115200);
  s1.attach(8);
  s2.attach(9);
}

void loop() {
  String input = Serial.readString();
  input.remove(input.indexOf("V"), 3);
  input.remove(input.indexOf("\tH"), 4);
  
  int h = analogRead(A0), v = analogRead(A1);
  Serial.println("V: " + String(v) + "\tH: " + String(h));
  h = map(h, 0, 1023, 0, 180);
  v = 180 - map(v, 0, 1023, 0, 180);
  s1.write(h);
  s2.write(v);
}
