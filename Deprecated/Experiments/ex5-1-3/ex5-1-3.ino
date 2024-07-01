//========== ex5-1-3.ino ============
//LCD 1602 inserted in P13C header 
// pin A4 connected to P13B1-1 (SCL), pin A5 connected to P13B1-2 (SDA)
// pin A0 connected to P7-2 (V pot)
//========== Global Declaration ============
#include <Wire.h>  		   // include the Wire library 
#include <LiquidCrystal_I2C.h> 	   // include the LiquidCrystal_I2C library 
#define  POT  A0 		   // V pot connected to analog pin A0
LiquidCrystal_I2C myI2C(0x27,16,2);// create a LiquidCrystal_I2C object named myI2C
//========== Initialization ============
void setup()
{  myI2C.begin(); 	      // initialize the I2C LCD 
   myI2C.backlight(); 	      // turn on the backlight
   pinMode(POT,INPUT); 	      // configure analog pin A0 as an input 
} 
//========== Main Code ============
void loop()
{  myI2C.home(); 			// cursor home
   myI2C.print("Voltage =     mV");	// display string
   int pot = analogRead(POT);	  // read the value of V pot, range 0 to 1023
   pot = map(pot, 0,1023, 0,4999);// scale it for the voltmeter use, range 0 to 4999
   myI2C.setCursor(10,0); 	  // set cursor position to col 10 of row 0, (10,0) 
   myI2C.print(pot);		  // display the scaled voltage value
   delay(1000);			  //delay 1 second
}

