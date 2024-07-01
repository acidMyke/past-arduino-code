void setup() {
  Serial.begin(9600);
}

void loop() {
  Serial.println("delayStart");
  Serial.print("Waiting ");
  Serial.println(delayWhile(10000, func, String("_")));
  Serial.println("\ndelayEnd");
  delay(1000);
}

template <typename ret, typename Arg> ret delayWhile(unsigned long ms, ret (*f)(Arg), Arg param) {
  ret retValue;
  unsigned long newTime = millis() + ms;
  while (millis() < newTime) {
    retValue += f(param);
  }
  return retValue;
}

int func(String s) {
  delay(500);
  return Serial.print(s);
}

