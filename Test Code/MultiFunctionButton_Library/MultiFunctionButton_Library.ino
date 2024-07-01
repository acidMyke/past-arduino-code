#include "multiPress.h"

int buttonPin = 2;

multiPress button;

void setup() {
  if(!button.begin(buttonPin)) return;
}

void loop() {

}

