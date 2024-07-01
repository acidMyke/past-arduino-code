//========== ex3-2-1.ino ============
//========== Global Declaration ============
// pin 3 connected to 1W LED
#define LED  3	// LED connected to digital pin 3 
//========== Initialization ============
void setup()
{  Serial.begin(9600);		// open the serial port at 9600 bps
   pinMode(LED, OUTPUT); 	// configure digital pin 3 as an output 
   digitalWrite(LED, 1); 	// turn off LED
} 
//========== Main Code ============
void loop()
{  int PC; 		    // declare the variable PC 
   if (Serial.available()>0) // if incoming data on serial port is ready to read,
   {  PC = Serial.read()-48;// read brightness setting and convert ASCII to number
			   // range 0 to 9 (ASCII char 0 = 48 in decimal)
      PC = map(PC,0,9,0,255);// scale it for the dimmer use, range 0 to 255
      Serial.println(PC);   // set LED’s brightness according to the scaled value
      for (int x=0;x<PC;x++)	  // increase brightness gradually
      {  analogWrite(LED,255-x);  // drive LED
	 delay(25);		  // a delay of 25 ms
      }
      for (int x=255-PC;x<=255;x++)	// decrease brightness gradually   
      {  analogWrite(LED,x);		// drive LED
	 delay(25);			// a delay of 25 ms 
      }
    }
}

