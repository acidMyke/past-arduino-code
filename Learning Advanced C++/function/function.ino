int x = 400;

void setup() {
  Serial.begin(115200);
  Serial.println(x);
  Serial.println(decrement(x));
  Serial.print("Ended");
}

void loop() {
  delay(10);
}

int decrement(int i) {
  i--;
  Serial.println(i);
  if (i > 4)
    decrement(i);
    //return 0;
  else
    Serial.println("ERR");
}

