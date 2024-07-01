#include "Keyboard.h"

const int inputPin[4] = {4, 3, 2, 1};
const int outputPin[3] = {5, 6, 7};

const bool logic = LOW;

int value = 0;

String c[13] = {"", "1", "2", "3", "4", "5", "6", "7", "8", "9", "*", "0", "#"};

void setup() {
  Serial.begin(115200);
  Keyboard.begin();
  while (!Serial);
  for (int x = 0; x < 3; x++) {
    pinMode(outputPin[x], OUTPUT);
    digitalWrite(outputPin[x], logic);
  }
  for (int y = 0; y < 4; y++)
    pinMode(inputPin[y], INPUT);
}

void loop() {
  for (int x = 0; x < 3; x++) {
    digitalWrite(outputPin[x], !logic);
    for (int y = 0; y < 4; y++) {
      if (digitalRead(inputPin[y]) == !logic && value == 0)value = x + y * 3 + 1 ;
    }
    digitalWrite(outputPin[x], logic);
  }
  if (value != 0){
    Serial.println("Value: " + String(value) + "\t It represent: " + c[value]);
    Keyboard.print(c[value]);
  }
  value = 0;
  delay(100);
}
