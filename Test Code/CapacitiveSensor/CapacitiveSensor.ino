long readCap(uint8_t, uint8_t, uint64_t = 60000L);

void setup() {
  Serial.begin(115200);
}

void loop() {
  Serial.println(readCap(4, 5));
  delay(1000);
}

long readCap(uint8_t sendPin, uint8_t recPin, uint64_t timeout) {
  long count = 0;
  
  noInterrupts();
  digitalWrite(sendPin, LOW);  // send pin LOW
  pinMode(recPin, INPUT); // receive pin INPUT
  pinMode(recPin, OUTPUT); // receive pin OUTPUT
  digitalWrite(recPin, LOW); // receive pin LOW
  delayMicroseconds(10); // wait for 10us
  pinMode(recPin, INPUT); // receive pin INPUT
  digitalWrite(sendPin, HIGH);  // send pin HIGH
  interrupts();

  uint64_t elapsed = micros() + timeout;
  while (!digitalRead(recPin) && elapsed > micros()) count++;
  if (elapsed < micros()) return -2;

  noInterrupts();
  digitalWrite(recPin, HIGH); // receive pin HIGH
  pinMode(recPin, OUTPUT); // receive pin OUTPUT
  digitalWrite(recPin, HIGH); // receive pin HIGH
  pinMode(recPin, INPUT); // receive pin INPUT
  digitalWrite(sendPin, LOW);  // send pin LOW
  interrupts();

  pinMode(recPin, OUTPUT); // receive pin OUTPUT
  digitalWrite(recPin, LOW); // receive pin LOW
  delayMicroseconds(10); // wait for 10us
  pinMode(recPin, INPUT); // receive pin INPUT

  if (elapsed < micros()) return -2;
  else return count/1000;
}

