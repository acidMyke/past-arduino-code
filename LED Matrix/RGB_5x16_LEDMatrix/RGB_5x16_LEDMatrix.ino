#include "Tlc5940.h"

#define RowOne 2
#define RowTwo 4
#define RowThree 5
#define RowFour 6
#define RowFive 7
#define Bpot 14

int timing = 4000;
int row = 1 ;
int staticPicture = 1;
int norow = 6;
int bright;

void setup() {

  pinMode(RowOne , OUTPUT);
  pinMode(RowTwo , OUTPUT);
  pinMode(RowThree , OUTPUT);
  pinMode(RowFour , OUTPUT);
  pinMode(RowFive , OUTPUT);

  digitalWrite(RowOne , HIGH);
  digitalWrite(RowTwo , HIGH);
  digitalWrite(RowThree , HIGH);
  digitalWrite(RowFour , HIGH);
  digitalWrite(RowFive , HIGH);

  Tlc.init();

}
void loop() {
  if (staticPicture = 1) {
    reset();allred(bright);
  }
  if (staticPicture = 2) {
    reset();allblue(bright);
  }
  if (staticPicture = 3) {
    reset();allgreen(bright);
  }
  if (staticPicture = 4) {
    reset();allone(bright);
  }
  if (staticPicture = 5) {
    reset();alltwo(bright);
  }
  if (staticPicture = 6) {
    reset();allthree(bright);
  }
  if (staticPicture = 7) {
    reset();allfour(bright);
  }
  if (staticPicture = 8) {
    reset();allfive(bright);
  }
  if (staticPicture = 9) {
    reset();
  }
  if (staticPicture = 10) {
    reset();
  }
  if (staticPicture = 11) {
    reset();
  }
  if (staticPicture = 12) {
    reset();
  }
  if (staticPicture = 13) {
    reset();
  }
  if (staticPicture = 14) {
    reset();
  }
  if (staticPicture = 15) {
    reset();
  }
  if (staticPicture = 16) {
    reset();
  }
  if (staticPicture = 17) {
    reset();
  }
  if (staticPicture = 18) {
    reset();
  }
  matrixUpdate(row);
  delayMicroseconds(timing);
  row++;
  if (row > norow) {
    row = 0;
    staticPicture++;
  }
  bright = analogRead(Bpot);
  bright = map(bright , 0 , 255 , 0 , 4095);
}

