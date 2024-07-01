//========== ex2-4-2.ino ============
//========== Global Declaration ============
// pin 9 connected to RY1 relay 
// pin 3 connected to key 1 
// pin A5 connected to buzzer (external drive buzzer LS14-2)
#define PB  3	// key 1 connected to digital pin 3 
#define RY1  9	// RY1 relay connected to digital pin 9 
#define BZ1  A5	// external drive buzzer connected to analog pin A5 
int pB=0;	// declare a integer variable pB 
int rY=0;	// declare a integer variable rY 
//========== Initialization ============
void setup()
{  pinMode(PB, INPUT); 	   // configure digital pin 3 as an input 
   pinMode(RY1, OUTPUT);   // configure digital pin 9 as an output  
   pinMode(BZ1, OUTPUT);   // configure analog pin A5 as an output 
   digitalWrite(RY1, 1);   // de-energize RY1 relay 
   digitalWrite(BZ1, 0);   // turn off external drive buzzer LS14-2
} 
//========== Main Code ============
void loop()
{  pB=digitalRead(PB); 		      // read and store key 1 state in pB
   if (!pB) 			      // if key 1 is pressed, 
   {  tone(BZ1, 1000, 100);	      // external drive buzzer makes a beep 
      while(!pB) pB=digitalRead(PB);  // wait for key 1 released 
      rY=!rY;			      // invert the value of rY variable
    } 
    digitalWrite(RY1, rY);// manipulate the RY1 relay according to the rY value
}

