#include "Arduino.h"
#include "MultiFunction.h"

void MultiFunction::begin(int pin, int interval = 5000, int state = HIGH, int mode = INPUT_PULLUP) {
  pinMode(pin , mode);
  attachInterrupt(digitalPinToInterrupt(pin), buttonDec, state);
  _interval = interval;
}

int MultiFunction::get() {
  int functionNo;
  for (int i = 1; i < 5; i++) {
    if (oldMicros[i - 1] > oldMicros[i] && micros() - _interval > oldMicros[i]) {
      functionNo = i;
      for (int i = 0; i < 5; i++) {
        oldMicros[i] = 0;
      }
    }
    else {
      functionNo = 0;
    }
  }
  return functionNo;
}

void buttonDec() {
  if (oldMicros[0] == 0) {
    oldMicros[0] = micros();
  }
  else if (oldMicros[1] == 0 && micros() - _interval < oldMicros[0]) {
    oldMicros[1] = micros();
  }
  else if (oldMicros[2] == 0 && micros() - _interval < oldMicros[1]) {
    oldMicros[2] = micros();
  }
  else if (oldMicros[3] == 0 && micros() - _interval < oldMicros[2]) {
    oldMicros[3] = micros();
  }
  else if (oldMicros[4] == 0 && micros() - _interval < oldMicros[3]) {
    oldMicros[4] = micros();
  }
}

