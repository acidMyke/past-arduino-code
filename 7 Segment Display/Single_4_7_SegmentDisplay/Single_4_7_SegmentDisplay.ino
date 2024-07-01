const int shiftPin[] = {12, 11};
const int clearPin = 10;
/*
    MCU
  shiftPin[0] - 1(IC1)
  shiftPin[1] - 8(IC1)
  clearPin - 9(IC1)
  ___________
  IC1 (74*164)
  01 - shiftPin[0](MCU)
  02 - VCC
  03 - Digit 0
  04 - Digit 1
  05 - Digit 2
  06 - Digit 3
  07 - GND
  08 - shiftPin[1](MCU)
  09 - clearPin(MCU)
  10 - 7(IC2)
  11 - 1(IC2)
  12 - 2(IC2)
  13 - 6(IC2)
  14 - VCC
  __________
  IC2 (74*47)
  01 - 11(IC1)
  02 - 12(IC1)
  03 - VCC
  04 - VCC
  05 - VCC
  06 - 13(IC1)
  07 - 10(IC1)
  08 - GND
  09 - Segment E
  10 - Segment D
  11 - Segment C
  12 - Segment B
  13 - Segment A
  14 - Segment G
  15 - Segment F
  16 - VCC
*/

int data = 0;
String serial;

void setup() {
  Serial.begin(115200);
  while (!Serial)delay(1);
  pinMode(shiftPin[0], OUTPUT);
  pinMode(shiftPin[1], OUTPUT);
  pinMode(clearPin, OUTPUT);
  digitalWrite(clearPin, HIGH);
}

void loop() {
  if (Serial.available() > 0)
    serial = Serial.readString();
  if (serial != NULL && serial.toInt() != -1 && serial.length() <= 4)
    data = serial.toInt();
  else if (serial != NULL && serial.toInt() != -1)
    Serial.println("ERR: Number to long");
  else if (serial != NULL && serial.toInt() == -1)
    Serial.println("ERR: Not a number");
  segmentUpdate();
}

void segmentUpdate() {
  int thousands, hundreds, tens, ones;

  thousands = data / 1000;
  hundreds = data % 1000 / 100;
  tens = data % 100 / 10;
  ones = data % 10;

  Serial.println("\nData: " + String(data));
  Serial.println("Thousands: " + String(thousands));
  Serial.println("Hundreds: " + String(hundreds));
  Serial.println("Tens: " + String(tens));
  Serial.println("Ones: " + String(ones));

  thousands += 128;
  hundreds += 64;
  tens += 32;
  ones += 16;

  Serial.println("\nData in BINARY");
  Serial.println("Thousands: " + String(thousands, BIN));
  Serial.println("Hundreds: " + String(hundreds, BIN));
  Serial.println("Tens: " + String(tens, BIN));
  Serial.println("Ones: " + String(ones, BIN));

  byte buffer[4] = {byte(thousands), byte(hundreds), byte(tens), byte(ones)};
  for (int i = 0; i < 4; i++) {
    digitalWrite(clearPin, LOW);
    digitalWrite(clearPin, HIGH);
    shiftOut(shiftPin[0], shiftPin[1], LSBFIRST, buffer[i]);
    delayMicroseconds(500);
  }
  digitalWrite(clearPin, LOW);
  digitalWrite(clearPin, HIGH);
}

