//========== ex7-1-1.ino ============
// pin 5 connected to P17B-1 (Y-axis servo M1)
// pin 6 connected to P17B-2 (X-axis servo M2)
// pin A5 connected to P7-1 (H pot)
// pin A4 connected to P7-2 (V pot)
//========== Declaration ============
#define  M1	5	// M1 connected to digital pin 5 
#define  M2	6	// M2 connected to digital pin 6
#define  potH	 A5	// H pot connected to analog pin A5
#define  potV	 A4	// V pot connected to analog pin A4
#include <Servo.h>  	// include the Servo library
Servo ServoM1;		// create a Servo object named ServoM1
Servo ServoM2;		// create a Servo object named ServoM2 
int pH,pV;		// declare integer variables pH and pV 
//========== Initialization ============
void setup()
{  ServoM1.attach(M1); 	  // attach the ServoM1 variable to digital pin 5
   ServoM2.attach(M2); 	  // attach the ServoM2 variable to digital pin 6
   pinMode(potV, INPUT);  // configure analog pin A4 as an input 
   pinMode(potH, INPUT);  // configure analog pin A5 as an input 
} 
//========== Main Code ============
void loop()
{  pV = analogRead(potV);	// read the voltage of V pot, range 0 to 1023 
   pV = map(pV,0,1023, 0,180);	// scale it for the servo use, range 0 to 180 
   ServoM1.write(pV); 	// set the Y-axis servo position using the scaled value
   pH = analogRead(potH);	// read the voltage of H pot, range 0 to 1023
   pH = map(pH,0,1023, 0,180);	// scale it for the servo use, range 0 to 180
   ServoM2.write(pH); 	// set the X-axis servo position using the scaled value 
   delay(100); 			// a delay of 100 ms
}	

