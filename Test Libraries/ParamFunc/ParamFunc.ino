#include "ParamFunc.h"

ParamFunc<size_t> HW = ParamFunc<size_t>(static_cast<size_t*(String)>(Serial.println), String("Hello"));;
void setup() {
  Serial.begin(9600);
}

void loop() {
  HW();
}

