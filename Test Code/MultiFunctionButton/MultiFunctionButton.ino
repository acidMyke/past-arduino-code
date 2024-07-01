int button = 2;

void setup() {
  attachInterrupt(digitalPinToInterrupt(button), readButton, FALLING);
}

void loop() {

}

void readButton() {
  int i = 0;
  void (*event[])() = {event0, event1, event2, event3}; 
  detachInterrupt(digitalPinToInterrupt(button));
  while (digitalRead(button) == LOW & i < 4) delay(1);
  int oldMillis = millis();
  while (oldMillis > millis() - 5000) {
    if (digitalRead(button) == LOW) {
      i++;
      while (digitalRead(button) == LOW) delay(1);
      oldMillis = millis();
    }
  }
  event[i]();
  attachInterrupt(digitalPinToInterrupt(button), readButton, FALLING);
}

void event0() {
  
}

void event1(){
  
}

void event2(){
  
}

void event3(){
  
}

