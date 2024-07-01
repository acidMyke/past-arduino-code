#define BuzzerPin 11
#define EchoPin 10
#define TrigPin 9

float distance = 0.00;
uint32_t startPing = 0;
uint8_t SignalSent = false;
uint16_t freq = 0;


void setup() {
  pinMode(BuzzerPin, OUTPUT);
  pinMode(TrigPin, OUTPUT);
  pinMode(EchoPin, INPUT);
  Serial.begin(9600);
  Serial.println("Starting");
}

void loop() {
  getDistanceAsync();
  //  printDistance();
  if (freq != 0) {
    //Serial.println("Frequency: " + String(freq));
    //    tone(BuzzerPin, freq);
  }
}

void getDistanceAsync() {
  if (!SignalSent) {
    digitalWrite(TrigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(TrigPin, HIGH);
    delayMicroseconds(5);
    digitalWrite(TrigPin, LOW);
    SignalSent = true;
  }
  else if (digitalRead(EchoPin)) {
    startPing = micros();
    while (digitalRead(EchoPin));
    uint32_t timing = micros() - startPing;
        Serial.println("Time: " + String(timing));
    freq = map(constrain(timing, 150, 1500), 150, 1500, 31, 3136);
    //Serial.println("Frequency: " + String(freq));
    if (freq != 3136 || freq != 31) tone(BuzzerPin, freq);
    else noTone(BuzzerPin);
    //    distance = (float)timing / 29.1 / 2;
    //Serial.println("Distance: " + String(distance, 5));
    SignalSent = false;
  }
}

void printDistance() {
  Serial.println("Distance: " + String(distance, 5));

}
