int led = LED_BUILTIN;
uint64_t prevMillis;

void setup() {
  Serial.begin(115200);
  uint64_t prevMillis = millis();
}

void loop() {
  
}

void fx() {
  digitalWrite(led, digitalRead(led));
}


