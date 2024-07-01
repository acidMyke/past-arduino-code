#include <Servo.h>
#define LDR_0 A4
#define LDR_1 A5
#define ServoPin 9
Servo Pivot;

const int diffThres = 20;
const int threshold = 100;
const int centre = 90;
const int range = 30;

int value[2];
int angle = 180;

void setup() {
  Serial.begin(9600);
  Pivot.attach(ServoPin);
  Pivot.write(centre);
  delay(500);
}
void loop() {
  value[0] = analogRead(LDR_0);
  value[1] = analogRead(LDR_1);
  if (value[0] > threshold || value[1] > threshold) {
    int diff = abs(value[0] - value[1]);
    angle += ( diff > diffThres ? (value[0] > value[1] ? 1 : -1) : 0);
    angle = constrain(angle, 90 - range / 2, 90 + range / 2);
    Pivot.write(angle);
  }
  Serial.print("LDR_0: " + String(value[0]));
  Serial.print("\tLDR_1: " + String(value[1])):
  Serial.println("\tAngle: " + String(angle));
}
