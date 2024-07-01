#include <Tlc5940.h>

#define NUM_TLCS 3
#define NUM_ROWS 8

// PINs
const int brightPot = A0;
const int rowPin[] = {A4, A3, A2, A1}; //A1 is LSB
const int TLC[NUM_TLCS][16] { // TLC pin // TLC[RGB][Colume]
  { 0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15},
  {16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31},
  {32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47}
};

// Variable
int ledValue[NUM_TLCS][16][NUM_ROWS]; // ledValue[RGB][Colume][Row]
int timing = 4000;
int bright;
int oldMillis;
//int fxNo;


String serialData;
//String fxKey[5] = {"Set :", "Clear :", "", ""};

#include "fx.h"

void setup() {
  Serial.begin(115200);
}

void loop() {
  serialDecoder();
  matrixUpdate();
}
void serialDecoder() {
  if (Serial.available() > 0) {
    serialData = Serial.readStringUntil("\n");
  }
  if (serialData.startsWith("#")) {
    Serial.println(serialData.substring(1));
    serialData.remove(0);
  }
  else {
    if (oldMillis < millis() - timing ) {
      if (serialData != NULL) {
        serialToLedValue(serialData);
        /*serialData.toLowerCase();
        for (int fx = 0; fx < 5; fx++) {
          fxKey[fx].toLowerCase();
          if (serialData.indexOf(fxKey[fx]) != -1 ) {
            serialData.replace(fxKey[fx], "");
            fxNo = fx;
            break;
          }
        }
        switch (fxNo) {
          case 1: serialToLedValue(serialData); break;
        }*/
      }
    }
  }
}

