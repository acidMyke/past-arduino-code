// For 4 Digit Clock & Alarm Only //

#include <DS1302RTC.h>
#include <Time.h>
#include "LedControl.h"

// Variable //

int adigit;
int bdigit;
int cdigit;
int ddigit;

int a;
int b;
int c;
int d;
boolean APM = true; // True is AM, False is PM //

int aalarm;
int balarm;
int calarm;
int dalarm;

int bright;

// Switches //

int plus = 6;
int minus = 5;
int setTiming = 4;
int setAlarm = 3;

// Analog Pin //

int brightness = A1 ;

// LED //

int APMLED = 13;

// Buzzer //

int buzzer = 2;

// MAX72XX //

int DataIn = 12;
int CLK = 11;
int LOAD = 10;
int noOfIC = 1;

LedControl lc = LedControl(DataIn, CLK, LOAD, noOfIC);

//DS1302//

int CE = 9;
int IO = 8;
int SCLK = 7;

DS1302RTC RTC(CE, IO, SCLK);

// Setting Up //

void setup() {

  // Set Switches to INPUT //

  pinMode(plus, INPUT);
  pinMode(minus, INPUT);
  pinMode(setTiming, INPUT);
  pinMode(setAlarm, INPUT);

  // Brightness Adjustment //

  bright = analogRead(brightness);
  bright = map(bright, 0, 1023, 0, 8);

  // MAX72XX //

  lc.shutdown(0, false);
  lc.setIntensity(0, bright);
  lc.clearDisplay(0);

  // DS1302 //

  hourFormat12();
  if (RTC.haltRTC()) {
    blink(0);
  }
  delay(2000);
  scroll(0);
  setSyncProvider(RTC.get());
  scroll(1);
  scroll(2);
  if (timeStatus() != timeSet) {
    blink(1);
  }
  scroll(3);
  delay(2000);
  lc.clearDisplay(0);
}
void loop() {
  if (digitalRead(setTiming) == HIGH) {
    adjust();
  }
  if (pulseIn(setAlarm, HIGH) <= 5000000 ) {
    settingAlarm();
  }
  else {
    resetAlarm();
  }
  lc.clearDisplay(0);
  ttime();
  setdigits();

}
void blink(int digit) {
  lc.setDigit(0, digit, 8, true);
  delay(1000);
  lc.clearDisplay(0);
}
void scroll(int digit) {
  for (int i = 0; i < 10; i++) {
    lc.setDigit(0, digit, i, false);
    lc.clearDisplay(0);
  }
}
void adjust() {
  if (digitalRead(plus) == HIGH) {
    adjustTime(+1);
  }
  if (digitalRead(minus) == HIGH) {
    adjustTime(-1);
  }
}
void settingAlarm() {
  adigit = a;
  bdigit = b;
  cdigit = c;
  ddigit = d;
  if (digitalRead(plus) == HIGH) {
    d++;
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
    if (a == 1 & b == 2) {
      APM = !APM;
      a = 0;
      b = 0;
      c = 0;
      d = 0;
    }
  }

  if (digitalRead(minus) == HIGH) {
    d--;
    if (d == 0) {
      c--;
      d = 10;
    }
    if (c == 0) {
      b--;
      c = 6;
    }
    if (b == 0) {
      a--;
      b = 10;
    }
    if (a == 0 & b == 0) {
      a = 1;
      b = 2;
      c = 0;
      d = 0;
      APM = !APM;
    }
  }
  if (digitalRead(setAlarm) == HIGH) {
    return;
  }
}
void resetAlarm() {
  aalarm = 0;
  balarm = 0;
  calarm = 0;
  dalarm = 0;

  settingAlarm();
}
void ttime() {
  adigit = hour() / 10;
  bdigit = hour() % 10;
  cdigit = minute() / 10;
  ddigit = minute() % 10;
}
void setdigits() {
  lc.setDigit(0, 0, adigit, true);
  lc.setDigit(0, 1, bdigit, true);
  lc.setDigit(0, 2, cdigit, true);
  lc.setDigit(0, 3, ddigit, true);
}

