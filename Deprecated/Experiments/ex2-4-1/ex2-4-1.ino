//========== ex2-4-1.ino ============
//========== Global Declaration ============
// pin 9 connected to RY1 relay, pin 8 connected to RY2 relay 
// pin 3 connected to key 0 (OFF button), pin 2 connected to key 1 (ON button)
// A5 connected to buzzer 
#define ON  3	// keypad key 1 connected to digital pin 3 
#define OFF  2	// keypad key 0 connected to digital pin 2 
#define RY1  9	// RY1 relay connected to digital pin 9
#define RY2  8	// RY2 relay connected to digital pin 8
#define BZ1  A5	// external drive buzzer connected to analog pin A5 
int oN=0,oFF=0;	// declare integer variables oN and oFF for storing states of ON, OFF 
//========== Initialization ============
void setup()
{  pinMode(ON, INPUT); 	    // configure digital pin 3 as an input 
   pinMode(OFF, INPUT);     // configure digital pin 2 as an input 
   pinMode(RY1, OUTPUT);    // configure digital pin 9 as an output 
   pinMode(RY2, OUTPUT);    // configure digital pin 8 as an output 
   pinMode(BZ1, OUTPUT);    // configure analog pin A5 as an output 
   digitalWrite(RY1, 1);    // de-energize RY1 relay 
   digitalWrite(RY2, 1);    // de-energize RY2 relay 
   digitalWrite(BZ1, 0);    // turn off external drive buzzer LS14-2
} 
//========== Main Code ============
void loop()
{  oFF=digitalRead(OFF); 		// read and store key 0 state in oFF
   if (!oFF) 				// if key 0 is pressed,
   {  digitalWrite(RY1, 1); 		// de-energize RY1 relay 
      digitalWrite(RY2, 1);		// de-energize RY2 relay 
   } 
   else 
   {  oN=digitalRead(ON); 		// read and store key 1 state in oN
      if (!oN) 				// if key 1 is pressed,
      {  digitalWrite(RY1, 0); 		// energize RY1 relay 
	 for(int i=0;i<500;i++)		// repeat 500 times (500*10ms)
	 {  delay(10);			// wait for 10 ms
	    oFF=digitalRead(OFF);	// read and store key 0 state in oFF
	    if (!oFF)			// if key 0 is pressed,
	    {  digitalWrite(RY1, 1);	// de-energize RY1 relay 
	       break;			//exit
	    }
	  }
	  digitalWrite(RY1, 1);		// de-energize RY1 relay 
	  digitalWrite(RY2, 0);		// energize RY2 relay 
	}
    }
}

