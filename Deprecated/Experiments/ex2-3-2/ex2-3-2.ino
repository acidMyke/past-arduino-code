//========== ex2-3-2.ino ============
//========== Global Declaration ============
// pins 13~7 connected to the segments a~g of 7-segment display 
// pin 6 connected to the colon (blinking seconds) of 7-segment display 
// pins 5~2 connected to digit enable pins of 7-segment display
const int seg7[]={13,12,11,10,9,8,7};  //segments a~g connected to digital pins 13~7
const int DD=6;			       // colon connected to digital pin 6
const int scanP[]={5,4,3,2};	       // digit enables D0~D3 connected to digital pins 5~2
byte disp[]={0,0,0,0};		       // declare display data array 
const byte mySeg7[]=		       // declare 7-segment code array
{  0xC0,0xF9,0xA4,0xB0,  0x99,0x92,0x82,0xF8,  //0~7
   0x80,0x90,0xA0,0x83,  0xA7,0xA1,0x86,0x8E};  //8~F
unsigned long t0=0,t1=0,t2=0;	    // declare time variables t0, t1, t2
int hs=0,second=0;		    // declare time variables hs and second
//========== Initialization ============
void setup()
{  for(int i=0;i<7;i++) 	  // configure digital pins 7 to 13 as outputs
	pinMode(seg7[i], OUTPUT);
   for(int i=0;i<4;i++) 	  // configure digital pins 2 to 5 as outputs
	pinMode(scanP[i], OUTPUT);
   pinMode(DD, OUTPUT); 	  // configure digital pin 6 as output  
   for(int i=0;i<4;i++) 	  // disable the 7-segment display
	digitalWrite(scanP[i], 1);
} 
//========== Main Code ============
void loop()
{  scanSeg7();			// scan the 7-segment display
   t1=millis();			// query time in ms 
   t2=t1-t0;			// calculate time difference
   if(t2>=500)			// if calculated time difference>= 0.5 seconds
   {  t0=t1;			// store the current time
      hs=!hs;			// activate blinking seconds 
      digitalWrite(DD,hs);				 
      if(hs)			// timing
      {	if(++second==60)	// if the number of seconds equals 60
	{  second=0; 		// reset the second value
	   if(disp[3]==9) 	// if units digit of minute=9 (need to carry)
	   {  disp[3]=0; 	// reset the units digit of minute to 0
	      if(disp[2]==5)	// if tens digit of minute=5 (need to carry)
	      {	disp[2]=0; 	// reset the tens digit of minute to 0
		if(disp[0]==2 && disp[1]==3)  // if hour value is 23,
		{  disp[0]=0; disp[1]=0; }    // reset the hour value
		else if(disp[1]==9)  // if units digit of hour=9 (need to carry)
		{  disp[1]=0;	 // reset the units digit of hour to zero
		   disp[0]++;    // increment the tens digit of hour (carry)
		}	
		else disp[1]++;	 // increment the units digit of hour (carry)
	       }	
	       else disp[2]++;	 // increment the tens digit of minute (carry)
      	    }
	    else disp[3]++;	 // increment the units digit of minute 
         }
      }
   }
}
//========== Functions ============
//=== writeSeg7() outputs 7-segment display data (4 decimal points not included) =====
void writeSeg7(byte x)
{  for(int i=0;i<7;i++)		// output 7-segment data 
   {  if((x&(1<<i))==0) digitalWrite(seg7[i],0);
      else digitalWrite(seg7[i],1); 			
   }
}
//=== scanSeg7() scans 7-segment display ============
void scanSeg7(void)
{  for(int i=0;i<4;i++)		    // digit scanning
   {  for(int j=0;j<4;j++)	    // disable digit enables (preventing motion blur) 
	  digitalWrite(scanP[j],1); 
      writeSeg7(mySeg7[disp[i]]);   // output 7-segment display data 
      digitalWrite(scanP[i],0);	    // enable digit enables 
      delay(1); 		    // a delay of 1 ms
   }
}

