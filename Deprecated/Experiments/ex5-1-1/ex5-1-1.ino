//========== ex5-1-1.ino ============
// Arduino pin A0 connected to P6A-5, P6A-1 connected to GND (key 0)
// Arduino pin A5 connected to P14-2 (external drive buzzer LS14-2)
// Arduino pins 12~2 connected to P13A-14~P13A-4; RS, RW, EN, DB0~DB7
// LCD 1602 inserted in the P13A1 header 
//========== Global Declaration ============
#include <LiquidCrystal.h>	// include the LiquidCrystal library  
#define  BZ  A5			// buzzer connected to analog pin A5
#define  PB  A0			// key 0 connected to analog pin A0 
LiquidCrystal  myLCD(12,11,10, 9,8,7,6,5,4,3,2);//create LiquidCrystal object named myLCD
//========== Initialization ============
void setup()
{  pinMode(PB, INPUT); 	// configure analog pin A0 as an input  
   pinMode(BZ, OUTPUT); // configure analog pin A5 as an output
   digitalWrite(BZ, 1); // turn off the buzzer
   myLCD.begin(16, 2); 	// initialize the LCD
} 	
//========== Main Code ============
void loop()
{  int CNTs,pb; 		// declare integer variables CNTs, pb
   pb=digitalRead(PB);		// read key 0 state
   if (!pb)			// if key 0 is pressed, 
   {  CNTs=100;			// count down starting at 100
      while(CNTs!=0)		// if the counter is not equal to 0, 
      {  myLCD.setCursor(7,0); 	// set cursor position
	 myLCD.print(CNTs); 	// display count value (counter output)
	 myLCD.print("  "); 	// display spaces
	 delay(500); 		// a delay of 0.5 seconds
	 CNTs--;		// subtract one from count
      }
      myLCD.setCursor(7,0); 	// set cursor position
      myLCD.print("  "); 	// display spaces
      tone(BZ,1000);		// generate a 1kHz tone
      delay(50);	 	// a delay of 0.05 seconds
      noTone(BZ);		// muting
      delay(50);	 	// delay 0.05 seconds
      tone(BZ,1000);		// generate a 1kHz tone 
      delay(50);	 	// a delay of 0.05 seconds
      noTone(BZ);		// muting
      delay(50);	 	// a delay of 0.05 seconds
   }
}

