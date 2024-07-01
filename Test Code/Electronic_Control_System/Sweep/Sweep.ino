/* Sweep
  by BARRAGAN <http://barraganstudio.com>
  This example code is in the public domain.

  modified 8 Nov 2013
  by Scott Fitzgerald
  http://www.arduino.cc/en/Tutorial/Sweep
*/

#include <Servo.h>

Servo servo[2];

boolean state = 0;    // variable to store the servo position
int value[64];
int i = 1;

void setup() {
  Serial.begin(9600);
  pinMode(2, INPUT_PULLUP);
  pinMode(3, INPUT_PULLUP);
  servo[0].attach(9);  // attaches the servo on pin 9 to the servo object
  servo[1].attach(8);  // attaches the servo on pin 9 to the servo object
}

void loop() {
  if (!digitalRead(2)) {
    for (int x = 0; x < (sizeof(value)/sizeof(); x++) {
      int newValue = ((180 - map(analogRead(A0), 0, 1024, 0, 180)) * 180) + (map(analogRead(A1), 0, 1024, 0, 180));
      servo[0].write(newValue / 180);
      servo[1].write(newValue % 180);
      value[x] = newValue;
      Serial.println("Record: " + String(x) + ": " + String(newValue / 180) + "\t" + String(newValue % 180));
      delay(50);
    }
    i = 0;
  }
  //Serial.println(String(newValue / 180) + "\t\t" + String(newValue % 180));
  int x = 0;
  if (!digitalRead(3)) {
    for (int x = 0; x < 64; x++) {
      if (value[x] == 0) break;
      Serial.println("Run: " + String(x) + ": " + String(value[x] / 180) + "\t" + String(value[x] % 180));
      servo[0].write(value[x] / 180);
      servo[1].write(value[x] % 180);
      delay(50);
      value[x] = 0;
    }
    i = 0;
  }
  delay(50);
}

