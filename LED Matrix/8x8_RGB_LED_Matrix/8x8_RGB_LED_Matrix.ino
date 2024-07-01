//Date Created: 4th Nov 2018
//Orignal Dimension: 8 Row by 8 Columns
//IC: One 74*138, 3 TLC5917

//Input/Output pin
const int rowA = 2, rowB = 3, rowC = 4, rowEN = 5;
const int colSDI = 6, colCLK = 7, colLE = 8, colOE = 9, colSDO = 10;
const int brightnessPot = A0; //Arduino Analog Pin 0 (digitalPin 14)

//Variable
byte value[8][24]; //value[Row][Column]
byte brightness;

void setup() {
  Serial.begin(9600);
  pinMode(rowA, OUTPUT);
  pinMode(rowB, OUTPUT);
  pinMode(rowC, OUTPUT);
  pinMode(rowEN, OUTPUT);
  pinMode(colSDI, OUTPUT);
  pinMode(colCLK, OUTPUT);
  pinMode(colLE, OUTPUT);

  pinMode(colSDO, INPUT);
}

void loop() {
  matrixUpdate();
}

void matrixUpdate() {
  for (int b; b < 16; b++) {
    for (int r; r < 8; r++) { //Loop thru all eight rows
      for (int c = 24; c > -1; c--) {
        digitalWrite(colSDI, value[r][c] < b); //digitalWrite(colSDI, value[r][c] & (1 << b))
        digitalWrite(colCLK, HIGH);
        digitalWrite(colCLK, LOW);
      }
      digitalWrite(colOE, HIGH); //Disable OUTPUT
      digitalWrite(colLE, HIGH); //Latch Data
      digitalWrite(colLE, LOW);
      digitalWrite(rowA, r & 0x01);
      digitalWrite(rowB, r & 0x02);
      digitalWrite(rowC, r & 0x04);
      digitalWrite(colOE, LOW); //Enable OUTPUT
    }
  }
}
