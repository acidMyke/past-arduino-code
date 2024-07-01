const int motorPin[] = {8, 9, 10, 11};
String serial;

void setup() {
  Serial.begin(115200);
  for (int i = 0; i < 4; i++) {
    pinMode(motorPin[i], OUTPUT);
    digitalWrite(motorPin[i], LOW);
  }
}

void loop() {
  if (Serial.available() > 0) serial = Serial.readString();
  if (serial != NULL) {
    rotate(serial.toInt());
    serial.remove(0);
  }
}

void rotate(int degree) {
  Serial.println(degree);
  int no = degree / 7.2;
  for (int x = 0; x < no; x++) {
    writeMotor(1 << 0);
    writeMotor(1 << 2);
    writeMotor(1 << 1);
    writeMotor(1 << 3);
    Serial.println(no - x);
  }
  //writeMotor(0);
}

void writeMotor(byte _buffer) {
  for (int i = 0; i < 4; i++) {
    digitalWrite(motorPin[i], bitRead(_buffer, i));
  }
  delay(10);
}

