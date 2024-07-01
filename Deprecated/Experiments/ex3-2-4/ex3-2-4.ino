//========== ex3-2-4.ino ============
//========== Global Declaration ============
#define MIC  A2		   // MIC connected to analog pin A2
int mic0=0,mic1=0,mic2=0;  // declare integer variables mic0,mic1,mic2 
//========== Initialization ============
void setup()
{  Serial.begin(9600);	   // open the serial port at 9600 bps
   pinMode(MIC, INPUT);    // configure analog pin A2 as an input 
} 
//========== Main Code ============
void loop()
{  for(int i=0;i<10;i++)	   // repeat 10 times
   {  mic2 = analogRead(MIC);	   // read MIC output voltage, range 0 to 1023
      mic1 += mic2;		   // accumulate the voltages 
   } 
   if (mic0!=mic1)		   // if the value is changed,
   {  mic0=mic1;		   // store the value in mic0
      mic1=map(mic1,0,1023,0,5000);//scale it for the detector use, range 0 to 5000
      Serial.print(mic1);   //display the scaled value in Serial Monitor window 
      Serial.println(" mV");//display the “mV” string followed by a CR and an LF
      mic1=0;		   // reset mic1 to zero, for next detection
   }
   delay(500);		   // a delay of 0.5 seconds
}

