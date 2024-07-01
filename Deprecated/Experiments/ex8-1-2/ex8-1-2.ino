//========== ex8-1-2.ino ============
// pin A0 connected to P7-2 (V pot) 
// pin A1 connected to P7-1 (H pot) 
// pins 3~8 connected to P18A1-1~ P18A1-6, DC motors
//========== Global Declaration ============
#define  EN12	3  	// EN12 connected to digital pin 3
#define  m4_1A	4  	// m4_1A connected to digital pin 4
#define  m4_2A	5  	// m4_2A connected to digital pin 5
#define  EN34	6  	// EN34 connected to digital pin 6
#define  m5_3A	7  	// m5_3A connected to digital pin 7
#define  m5_4A	8  	// m5_4A connected to digital pin 8
#define  pV	A0  	// pV (V pot) connected to analog pin A0 
#define  pH	A1  	// pH (H pot) connected to analog pin A1 
//========== Initialization ============
void setup()
{  pinMode(EN12,OUTPUT);	// configure digital pin 3 as an output 
   pinMode(m4_1A,OUTPUT);	// configure digital pin 4 as an output  
   pinMode(m4_2A,OUTPUT);	// configure digital pin 5 as an output  
   pinMode(EN34,OUTPUT);	// configure digital pin 6 as an output 
   pinMode(m5_3A,OUTPUT);	// configure digital pin 7 as an output  
   pinMode(m5_4A,OUTPUT);	// configure digital pin 8 as an output   
   digitalWrite(EN12, 0);	// disable drivers 1 and 2, DCM1 stops
   digitalWrite(m4_1A, 1);	// m4_1A outputs 1
   digitalWrite(m4_2A, 0);	// m4_2A outputs 0
   digitalWrite(EN34, 0);	// disable drivers 3 and 4, DCM2 stops
   digitalWrite(m5_3A, 1);	// m5_3A outputs 1
   digitalWrite(m5_4A, 0);	// m5_4A outputs 0
} 
//========== Main Code ============
void loop()
{  int V = analogRead(pV);  // read V pot’s output voltage of, range 0 to 1023
   int H = analogRead(pH);  // read H pot’s output voltage of, range 0 to 1023
   V = map(V,0,1023,0,255);//scale V pot’s value for m4 motor use, range 0 to 255
   H = map(H,0,1023,0,255);//scale H pot’s value for m5 motor use, range 0 to 255
   motorWrite(V, 0);	    // drive DCM1 using the scaled value
   motorWrite(H, 1);	    // drive DCM2 using the scaled value
}
//========== Functions ============
void motorWrite(int val, int motor)
{  if (motor) 				  // drive DCM2 
   {  if(val<128)			  // DCM2 rotates CCW
      {  digitalWrite(m5_3A, 0);	  // m5_3A outputs 0
	 digitalWrite(m5_4A, 1);	  // m5_4A outputs 1
	 analogWrite(EN34, (127-val)*2);  // EN34 outputs (127-val)*2 value
      } 
      else 				  // m5 motor (DCM2) rotates CW 
      {  digitalWrite(m5_3A, 1);	  // m5_3A outputs 1
	 digitalWrite(m5_4A, 0);	  // m5_4A outputs 0
	 analogWrite(EN34, (val-127)*2);  // EN34 outputs (val-127)*2 value
      }
    }
    else  				   // drive m4 motor (DCM1)
    {  if(val<128)			   // m4 motor (DCM1) rotates CCW
       {  digitalWrite(m4_1A, 0);	   // m4_1A outputs 0
	  digitalWrite(m4_2A, 1);	   // m4_2A outputs 1
	  analogWrite(EN12, (127-val)*2);  // EN12 outputs (127-val)*2 value
       } 
       else 				   // m4 motor (DCM1) rotates CW
       {  digitalWrite(m4_1A, 1);	   // m4_1A outputs 1
	  digitalWrite(m4_2A, 0);	   // m4_2A outputs 0
	  analogWrite(EN12, (val-127)*2);  // EN12 outputs (val-127)*2 value
       } 
    } 
    delay(500);			// change speed and direction every 0.5 seconds 
}

