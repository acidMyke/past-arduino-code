//========== ex2-3-1.ino ============
//========== Global Declaration ============
// pins 13~7 connected to segments a~g of 7-segment display 
// pins 6 connected to the colon (not used here)
// pins 5~2 connected to digit enable pins of 7-segment display 
const int seg7[]={13,12,11,10,9,8,7};  // segments a~g connected to digital pins 13-7
const int scanP[]={5,4,3,2};	       // digit enables D0~D3 connected to digital pins 5-2
const byte disp[]={2,0,1,5, 0,2,2,5};  // declare display data array
const byte mySeg7[]=		       // declare 7-segment code array
{  0xC0,0xF9,0xA4,0xB0,  0x99,0x92,0x82,0xF8,  // 0~7
   0x80,0x90,0xA0,0x83,  0xA7,0xA1,0x86,0x8E};  // 8~F
#define  speed  125 // define speed (times of repetition, switching time about 4ms*speed)
//========== Initialization ============
void setup()
{  for(int i=0;i<7;i++) 	    // configure digital pins 7 to 13 as outputs
	pinMode(seg7[i], OUTPUT);
   for(int i=0;i<4;i++) 	    // configure digital pins 2 to 5 as outputs
	pinMode(scanP[i], OUTPUT);
   for(int i=0;i<4;i++) 	    // turn off 7-segment display
	digitalWrite(scanP[i], 1);
} 
//========== Main Code ============
void loop()
{  int TMP=0;				// declare an integer variable TMP 
   for(int i=0;i<2;i++)			// display two 4-digit numbers 
   {  for(int j=0;j<speed;j++)		// scan each character 125 times
      {	for(int k=0;k<4;k++)		// digit scanning
	{  for(int l=0;l<4;l++)	        // disable digit enables (preventing motion blur)
		digitalWrite(scanP[l],1); 
	   writeSeg7(mySeg7[disp[4*i+k]]);  // output 7-segment display data
	   digitalWrite(scanP[k],0);	    // enable digit enables 
	   delay(1);			    // a delay of 1 ms
	 }
       }
    }
}
//========== Function ============
//=== writeSeg7() outputs 7-segment display data (4 decimal points not included) =======
void writeSeg7(byte x)
{  for(int i=0;i<7;i++)		// output 7-segment code 
   {  if((x&(1<<i))==0) digitalWrite(seg7[i],0);
      else digitalWrite(seg7[i],1); 			
   }
}

