//========== ex6-1-1.ino ============
// pin A0 connected to P6A-5, P6A-1 connected to GND (key 0)
// pin A1 connected to P14-2 (buzzer)
// pin 6 connected to P22B-1 (Trig pin)
// pin 7 connected to P22B-2 (Echo pin)
//========== Global Declaration ============
#define  trig	6	// Trig pin connected to digital pin 6
#define  echo	7	// Echo pin connected to digital pin 7
#define  PB  A0		// key 0 connected to analog pin A0
#define  BZ  A1		// buzzer connected to analog pin A1
int Width;		// declare an integer variable named Width 
int distance=0;		// declare an integer variable named distance 
//========== Initialization ============
void setup()
{  pinMode(PB, INPUT); 		// configure analog pin A0 as an input
   pinMode(BZ, OUTPUT); 	// configure analog pin A1 as an output
   digitalWrite(BZ, 1); 	// turn off buzzer
   pinMode(trig, OUTPUT);	// configure digital pin 6 as an output
   pinMode(echo, INPUT);	// configure digital pin 7 as an input
   Serial.begin(9600);		// open the serial port at 9600 bps
} 	
//========== Main Code ============
void loop()
{  int pb=digitalRead(PB);	// read key 0 state
   if (!pb)			// if key 0 is pressed, 
   {  tone(BZ,1000);		// generate a beep
      delay(100);		// a delay of 0.1 seconds
      noTone(BZ);		// no beeps generated
      for(int i=0;i<10;i++) 	// repeat measuring 10 times
	{  readUtrasonic(); 	// measure the distance 
	   distance+=Width; 	// accumulate the distance measurements
	   delay(50); 		// a delay of 0.05 seconds
	}
	distance/=10; 	 // calculate the average of 10 measurements
	Serial.print("Distance = "); // display character string
	Serial.print(distance); 	    // display distance value
	Serial.print("  cm"); 	    // display units
	Serial.println(); 	    // next line
    }
}
//========== Function ============
void readUtrasonic()
{  digitalWrite(trig, 1);	// trigger the ultrasonic sensor
   delayMicroseconds(20);	// a delay of 20 us
   digitalWrite(trig, 0);	// stop triggering the ultrasonic sensor
   Width = pulseIn(echo, HIGH);	// measure the width of echo pulse
   Width *= 0.0173;		// calculate distance
}

