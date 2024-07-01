const int shiftPin[] = {14, 12, 13}; // {Data,IC1 - Clock,IC2 Clock}
/*   IC1
   QA - Segment A
   QB - Segment B
   QC - Segment C
   QD - Segment D
   QE - Segment E
   QF - Segment F
   QG - Segment G
   QH - Segment DP
   ________
     IC2
   QA - Digit 0
   QB - Digit 1
   QC - Digit 2
   QD - Digit 3
   QE - Digit 4
   QF - Digit 5
   QG - Digit 6
   QH - Digit 7 */
const byte data[] {
  B11111100,  //0
  B01100000,  //1
  B11011010,  //2
  B11110010,  //3
  B01100110,  //4
  B10110110,  //5
  B10111110,  //6
  B11100000,  //7
  B11111110,  //8
  B11100110,  //9
  B00000000   //Nothing
};

int dataBuffer[8];
String serial;

void setup() {
  Serial.begin(115200);
  while (!Serial) delay (1);
  for (int i = 0; i < 3; i++)
    pinMode(shiftPin[i], OUTPUT);
  for (int i = 0; i < 8; i++)
    dataBuffer[i] = -1;
}

void loop() {
  segmentUpdate();
  SerialDigit();
}

void segmentUpdate() {
  for (int i = 0; i < 8; i++)
    if (dataBuffer[i] != 0) {
        shiftOut(shiftPin[0], shiftPin[2], LSBFIRST, 0); // Turn off ALL digit
        shiftOut(shiftPin[0], shiftPin[1], LSBFIRST, dataBuffer[i]); // Turn on the specific segment
        shiftOut(shiftPin[0], shiftPin[2], LSBFIRST, (1 << (7 - i))); // Turn on the specific digit
        delayMicroseconds(10);
    }
}

void SerialDigit() {
  if (Serial.available() > 0)
    serial = Serial.readString();
  if (serial != NULL) {
    if (serial.length() <= 8)
      for (int i = 0; i < 8; i++)
        if (serial.substring(i, 1).toInt() != -1)
          dataBuffer[i] = serial.substring(i, 1).toInt();
        else
          dataBuffer[i] = 10;
    else 
      Serial.println("ERROR Length > 8");
  }
}
