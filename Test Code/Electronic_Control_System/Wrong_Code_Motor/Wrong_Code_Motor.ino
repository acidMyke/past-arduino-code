int enable2 = 9;
int in3 = 10;
int in4 = 11;
int swPin = 2;
int ledPin = 13;
int swState = 0;

void setup() {
  Serial.begin(115200);
  pinMode(enable2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(ledPin, OUTPUT);
  pinMode(swPin, INPUT_PULLUP);
}

void loop() {
  swState = digitalRead(swPin);
  if (!swState) {
    digitalWrite(ledPin, HIGH);
    Serial.println("Stage 1");
    analogWrite(enable2, 255);
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);
    delay(10000);
    Serial.println("Stage 2");
    digitalWrite(in3, LOW);
    digitalWrite(in4, LOW);
    delay(1000);
    analogWrite(enable2, 150);
    Serial.println("Stage 3");
    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);
    delay(3000);
    Serial.println("Stage 4");
    digitalWrite(in3, LOW);
    digitalWrite(in4, LOW);
    delay(1000);
    analogWrite(enable2, 200);
    Serial.println("Stage 5");
    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);
    delay(7000);
    Serial.println("Stage 6");
    digitalWrite(in3, LOW);
    digitalWrite(in4, LOW);
    delay(1000);
  }
  else {
    Serial.println("Stage 7");
    digitalWrite(ledPin, LOW);
    digitalWrite(in3, LOW);
    digitalWrite(in4, LOW);
    delay(1000);
  }
}

