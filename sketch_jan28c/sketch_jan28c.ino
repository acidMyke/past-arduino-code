

void setup() {
  pinMode(A4, INPUT);
  Serial.begin(9600);
}

void loop() {
  Serial.println(analogRead(A4));
}
