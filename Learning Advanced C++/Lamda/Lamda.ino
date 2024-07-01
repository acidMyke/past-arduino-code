void setup() {
  Serial.begin(9600);
}

void loop() {
  Serial.println("delayStart");
  Serial.print("Waiting ");
  delayWhile(10000, [](String s){
    Serial.print(s);
    delay(500);
  }, "~");
  Serial.println("\ndelayEnd");
  delay(10000);
}

void delayWhile(unsigned long ms, void (*f)(String), String s){
  unsigned long newTime = millis() + ms;
  while(millis() < newTime){
    f(s);
  }
}

