int en = 9, in3 = 10, in4 = 11, sw = 2, led = LED_BUILTIN, mode = 0;

void setup() {
  pinMode(en, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(led, OUTPUT);
  pinMode(sw, INPUT);
}

void loop() {
  if (!digitalRead(sw)) {
    digitalWrite(led, HIGH);
    analogWrite(en, 255);
    
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);
    delay(10000);
    digitalWrite(in3, LOW);
    digitalWrite(in4, LOW);
    delay(1000);
    analogWrite(en, 150);
    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);
    delay(3000);
    digitalWrite(in3, LOW);
    digitalWrite(in4, LOW);
    delay(1000);
    analogWrite(en, 200);
    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);
    delay(7000);
    digitalWrite(in3, LOW);
    digitalWrite(in4, LOW);
    delay(1000);
  }
  else {
    digitalWrite(led, LOW);
    digitalWrite(in3, LOW);
    digitalWrite(in4, LOW);
    delay(1000);
  }
}
