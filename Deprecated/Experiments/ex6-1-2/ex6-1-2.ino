//========== ex6-1-2.ino ============
// A4 pin connected to P13B1-1 (SDA)
// A5 pin connected to P13B1-2 (SCL)
// pin 6 connected to P22B-1 (Trig pin)
// pin 7 connected to P22B-2 (Echo pin)
//========== Global Declaration ============
#define  trig	6	        // Trig pin connected to digital pin 6
#define  echo	7	        // Echo pin connected to digital pin 7
#include <Wire.h>  		// include the Wire library 
#include <LiquidCrystal_I2C.h> 	// include the LiquidCrystal_I2C library 
int Width;		// declare an integer variable named Width 
int distance=0;		// declare an integer variable named distance 
LiquidCrystal_I2C myI2C(0x27,16,2); // create a LiquidCrystal_I2C object
//========== Initialization ============
void setup()
{  myI2C.begin(); 		// initialize the LCD 
   myI2C.backlight(); 		// turn on the backlight
   pinMode(trig, OUTPUT);	// configure digital pin 6 as an output
   pinMode(echo, INPUT);	// configure digital pin 7 as an input 
} 
//========== Main Code ============
void loop()
{  myI2C.home(); 		// cursor home
   for(int i=0;i<10;i++) 	// repeat measuring 10 times
   {  readUtrasonic(); 		// measure the distance
      distance+=Width; 		// accumulate the distance measurements
      delay(50); 		// a delay of 0.05 seconds
   }
   distance/=10; 	   // calculate the average of 10 measurements
   myI2C.print("Distance");	// display string
   myI2C.setCursor(0,1);   // set cursor to the left end of row 1, (0,1) 
   myI2C.print(distance); 	// display the distance
   myI2C.print("  cm    "); 	// display units
   delay(1000);			// a delay of 1 second
}
//========== Function ============
void readUtrasonic()
{  digitalWrite(trig, 1);	// trigger the ultrasonic sensor
   delayMicroseconds(20);	// a delay of 20 us
   digitalWrite(trig, 0);	// stop the ultrasonic sensor 
   Width = pulseIn(echo, HIGH);	// measure the width of echo pulse
   Width *= 0.0173;		// calculate the distance
}

