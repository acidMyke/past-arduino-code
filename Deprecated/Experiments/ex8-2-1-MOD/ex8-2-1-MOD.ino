const int stepPin[4] = {2, 3, 4, 5};
const int EN[2] = {6, 7};
const int SW[5] = {A0, A1, A2, A3, A4};

int i;

void setup() {
  Serial.begin(115200);
  delay(1000);
  for (int x = 0; x < 5; x++) {
    if (x < 2) {
      pinMode(EN[x], OUTPUT);
      digitalWrite(EN[x], LOW);
    }
    if (x < 4) {
      pinMode(stepPin[x], OUTPUT);
      digitalWrite(stepPin[x], LOW);
    }
    pinMode(SW[x], OUTPUT);
    digitalWrite(SW[x], LOW);
  }
}

void loop() {
  if (!digitalRead(SW[4])) {
    digitalWrite(EN[0], HIGH);
    digitalWrite(EN[1], HIGH);
    int y = i;
    if (digitalRead(SW[3])) y = 3 - y;
    switch (readThree()) {
      case B011: // 1 - Phase Scheme
        digitalWrite(stepPin[i], HIGH);
        delay(50);
        digitalWrite(stepPin[i], LOW);
        if (++i >= 4)  i = 0;
        break;
      case B101: //2 - Phase Scheme
        digitalWrite(stepPin[i], HIGH);
        digitalWrite(stepPin[i + 1], HIGH); //digitalWrite(stepPin[(i + 1) % 4], HIGH);
        delay(50);
        digitalWrite(stepPin[i], LOW);
        digitalWrite(stepPin[i + 1], LOW); //digitalWrite(stepPin[(i + 1) % 4], LOW);
        if (++i >= 4)  i = 0;
        break;
      case B110: //1/2 - Phase Scheme
        if (i % 2 == 0) {
          digitalWrite(stepPin[i / 2], HIGH);
          delay(50);
          digitalWrite(stepPin[i / 2], LOW);
        }
        else {
          digitalWrite(stepPin[i / 2], HIGH);
          digitalWrite(stepPin[i / 2 + 1], HIGH); //digitalWrite(stepPin[(i / 2 + 1) % 4], HIGH);
          delay(50);
          digitalWrite(stepPin[i / 2], LOW);
          digitalWrite(stepPin[i / 2 + 1], LOW); //digitalWrite(stepPin[(i / 2 + 1) % 4], LOW);
        }
        if (++i >= 8)  i = 0;
        break;
    }
    digitalWrite(EN[0], 0);    // disable drivers 1 and 2
    digitalWrite(EN[1], 0);    // disable drivers 3 and 4
  }
}

byte readThree() {
  byte value = B110;
  //for (int x = 0; x < 3; x++) bitWrite(value, x, digitalRead(SW[x]));
  Serial.println("SwitchThree() Value: B" + String(value, BIN));
  return value;
}


