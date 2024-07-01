void setup() {
  Serial.begin(9600);
}

void loop() {
  Serial.println("delayStart");
  Serial.print("Waiting ");
  delayWhile(10000, [](int i, int ii, int iii, int iiii) {
    Serial.println(i + ii + iii + iiii);
    delay(500);
  }, 2, 4, 6, 8);
  Serial.println("\ndelayEnd");
  delay(1000);
}

template <typename... Args> void delayWhile(unsigned long ms, void (*f)(Args...), Args... args) {
  unsigned long newTime = millis() + ms;
  while (millis() < newTime) {
    f(args...);
  }
}



