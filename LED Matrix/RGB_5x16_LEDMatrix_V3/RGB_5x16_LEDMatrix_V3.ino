#include <Tlc5940.h>
#include <avr/pgmspace.h>

// Fuction
void ran(int i, int no = 20);

// Pins
int row[5] = {2, 4, 5, 6, 7};  // Digital Pins // row[Row]
int brightnessPot = 14;  // Analog Pin
int TLC[16][3] = {  // TLC Pin // TLC [Colume][RGB]
  { 0 , 16, 32 },
  { 1 , 17, 33 },
  { 2 , 18, 34 },
  { 3 , 19, 35 },
  { 4 , 20, 36 },
  { 5 , 21, 37 },
  { 6 , 22, 38 },
  { 7 , 23, 39 },
  { 8 , 24, 40 },
  { 9 , 25, 41 },
  { 10, 26, 42 },
  { 11, 27, 43 },
  { 12, 28, 44 },
  { 13, 29, 45 },
  { 14, 30, 46 },
  { 15, 31, 47 }
};

// Variable
int rowValue[5][16][4]; // Brightness value of the LED // rowValue[Row][Colume][RGB] // RGB : 0 = Red, 1 = Green, 2 = Blue,  3 = Nothing
int staticPicture = 0;
int timing = 4000;  // On time for each rows
int brightness;
int oldMillis = 0;
int picDuration = 10000; // Duration of one Static Picture / Animation


void setup() {
  for (int i = 0 ; i < 5; i++) {
    pinMode(i, OUTPUT);
    digitalWrite(i, HIGH);
  }
  Tlc.init();
}
void loop() {
  brightness = map(analogRead(brightnessPot), 0, 1023, 0, 4095);
  switch (staticPicture) {
    case 0 : all(0); break; // All Red
    case 1 : all(1); break; // All Green
    case 2 : all(2); break; // All Blue
    case 3 : all(0); all(1); break; // All Yellow
    case 4 : all(0); all(2); break; // All Magenta
    case 5 : all(1); all(2); break; // All Cyan
    case 6 : all(0); all(1); all(2); break; // All White
    case 7 : ran(0); break; // Randomly light any 10 of the red
    case 8 : ran(1); break; // Randomly light any 10 of the green
    case 9 : ran(2); break; // Randomly light any 10 of the blue
    case 10: ran(0); ran(1); ran(2); break; // Randomly light any led
    case 11: triangleWave(2); break;
  }
  matrixUpdate(timing);
  if (oldMillis >= millis() - picDuration) {
    staticPicture++;
  }
  if ( staticPicture == 12) {
    staticPicture = 0;
  }
}

void matrixUpdate(int onTime) {
  for (int x = 0; x < 5; x++) {
    for (int y = 0; y < 16; y++) {
      for (int i = 0; i < 3; i++) {
        Tlc.set(  TLC[y][i]  , rowValue[x][y][i] );
      }
    }
    digitalWrite( row[x], LOW);
    delayMicroseconds(onTime);
    for (int row = 0 ; row < 5; row++) {
      digitalWrite(row, HIGH);
    }
  }
  reset();
}

