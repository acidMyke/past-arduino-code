const int sensorPin[5] = {A1, A2, A3, A4, A5}, motorPin[4] = { 5 ,  6 ,  7 ,  8 };
//       Light Sensor Pin S1, S2, S3, S4, S5   L298 Pin       IN1, IN2, IN3, IN4
const byte comp[4] = {0x1C, 0x01, 0x07, 0x10};

void setup() {
  for (int pin: sensorPin) pinMode(pin, INPUT);  //Set all the sensor pin as INPUT
  for (int pin: motorPin)  pinMode(pin, OUTPUT); //Set all the motor drive pin as OUTPUT
  analogWrite(3, 250); // Set the PWM for ENA
  analogWrite(9, 250); // Set the PWM for ENB
}

void loop() {
  byte value = 0; //Create a new variable "value" as 0
  for (int i; i < 5; i++) value |= digitalRead(sensorPin[i]) << i;
  //Set "value" to be the bitwise OR of "value" and the left shifted bit of sensorPin (Repeat 5 times)
  for (int i; i < 4; i++) digitalWrite(motorPin[i], value & comp[i]);
  //Set the motor pin to the bitwise AND of value and the respective comp (Repeat 4 times)
}
