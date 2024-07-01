//========== ex3-2-3.ino ============
//========== Global Declaration ============
#define CDS  A2		// CdS connected to analog pin A2
int cds,cds0; 		// declare integer variables cds,cds0 
//========== Initialization ============
void setup()
{  Serial.begin(9600);	// open the serial port at 9600 bps
   pinMode(CDS, INPUT);	// configure analog pin A2 as an input 
} 
//========== Main Code ============
void loop()
{  cds = analogRead(CDS);	 // read CDS output voltage, range 0 to 1023 
   if (cds!=cds0)	         // if the voltage is changed,
   {  cds0=cds;			 // store the voltage value in cds0
      cds=map(cds,0,1023,0,5000);// scale it for the detector use, range 0 to 5000 
      Serial.print(cds);		 // display the scaled value on Serial Monitor
      Serial.println(" mV");// display the “mV” string followed by a CR and an LF 
   }
   delay(1000);			 // a delay of 1 second
}

