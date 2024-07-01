//Sensor pin
const int S1 = A1;
const int S2 = A2;
const int S3 = A3;
const int S4 = A4;
const int S5 = A5;

//Motor pin
const int ENA = 3;
const int ENB = 5;
const int IN1 = 6;
const int IN2 = 7;
const int IN3 = 8;
const int IN4 = 9;

void setup() {
  pinMode(S1, INPUT);
  pinMode(S2, INPUT);
  pinMode(S3, INPUT);
  pinMode(S4, INPUT);
  pinMode(S5, INPUT);

  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  analogWrite(ENA, 200);
  analogWrite(ENB, 200);
}

void loop() {
  if (digitalRead(S3) || digitalRead(S4) || digitalRead(S5))  digitalWrite(IN1, HIGH);
  else                                                        digitalWrite(IN1, LOW);
  
  if (digitalRead(S1))                                        digitalWrite(IN2, HIGH);
  else                                                        digitalWrite(IN2, LOW);
  
  if (digitalRead(S1) || digitalRead(S2) || digitalRead(S3))  digitalWrite(IN3, HIGH);
  else                                                        digitalWrite(IN3, LOW);
  
  if (digitalRead(S5))                                        digitalWrite(IN4, HIGH);
  else                                                        digitalWrite(IN4, LOW);
}
