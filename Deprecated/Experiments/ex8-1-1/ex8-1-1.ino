//========== ex8-1-1.ino ============
// pin A0 connected to P6A-5 (key 0), P6A-5 to GND
// pins 3~8 connected to P18A-1~ P18A-6, DC motors
//========== Global Declaration ============
#define  EN12	3	// EN12 connected to digital pin 3
#define  m4_1A	4	// m4_1A connected to digital pin 4
#define  m4_2A	5	// m4_2A connected to digital pin 5
#define  EN34	6	// EN34 connected to digital pin 6
#define  m5_3A	7	// m5_3A connected to digital pin 7
#define  m5_4A	8	// m5_4A connected to digital pin 8
#define  PB	A0	// key 0 connected to analog pin A0
//========== Initialization ============
void setup()
{  pinMode(PB,INPUT);		// configure analog pin A0 as an input  
   pinMode(EN12,OUTPUT);	// configure digital pin 3 as an output  
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
{  int pb = digitalRead(PB); 	// read key 0 state
   if(!pb) 			// if key 0 is pressed, 
   {  for(int i=0;i<3;i++)	//repeat 3 times
      {  digitalWrite(EN12, 1);	// enable drivers 1 and 2, DCM1 runs
	 delay(30000);		// a delay of 30 seconds
	 digitalWrite(EN12, 0);	// disable drivers 1 and 2, DCM1 stops
	 digitalWrite(EN34, 1);	// enable drivers 3 and 4, DCM2 runs
	 delay(30000);		// a delay of 30 seconds
	 digitalWrite(EN34, 0);	// disable drivers 3 and 4, DCM2 stops
      }
   }
}

