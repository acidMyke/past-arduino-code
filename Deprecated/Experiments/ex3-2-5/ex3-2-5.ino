//========== ex3-2-5.ino ============
//========== Global Declaration ============
#define potV  A2		// V pot’s wiper connected to analog pin A2
int pot0=0,pot1=0,pot2=0;	// declare integer variables pot0, pot1, pot2 
//========== Initialization ============
void setup()
{  Serial.begin(9600);		// open the serial port at 9600 bps
   pinMode(potV, INPUT); 	// configure analog pin A2 as an input 
} 
//========== Main Code ============
void loop()
{  for(int i=0;i<10;i++)	// read 10 times
   {  pot2 = analogRead(potV);	// read V pot’s voltage, range 0 to 1023
      pot1 += pot2;		// accumulate the voltages read 
   } 
   pot1 /=10;			// pot1 divided by 10, ignore units digit
   if (pot0!=pot1)		// if the value is changed (new),
   {  pot0=pot1;		// store the value in pot0
      pot1=map(pot1,0,1023,0,5000);// scale it for the voltmeter use, range 0 to 5000
      Serial.print(pot1);    // display the scaled value on Serial Monitor window 
      Serial.println(" mV"); // display the “mV” string followed by a CR and an LF
      pot1=0;		    // reset pot1 to zero, for next measurement
   }
   delay(1000);		    // a delay of 1 second
}

