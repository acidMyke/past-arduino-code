//========== ex2-1-1.ino ============
//========== Global Declaration ============
// pins 2 and 3 connected to keys 0 and 1
// pin 4 connected to self drive buzzer, pin 5 connected to external drive buzzer 
#define  PB0 2		// key 0 connected to digital pin 2 
#define  PB1 3		// key 1 connected to digital pin 3 
#define  BZ0 4		// self drive buzzer connected to digital pin 4 
#define  BZ1 5		// external drive buzzer connected to digital pin 5
//========== Intialization ============
void setup()
{  pinMode(PB0, INPUT);	 // configure digital pin 2 as an input 
   pinMode(PB1, INPUT);  // configure digital pin 3 as an input
   pinMode(BZ0, OUTPUT); // configure digital pin 4 as an output 
   pinMode(BZ1, OUTPUT); // configure digital pin 5 as an output 
} 
//========== Main Code ============
void loop()
{  int in0=0,in1=0;		// declare integer variables in0 and in1 
   in0=digitalRead(PB0);	// read and store key 0 state in in0 
   if (!in0) digitalWrite(BZ0,1);  // if key 0 is pressed, the self drive buzzer beeps. 
   else	digitalWrite(BZ0,0);	// otherwise, self drive buzzer off
   in1=digitalRead(PB1);	// read and store key 1 state in in1 
   if (!in1)			// if key 1 is pressed,
    {	  tone(BZ1,1000);		// external drive buzzer generates a 1kHz tone
	      delay(100);		    // a delay of 0.1 second
	      noTone(BZ1);		  // turn the external drive buzzer off
    }
}

