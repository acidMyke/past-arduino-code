unsigned long oldMicros[5];
unsigned long interval = 5000000;
int button = 2;
/*
void begin(int _button = 2, int _state = HIGH, int _mode = INPUT_PULLUP);
void buttonDec();
int get();
*/
void setup() {
  Serial.begin(115200);
  begin();
}

void loop() {
  switch (get()) {
    case 0:
      Serial.println("You didn't press the button");
      break;
    case 1:
      Serial.println("You pressed the button one time");
      break;
    case 2:
      Serial.println("You pressed the button two times");
      break;
    case 3:
      Serial.println("You pressed the button three times");
      break;
    case 4:
      Serial.println("You pressed the button four times");
      break;
    case 5:
      Serial.println("You pressed the button five times");
      break;
  }
}
/*
void begin(int _button = 2, int _state = HIGH, int _mode = INPUT_PULLUP){
  pinMode(_button, _mode);
  attachInterrupt(digitalPinToInterrupt(_button), buttonDec, _state);
}

int get() {
  int _functionNo;
  for (int i = 1; i < 5; i++) {
    if (oldMicros[i - 1] > oldMicros[i] && micros() - interval > oldMicros[i]) {
      _functionNo = i;
      for (int i = 0; i < 5; i++) {
        oldMicros[i] = 0;
      }
    }
    else {
      _functionNo = 0;
    }
  }
  return _functionNo;
}

void buttonDec() {
  if (oldMicros[0] == 0) {
    oldMicros[0] = micros();
  }
  else if (oldMicros[1] == 0 && micros() - interval < oldMicros[0]) {
    oldMicros[1] = micros();
  }
  else if (oldMicros[2] == 0 && micros() - interval < oldMicros[1]) {
    oldMicros[2] = micros();
  }
  else if (oldMicros[3] == 0 && micros() - interval < oldMicros[2]) {
    oldMicros[3] = micros();
  }
  else if (oldMicros[4] == 0 && micros() - interval < oldMicros[3]) {
    oldMicros[4] = micros();
  }
}
*/
