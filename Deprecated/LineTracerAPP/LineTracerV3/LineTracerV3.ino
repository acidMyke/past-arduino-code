const int sensorPin[5] = {A1, A2, A3, A4, A5};  // LM, L, C, R, RM
const int motorPin[4] = {8, 7, 6, 5};           // LF, LR, RF, RR
const byte comp[4] = {0x1C, 0x01, 0x07, 0x10};  //const byte comp[4] = {0x10, 0x07, 0x01, 0x1C};  //10000, 00111, 00001, 11100

void setup() {
  for (int pin : sensorPin) pinMode(pin, INPUT);  //Set all the sensor pin as INPUT
  for (int pin : motorPin)  pinMode(pin, OUTPUT); //Set all the motor drive pin as OUTPUT
  analogWrite(3, 220); // Set the PWM for ENA
  analogWrite(9, 220); // Set the PWM for ENB
}

void loop() {
  byte data = 0; //Create a new variable
  for (int i; i < 5; i++) data |= digitalRead(sensorPin[i]) << i;    //Read the pin, shift the bit, combine with "data"
  for (int i; i < 4; i++) digitalWrite(motorPin[i], data & comp[i]); //Bitwise AND data with
}
