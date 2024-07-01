void setup() {
  DDRD |= 0xFC;
}

void loop() {
  if (PINC == 0x00 || PINC == 0x3E) return;
  byte prevData = PINC, numRun = 0;
  while (PINC == prevData) {
    if (PINC & 0x38) PORTD |= 0xC4;
    if (PINC & 0x02) PORTD |= 0xC8;
    if (PINC & 0x0E) PORTD |= 0xD0;
    if (PINC & 0x20) PORTD |= 0xE0;
    if (numRun++ < 250) delay(20);
    else while (PINC == prevData);
    PORTD ^= 0x3C;
    delay(20);
    PORTD &= 0x03;
    
  }
}

/*Hardware Connection (Data Connection)
  Arduino     L298     Sensor
     2 --------IN1        |       //Left Motor Forward Pin
     3 --------IN2        |       //Left Motor Reverse Pin
     4 --------IN3        |       //Right Motor Forward Pin
     5 --------IN4        |       //Right Motor Reverse Pin
     6 --------ENA        |       //Left Motor Enable Pin
     7 --------ENB        |       //Right Motor Enable Pin
    A1 ------------------S1       //Extreme Left Sensor
    A2 ------------------S2       //Centre Left Sensor
    A3 ------------------S3       //Middle Sensor
    A4 ------------------S4       //Centre Right Sensor
    A5 ------------------S5       //Extreme Right Sensor
*/
