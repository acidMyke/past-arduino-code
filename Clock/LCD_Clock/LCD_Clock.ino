#include <LiquidCrystal.h>

const int lcdPin[] = {12, 11, 10, 9, 8, 7};  // {rs, en, D4, D5, D6, D7}
const int buttonPin[] = {6, 5, 4, 3, 2, 1, 0};  // {D7, D6, D5, D4, D3, D2, D1}
const int noOfDay[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}; // {Jan, Feb, Mar, Apr, Jun, Jul, Aug, Sep, Oct, Nov, Dec}

int time[3]; //{Hours, Minute, Seconds}
int date[5]; //{Day, Month, Year, Day of the Week, Week}
int timer[3];
int stopwatch[4];
int alarm[5][4];
int oldMillis;


String am = "AM", pm = "PM";
String nameOfMonth[12] = {"Jan", "Feb", "Mar", "Apr", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
//String corespondValue[3][4] = {{"1", "4", "7", "*"}, {"2", "5", "8", "0"}, {"3", "6", "9", "#"}};
//String corespondValue[4][3] = {{"1", "2", "3"}, {"4", "5", "6"}, {"7", "8", "9"}, {"*", "0", "#"}};
String buttonString;

LiquidCrystal LCD(lcdPin[0], lcdPin[1], lcdPin[2], lcdPin[3], lcdPin[4], lcdPin[5]);

#include "LCD_Time.h"

void setup() {
  Serial.begin(115200);
  while (!Serial)delay(100);
  LCD.begin(16, 2);
  for (int i = 0; i < 7; i++) {
    if (i < 4) {
      pinMode(buttonPin[i], OUTPUT);
      digitalWrite(buttonPin[i], LOW);
    }
    else
      pinMode(buttonPin[i], INPUT);
  }
}

void loop() {
  switch (readButton()) {
    case 0:
      delay(500);
      switch (readButton()) {
        case 0: display(time, 1); break;
        case 1: display(date, 2); break;
        case 2: break;
        case 3: break;
        case 4: break;
        case 5: break;
      }
      break;
    case 1: Time(); break;
    case 2: Date(); break;
    case 3: Alarm(); break;
    case 4: Timer(); break;
    case 5: Stopwatch(); break;
    case 9: getSerialTime(); break;
  }
  interval();
}


