//========== ex8-2-2.ino ============
// pins 2~5 connected to P19D-3~P19D-6 
// P19D-1 and P19D-2 connected to +5V
// pin A0 connected to P24-3 
//========== Global Declaration ============
const int joyV = A0; 		// joystick’s V pot connected to analog pin A0 
#define  steps  200		// define a 200-step motor
#include <Stepper.h>		// include the Stepper library 
Stepper myStep(steps,2,3,4,5); 	// create a Stepper object named myStep

//========== initialization ============
void setup()
{	
	} 
//========== Main Code ============
void loop()
{  int i = analogRead(joyV); // read the voltage of joystick’s V pot, range 0 to 1023
   i = map(i, 0,1023,0,100); // scale it for the stepper use, range 0 to 100
   if (i>60) 				// step motor rotates CW 
   {  myStep.setSpeed(2+(i-50)/10);	// set motor speed
      myStep.step(5);			// set the number of steps
   } 
   else if (i<40)			// step motor rotates CCW
   {  myStep.setSpeed((50-i)/10); 	// set motor speed
      myStep.step(-5); 			// set the number of steps 
   } 		
} 

