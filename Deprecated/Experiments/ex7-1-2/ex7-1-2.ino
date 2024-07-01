//========== ex7-1-2.ino ============
// pin 5 connected to P17B-1 (Y-axis servo M1, robot’s head)
// pin 6 connected to P17B-2 (X-axis servo M2, robot’s body)
//========== Global Declaration ============
#define  M1	5  // Y-axis servo M1 (robot’s head) connected to digital pin 5 
#define  M2	6  // X-axis servo M2 (robot’s body) connected to digital pin 6
#include <Servo.h>      // include the Servo library
Servo ServoM1;		// create a servo object named ServoM1 
Servo ServoM2;		// create a servo object named ServoM2 
//========== Initialization ============
void setup()
{  ServoM1.attach(M1);// attach Y-axis servo M1 (robot’s head) to digital pin 5
   ServoM2.attach(M2);// attach X-axis servo M2 (robot’s body) to digital pin 6
} 
//========== Main Code ============
void loop()
{  // robot’s head and body move to the middle, 90 position
   ServoM1.write(90); 	// drive the robot’s head to the middle, 90 position
   ServoM2.write(90); 	// drive the robot’s body to the middle, 90 position
   delay(500); 		// pause 0.5 seconds
   // lower robot’s head
   for(int i=90;i>0;i-=10)  // goes from 90 to 0 degrees in steps of 10 degrees
   {  ServoM1.write(i);     // drive the robot’s head to lower
      delay(150); 	    // a delay of 150 ms
   } 
   // three bows
   for(int i=0;i<3;i++)	       // makes 3 bows
   {  for(int j=0;j<180;j+=5)  // goes from 0 to 180 degrees in steps of 5 degrees
      {  ServoM1.write(j);     // drive the robot’s head to raise
	 delay(200); 	       // a delay of 200 ms 
      }
      delay(500); 	     // pause 0.5 seconds 
   for(int j=180;j>0;j-=10)  // goes from 180 to 0 degrees in steps of 10 degrees
      {  ServoM1.write(i);   // drive the robot’s head to lower
         delay(150); 	     // a delay of 150 ms
      }
      delay(250); 	     // pause 0.25 seconds 
   } 
   // robot’s body rotates from middle to left, then from left to right,
   // and the robot slowly raises its head at the same time
   for(int i=0;i<180;i+=5)  // goes from 0 to 180 degrees in steps of 5 degrees
   {  ServoM1.write(i);     // drive the robot’s head to raise 
      ServoM2.write(i);   // drive the robot’s body to rotate from left to right
      delay(150); 	  // a delay of 150 ms
   } 
   // robot’s body rotates from right to left, and
   // the robot rapidly makes a bow, and then raises its head 
   for(int i=180;i>0;i-=10)  // goes from 180 to 0 degrees in steps of 10 degrees
   {  ServoM1.write(180-i);  // drive the robot’s head to raise 
      ServoM2.write(i);   // drive the robot’s body to rotate from right to left
      delay(100); 	  // a delay of 100 ms
   } 
   delay(2000); 	  // a delay of 2 seconds 
}	

