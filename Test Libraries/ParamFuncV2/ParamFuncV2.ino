#include "ParamFunc.h"

ParamFunc<void> LEDHigh = new ParamFunc<void>(digitalWrite, (uint8_t)LED_BUILTIN, (uint8_t)HIGH);
ParamFunc<void> LEDLow = new ParamFunc<void>(digitalWrite, (uint8_t)LED_BUILTIN, (uint8_t)LOW);

void setup() {
  Serial.begin(9600);
}

void loop() {
  LEDHigh.run();
  LEDLow.run();
}

