#include "DumbClass.h"

void setup() {
  Serial.begin(9600);
  Serial.println(Dumb::add(5, 6, 7, 5, 9, 6, 1, 12, 3, 45, 6, 3));
}

void loop() {
  
}
