//========== ex2-1-2.ino ============
//========== Global Declaration ============
// pins 2~4 connected to keys 0~2 
// pin 5 connected to external drive buzzer 
#define  PB0 2		// key 0 connected to digital pin 2 
#define  PB1 3		// key 1 connected to digital pin 3 
#define  PB2 4		// key 2 connected to digital pin 4 
#define  BZ1 5		// external drive buzzer connected to digital pin 5 
#define  Do  523	// define Do frequency
#define  Re  587	// define Re frequency
#define  Mi  659	// define Mi frequency
//========== Initialization ============
void setup()
{	pinMode(PB0, INPUT);	// configure key 0 as an input 
	pinMode(PB1, INPUT);	// configure key 1 as an input
	pinMode(PB2, INPUT);	// configure key 2 as an input 
	pinMode(BZ1, OUTPUT);	// configure external drive buzzer as an output 
} 
//========== Main Code ============
void loop()
{	int in0,in1,in2;	    //declare integer variables in0, in1, in2 
	in0=digitalRead(PB0);	// read key 0 state and store it in in0 
	if (!in0)		    // if key 0 is pressed,
	{	tone(BZ1,Do);	// external drive buzzer plays a “Do” 
		delay(200);	  // a delay of 0.2 seconds
		noTone(BZ1);	// turn external drive buzzer off
	}
	in1=digitalRead(PB1);	// read key 1 state and store it in in1 
	if (!in1)		    // if key 1 is pressed
	{	tone(BZ1,Re);	// external drive buzzer plays a “Re” 
		delay(200);	  // a delay of 0.2 seconds
		noTone(BZ1);	// turn external drive buzzer off
	}
	in2=digitalRead(PB2);	// read key 2 state and store it in in2 
	if (!in2)		    // if key 2 is pressed,   
	{	tone(BZ1,Mi);	// external drive buzzer plays a “Mi” 
		delay(200);	  // a delay of 0.2 seconds
		noTone(BZ1);	// turn the external drive buzzer off
	}
}

