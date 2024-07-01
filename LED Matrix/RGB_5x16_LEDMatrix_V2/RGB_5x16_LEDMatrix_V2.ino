#include "Tlc5940.h"

// Pins
int row[5] = {2, 4, 5, 6, 7};  // Digital Pins
int brightnessPot = 14;  // Analog Pin
int TLC[3][16] = {
  { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15},
  { 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31},
  { 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47} // TLC Pins
};

// Variable
int rowValue[5][3][16]; // Brightness value of the LED
int staticPicture = 0;
int timing = 4000;
int brightness;
int oldMillis = 0;


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
    case 0: allRed(); break;
    case 1: allGreen(); break;
    case 2: allBlue(); break;
    case 3: allYellow(); break;
    case 4: allMagenta(); break;
    case 5: allCyan(); break;
    case 6: allWhite(); break;
    
  }
  matrixUpdate();
  if(oldMillis >= millis() - 5000){
      staticPicture++;
  }
  if ( staticPicture == 7) {
    staticPicture = 0;
  }
}

void matrixUpdate() {
  for (int x = 0; x < 5; x++) {
    for (int y = 0; y < 3; y++) {
      for (int i = 0; i < 16; i++) {
        Tlc.set(  TLC[y][i]  , rowValue[x][y][i] );
      }
    }
    digitalWrite( row[x], LOW);
    delayMicroseconds(timing);
    for (int i = 0 ; i < 5; i++) {
      digitalWrite(i, HIGH);
    }
    reset();
  }
}

