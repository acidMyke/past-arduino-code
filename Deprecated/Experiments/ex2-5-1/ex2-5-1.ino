//========== ex2-5-1.ino ============
//========== Global Declaration ============
// pin 4 connected to relay RY1, pin 3 connected to relay RY2 
// pin 8 connected to light sensor CDS, pin 9 connected to voice sensor MIC
#define RY1  4	  // RY1 relay connected to digital pin 4
#define RY2  3	  // RY2 relay connected to digital pin 3
#define CDS  8	  // CDS connected to digital pin 8
#define MIC  9	  // MIC connected to digital pin 9
int cds=0,mic=0;  // declare variables cds and mic for storing CDS and MIC states
//========== Initialization ============
void setup()
{  pinMode(CDS, INPUT);    // configure digital pin 8 as an input 
   pinMode(MIC, INPUT);    // configure digital pin 9 as an input 
   pinMode(RY1, OUTPUT);   // configure digital pin 4 as an output 
   pinMode(RY2, OUTPUT);   // configure digital pin 3 as an output 
   digitalWrite(RY1, 1);   // turn off the RY1 relay 
   digitalWrite(RY2, 1);   // turn off the Y2 relay 
} 
//========== Main Code ============
void loop()
{  cds=digitalRead(CDS); 	  // read and store CDS state in cds
   if (cds) digitalWrite(RY1, 1); // if high (a bright light), de-energize the RY1 relay 
   else  digitalWrite(RY1, 0);	  // otherwise (a dim light), energize the RY1 relay 
   mic=digitalRead(MIC); 	  // read and store MIC state in mic
   if (mic) digitalWrite(RY2, 0); // if high (high volume), energize the RY2 relay 
   else  digitalWrite(RY2, 1);	  // otherwise (low volume), de-energize the RY2 relay 
}

