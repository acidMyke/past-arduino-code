int enable2 = 9;
int in3 = 10;
int in4 = 11;
int swPin = 2;
int ledPin = 13;
int swState = 0;
int mode = 0;
int speed = 255;

void setup() {
  pinMode(enable2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(ledPin, OUTPUT);
  pinMode(swPin, INPUT);
}

void loop() {
  swState = digitalRead(swPin);
  if (swState == HIGH) {
    switch ( mode ) {
      case 0:
      break;
      case 1:
      break;
    }
    digitalWrite(in3, LOW);
    digitalWrite(in4, LOW);
    delay(1000);
  }
  else {
    digitalWrite(ledPin, LOW);
    digitalWrite(in3, LOW);
    digitalWrite(in4, LOW);
    delay(1000);
  }
}

void serialEvent() {
  char c = Serial.read();
  switch (c) {
    case 0x61: mode = 1; break;
    case 0x63: mode = 0; break;
    case 0x73:
      int s = Serial.readString().toInt();
      if (s != -1 && 0 <= s <= 255) speed = s;
      else Serial.println("INVALID!");
      break;
    default: Serial.println("INVALID!!"); Serial.flush(); break;
  }
  
}

