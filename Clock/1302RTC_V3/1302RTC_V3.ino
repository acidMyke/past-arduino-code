#include <DS1302RTC.h>
#include <Time.h>
#include <LedControl.h>

// Varable //
int digit[4], value[4], alarm[2][4], bright; 
boolean PM = false;

// Input //
// Analog //
int brightPin = 1;

// Digital //
int add = 6;
int subtract = 5;
int setTiming = 4;
int setAlarm = 3;

// Output //
// MAX72XX //
int DataIn = 12;
int CLK = 11;
int LOAD = 10;
int noOfIC = 1;

LedControl lc = LedControl(DataIn, CLK, LOAD, noOfIC);
// LED //
int APMLED = 13;

// Buzzer //
int buzzer = 2;

//DS1302//
int CE = 9;
int IO = 8;
int SCLK = 7;

DS1302RTC RTC(CE, IO, SCLK);

// Setup //

void setup(){
  // Set Pins to Input
  pinMode(add, INPUT);
  pinMode(subtract, INPUT);
  pinMode(setTiming, INPUT);
  pinMode(setAlarm, INPUT);

  // MAX72XX //
  lc.shutdown(0, false);
  lc.setIntensity(0, bright);
  lc.clearDisplay(0);

  // DS1302 //
  hourFormat12();
  if (RTC.haltRTC()) {
    
  }
  delay(2000);
  
  setSyncProvider(RTC.get());

  
  if (timeStatus() != timeSet) {
    
  }
  
  delay(2000);
  lc.clearDisplay(0);
}

void loop(){
  
}

