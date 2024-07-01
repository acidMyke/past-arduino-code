unsigned long oldMillis, t = 0; // t in seconds

void timer(int interval = 1000);

void setup() {
  oldMillis = millis();
  Serial.begin(115200);
  while(!Serial) delay(1);
}

void loop() {
  timer();
  if (Serial.available()) {
    String serial = Serial.readString();
    if (serial.indexOf("delay"))
      if (serial.substring(5).toInt())
        delay(serial.substring(5).toInt());
  }
}

void timer(int interval) {
  if (oldMillis < millis() - interval) {
    int diff = millis() - oldMillis;
    oldMillis = millis() - diff % interval;
    diff /= interval;
    t = t + diff;
    //Serial.print("\nMillis: " + String(millis()) + " t: " + String(t) + " Hours: " + String(time(0)) + " Minute: " + String(time(1)) + " Second: " + String(time(2)));
    //Serial.print("\n[" + String(millis()) + "] Time "  + String(time(0)) + ":" + String(time(1)) + ":" + String(time(2)));
    Serial.println("[" + String(micros()) + "]" + String(t));
  }
}
