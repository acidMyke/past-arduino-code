#include "multiPress.h"

bool multiPress::begin(uint8_t pin, uint8_t maxCount, uint32_t timeout) {
  if (digitalPinToInterrupt(pin) == NOT_AN_INTERRUPT) return false;
  pinMode(pin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(pin), countPress, FALLING);
  _pin = pin;
  _maxCount = maxCount;
  _timeout = timeout;
}

static void multiPress::countPress() {
  detachInterrupt(digitalPinToInterrupt(_pin));
  pressCount = 1;
  while (!digitalRead(_pin)) delay(1);
  int oldMillis = millis() + _timeout;
  while (millis() < oldMillis && pressCount <= _maxCount)
    if (!digitalRead(_pin)) {
      oldMillis = millis();
      pressCount++;
      while (!digitalRead(_pin)) delay(1);
      pressTime = millis() - oldMillis;
      oldMillis = millis() + _timeout;
    }
  attachInterrupt(digitalPinToInterrupt(_pin), countPress, FALLING);
}

uint16_t multiPress::count(uint8_t useLongPress) {
  if (useLongPress == LONGPRESS) {
    if (pressTime != 0 && pressCount != 0) {
      word wordCount = word(pressTime / 1000, pressCount);
      pressTime = 0;
      pressCount = 0;
      return wordCount;
    }
  }
  else {
    if (pressCount != 0) {
      word wordCount = word(pressCount);
      pressTime = 0;
      pressCount = 0;
      return wordCount;
    }
  }
}

