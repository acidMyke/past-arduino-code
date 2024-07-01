const int trig = 2, echo = 3;

void setup() {
  Serial.begin(115200);
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  for (int i = 8; i <= 13; i++)
    pinMode(i, OUTPUT);
}

void loop() {
  int sensorValue = readPingDist();
  Serial.print("Distance: " + String(sensorValue) + " cm");
  if (sensorValue <= 50) {
    PORTB = ~(1 << (sensorValue / 10));
    Serial.println("\t\tLED: " + String(~PORTB, BIN));
  }
  else{
    PORTB = ~0;
    Serial.println();
  }
  delay(100);
}

uint32_t readPingDist() {
  digitalWrite(trig, HIGH);
  delayMicroseconds(11);
  digitalWrite(trig, LOW);
  int duration = pulseIn(echo, HIGH);
  return duration / 58.2;
}

