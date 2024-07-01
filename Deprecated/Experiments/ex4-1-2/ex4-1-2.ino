//========== ex4-1-2.ino ============
// com pins connected to pins 7, 6, 5, 4
// RGB pins connected to pins 10, 9, 11 
//========== Global Declaration ============
const int scan[]={4,5,6,7};  // scan outputs connected to digital pins 4-7
const int LED[]={11,9,10};  // color outputs connected to digital pins 9-11 
const int color[]=	    // declare basic color array (BGR) for 8 colors
  {1,1,1,  1,1,0,  1,0,0,  1,0,1,  0,0,1,  0,1,1,  0,1,0,  0,0,0}; 
//========== Initialization ============
void setup()
{  for(int i=0;i<4;i++) 
   {  pinMode(scan[i], OUTPUT); // configure digital pins 4 to 7 as outputs
      digitalWrite(scan[i], 1); // disable scan outputs (turn all LEDs off)
   }
   for(int i=0;i<3;i++)
   {  pinMode(LED[i], OUTPUT);	// configure digital pins 9 to 11 as outputs
      digitalWrite(LED[i], 1); 	// disable color outputs (turn all LEDs off)
   }
} 
//========== Main Code ============
void loop()
{ 
  for(int CNT=0;CNT<10;CNT++)		// repeat the for loop 10 times
	  for(int c=0;c<8;c++)		// the index of color array 
      for(int i=0;i<50;i++)	// repeat 50 times, about 4*50=200 ms
		    for(int j=0;j<4;j++)	// scan 4 RGB LEDs
		    {  
		      for(int k=0;k<3;k++)	// fill color 
			      digitalWrite(LED[k], color[(c+j)*3+k]); 
		      digitalWrite(scan[3-j], 0);	// enable scan outputs
		      delay(1);			// a delay of 1 ms
		      digitalWrite(scan[3-j], 1);	// disable scan outputs
		    }
    delay(2000);				// wait for 2 seconds
} 

