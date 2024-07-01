#include <DS1302RTC.h>
#include <Time.h>
#include "LedControl.h"

//varible//

int delaytime = 250;
int adigit;
int bdigit;
int cdigit;
int ddigit; /*
  int edigit;
  int fdigit;*/
int a;
int b;
int c;
int d;
int e;
int f;
int tis = 0;

//switches//
int plus = 6;
int minus = 5;
int stopwatchpin = 2;
int timerpin = 1;
int start = 0;

//LED//
int AMpin = 4;
int PMpin = 3;

//LM35//
int reading;
int tempPin = 0;

//MAX72XX//

int DataIn = 12;
int CLK = 11;
int LOAD = 10;
int no = 1;

LedControl lc = LedControl(DataIn, CLK, LOAD, no);

//DS1302//

int CE = 9;
int IO = 8;
int SCLK = 7;

DS1302RTC RTC(CE, IO, SCLK);

void setup() {
  pinMode(plus, INPUT);
  pinMode(minus, INPUT);
  pinMode(start, INPUT);
  pinMode(stopwatchpin, INPUT);

  //MAX72XX//
  lc.shutdown(0, false);
  lc.setIntensity(0, 8);
  lc.clearDisplay(0);

  //DS1302//
  hourFormat12();
  if (RTC.haltRTC()) {
    blink(0);
  }
  delay ( 2000 );
  scroll(0);
  setSyncProvider(RTC.get);
  scroll(1);
  scroll(2);
  if (timeStatus() != timeSet) {
    blink(1);
  }
  scroll(3);
  delay ( 2000 );
  lc.clearDisplay(0);
  
  //LM35//
  analogReference(INTERNAL);
}

void loop() {
  adjust();
  lc.clearDisplay(0);
  if (digitalRead(stopwatchpin) == HIGH) {
    stopwatch();
  }
  ttime();
  readtemp();
  setdigit();


}
void blink(int digit) {
  lc.setDigit(0, digit, 8, true);
  delay(delaytime);
  lc.clearDisplay(0);
}
void scroll(int digit) {
  for (int i = 0; i < 10; i++) {
    lc.setDigit(0, digit, i, false);
    lc.clearDisplay(0);
  }
}
void readtemp(){
  reading = analogRead(tempPin);
  reading = reading/9.31;
  if(cdigit == 0 || cdigit == 1 || cdigit == 2 || cdigit == 3 || cdigit == 4 || cdigit == 5){ //Every 10 Minute//
    adigit = reading/10;
    bdigit = reading%10;
  }
}
void ttime() {
  adigit = hour() / 10;
  bdigit = hour() % 10;
  cdigit = minute() / 10;
  ddigit = minute() % 10;/*
  edigit = second()/10;
  fdigit = second()%10;*/
}
void setdigit() {
  lc.setDigit(0, 0, adigit, true);
  lc.setDigit(0, 1, bdigit, true);
  lc.setDigit(0, 2, cdigit, true);
  lc.setDigit(0, 3, ddigit, true);/*
  lc.setDigit(0,4,edigit,true);
  lc.setDigit(0,5,fdigit,true);*/
}
void adjust() {
  if (digitalRead(plus) == HIGH) {
    adjustTime(+1);
  }
  if (digitalRead(minus) == HIGH) {
    adjustTime(-1);
  }
}
void stopwatch() {
  if (digitalRead(minus) == HIGH) {
    a = 0;
    b = 0;
    c = 0;
    d = 0;
    e = 0;
    f = 0;
  }
  if (digitalRead(start) == HIGH) {
    delay(1000);
    f++ ;
  }
  if (f == 10) {
    e++;
    f = 0;
  }
  if (e == 6) {
    d++;
    e = 0;
  }
  if (d == 10) {
    c++;
    d = 0;
  }
  if (c == 6) {
    b++;
    c = 0;
  }
  if (b == 10) {
    a++;
    b = 0;
  }
  if (a == 2 & b == 4) {
    a = 0;
    b = 0;
    c = 0;
    d = 0;
    e = 0;
    f = 0;
  }
  if (b == 0 & a == 0) {
    adigit = c;
    bdigit = d;
    cdigit = e;
    ddigit = f;
  }
  else {
    adigit = a;
    bdigit = b;
    cdigit = c;
    ddigit = d;
  }
}

