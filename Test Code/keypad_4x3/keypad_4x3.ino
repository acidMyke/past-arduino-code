const int keypad[] = {14, 13, 12, 4, 5, 2, 16};

void setup() {
  Serial.begin(115200);
  for (int i = 0; i < 7; i++) {
    if (i < 3){
      pinMode(keypad[i], OUTPUT);
      digitalWrite(keypad[i], HIGH);
    }
    else {
      pinMode(keypad[i], INPUT_PULLUP);
    }
  }
}

void loop() {
  Serial.println("Value: " + String(readButton()));
  delay(250);
}

int readButton() {
  int value = 0;
  while (value == 0) {
    for (int x = 0; x < 3; x++) {
      digitalWrite(keypad[x], LOW);
      for (int y = 6; y >= 3; y--) {
        if (digitalRead(keypad[y]) == LOW) {
          value = x + (6 - y) * 3 + 1;
        }
      }
      digitalWrite(keypad[x], HIGH);
    }
    delay(10);
  }
  return value;
}


