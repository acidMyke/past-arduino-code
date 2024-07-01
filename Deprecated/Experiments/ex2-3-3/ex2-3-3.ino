//========== ex2-3-3.ino ============
//========== Global Declaration ============
// pins 13~6 connected to segments a~dp of 7-segment display 
// pins 5~2 connected to digit enable inputs D3~D0 of 7-segment display 
// pins 5~2 also connected to keypad row pins R0~R3 
// pins A0~A3 connected to keypad column pins C0~C3 
const int seg7[]={13,12,11,10,9,8,7,6};// segment pins connected to digital pins 13-6
const int scanP[]={5,4,3,2};	// row/digit enable pins connected to digital pins 5-2
const int keyP[]={A0,A1,A2,A3};	// column pins connected to analog pins A0-A3
byte disp[]={0,0,0,0};		// declare display data array 
const byte mySeg7[]=		// declare 7-segment code array
{	0xC0,0xF9,0xA4,0xB0,  0x99,0x92,0x82,0xF8,	// 0~7
	0x80,0x90,0xA0,0x83,  0xA7,0xA1,0x86,0x8E};	// 8~F
//========== Initialization ============
void setup()
{  for(int i=0;i<8;i++) 	  // configure digital pins 13-6 as outputs  
	pinMode(seg7[i], OUTPUT);
   for(int i=0;i<4;i++) 	  // configure digital pins 5-2 as outputs  
	pinMode(scanP[i], OUTPUT);
   for(int i=0;i<4;i++) 	  // configure analog pins A0-A3 as inputs  
	pinMode(keyP[i], INPUT);
   for(int i=0;i<4;i++) 	  // disable row/digit enables (LED display off)
	digitalWrite(scanP[i], 1);
} 
//========== Main Code ============
void loop()
{  scanKey4x4();	// scan 4x4 keypad
}
//========== Functions ============
//=== scanSeg7(): 7-segment display scanning (one digit) ============
void scanSeg7(int x) 		// scan digit x
{  for(int i=0;i<4;i++)		// disable row/digit enables
	digitalWrite(scanP[i],1); 
   int Seg=mySeg7[disp[x]]; 	// assign the display data of digit x to Seg 
   for(int i=0;i<8;i++)		// output 7-segment data 
   {	if((Seg&(1<<i))==0) digitalWrite(seg7[i],0);
	else digitalWrite(seg7[i],1); 			
   }
   digitalWrite(scanP[x],0);  // enable the digit enable of digit x 
   delay(1); 		      // a delay of 1 ms
   for(int i=0;i<8;i++)	      // turn off 7-segment display (preventing motion blur)
	digitalWrite(seg7[i],1);
}
//=== scanKey4x4(): 4x4 keypad scanning ============
void scanKey4x4(void)
{  int col,row,rowkey,keycode,dig;	// declare integer variables 
   for(int i=0;i<4;i++)	scanSeg7(i);	// scan 7-segment display
   for(row=0;row<4;row++)		// scan 4 digits
   {  for(int i=0;i<4;i++)		// row scanning 
	    digitalWrite(scanP[i],1); 
      digitalWrite(scanP[row],0);		
      for(col=0;col<4;col++)		    // read key state 
      {  if (!digitalRead(keyP[col]))       // if the key in a column is pressed,
	 {  while(!digitalRead(keyP[col]))  // wait for key released
	    {  for(int i=0;i<4;i++)	scanSeg7(i);  // scan 7-segment display
	       for(int i=0;i<4;i++)		      // disable digit enables 
		    digitalWrite(scanP[i],1); 
	       digitalWrite(scanP[row],0);	      // enable row enables (re-scan)
	    } 
	    keycode=4*row+col; 	// calculate key code 
	    for(int i=0;i<3;i++)	
	          disp[i]=disp[i+1];// shift elements in display data array one place
			    // disp[0] for thousands digit, disp[3] for units digit
	    disp[3]=keycode;	// save new key code in disp[3] (units digit)
	    break;		// exit 
	  }
	}
    }
}

