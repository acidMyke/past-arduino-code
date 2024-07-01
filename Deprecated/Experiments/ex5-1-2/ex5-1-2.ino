//========== ex5-1-2.ino ============
// pins 12~10 connected to P13A-1~P13A-3; RS, RW, EN
// pins 5~2 connected to P13A-8~P13A-11; DB4~DB7
// LCD 1602 inserted in P13A1 header 
//========== Global Declaration ============
#include <LiquidCrystal.h>		// include the LiquidCrystal library 
LiquidCrystal  myLCD(12,11,10, 5,4,3,2);// create a LiquidCrystal object named myLCD
byte up[]={	0b00000,
		0b00000,
		0b00100,
		0b01110,
		0b11111,
		0b01110,
		0b01110,
		0b00000 
	   };
byte down[]={	0b00000,
		0b00000,
		0b01110,
		0b01110,
		0b11111,
		0b01110,
		0b00100,
		0b00000 
	    };
byte left[]={	0b00000,
		0b00000,
		0b00100,
		0b01111,
		0b11111,
		0b01111,
		0b00100,
		0b00000
	     };
byte right[]={	0b00000,
		0b00000,
		0b00100,
		0b11110,
		0b11111,
		0b11110,
		0b00100,
		0b00000
	     };
//========== Initialization ============
void setup()
{  myLCD.createChar(0,up);	// create the character pattern of up arrow
   myLCD.createChar(1,down); 	// create the character pattern of down arrow
   myLCD.createChar(2,left); 	// create the character pattern of left arrow
   myLCD.createChar(3,right); 	// create the character pattern of right arrow
   myLCD.begin(16, 2); 		// initialize the LCD
} 	
//========== Main Code ============
void loop()
{  myLCD.home(); 		// cursor home
   myLCD.write(byte(0));	// display custom character pattern (up arrow) 
   myLCD.print("Up  Down");	// display string at col 0 of row 0, (0, 0)
   myLCD.write(byte(1));	// display custom character pattern (down arrow)
   myLCD.setCursor(0,1); 	// position cursor in the display position (0, 1)
   myLCD.write(byte(2));	// display custom character pattern (left arrow) 
   myLCD.print("Left  Right");	// display string at col 1 of row 1, (1, 1) 
   myLCD.write(byte(3));	// display custom character pattern (right arrow)
   delay(500); 			// pause 0.5 seconds
   for(int i=0;i<13;i++) 		
   {  myLCD.scrollDisplayLeft();// scroll the displayed characters one space to the left
      delay(750); 		// pause 0.75 seconds
   }	
   myLCD.clear();		// clear screen 
}	

