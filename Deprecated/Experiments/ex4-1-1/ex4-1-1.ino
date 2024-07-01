//========== ex4-1-1.ino ============
// RGB LED com pins connected to pins 7, 6, 5, 4
// RGB LED pins R, G, B connected to pins 10, 9, 11 
//========== Global Declaration ============
const int scan[]={4,5,6,7};	// scan outputs connected to digital pins 4-7
const int LED[]={11,9,10};	// color outputs connected to digital pins 9-11
const int color0[]=		// declare a basic color array (BGR) 
  {0,0,0,  0,0,1,  0,1,0,  0,1,1,  1,0,0,  1,0,1,  1,1,0,  1,1,1}; 
const int color1[]=		// declare a mixing color array (BGR)
  {1,1,0,  1,0,1,  0,1,1,  0,0,0,  0,0,1,  0,1,0,  1,0,0,  1,1,1}; 
//========== Initialization ============
void setup()
{  for(int i=0;i<4;i++) 
   {  pinMode(scan[i], OUTPUT);   // configure digital pins 4-7 as outputs
      digitalWrite(scan[i], 1);   // disable scan outputs
   }
   for(int i=0;i<3;i++)
   {  pinMode(LED[i], OUTPUT);	  // configure digital pins 9-11 as outputs
      digitalWrite(LED[i], 1); 	  // disable color outputs
   }
} 
//========== Main Code ============
void loop()
{  // #1: 4 LEDs sequentially display a single color listed in Table 4-1, 
   // with max brightness, non-scanning, 1 second each
   for(int i=0;i<8;i++)// display white, cyan, magenta, blue, yellow, green, red, black
		       // in sequence
   {  for(int j=0;j<3;j++)		// fill color 
      digitalWrite(LED[j], color0[i*3+j]); 
      for(int j=0;j<4;j++)	digitalWrite(scan[j], 0);  // enable scan outputs
      delay(1000);					   // a delay of 1 second
      for(int j=0;j<4;j++)	digitalWrite(scan[j], 1);  // disable scan outputs
	
   } 
   // #2: LEDs DS10A to DS10D light in red, green, blue, and white, 
   // (scan mode) respectively, for 1 second
   for(int i=0;i<125;i++)		//repeat 125 times, about 8*125=1000 ms 
	for(int j=0;j<4;j++)		// scan 4 RGB LEDs
	{  for(int k=0;k<3;k++)		// fill color 
		digitalWrite(LED[k], color1[3*j+k]); 
	   digitalWrite(scan[3-j], 0);	// enable scan outputs
	   delay(2);			// a delay of 2 ms
	   digitalWrite(scan[3-j], 1);	// disable scan outputs
	} 
   // #3: LEDs DS10A to DS10D light in cyan, magenta, yellow, black 
   // (scan mode) respectively, for 1 second
   for(int i=0;i<125;i++)		// repeat 125 times, about 8*125=1000 ms
	for(int j=0;j<4;j++)		// scan 4 RGB LEDs 
	{  for(int k=0;k<3;k++)		// fill color 
		digitalWrite(LED[k], color1[12+3*j+k]); 
	   digitalWrite(scan[3-j], 0);	// enable scan outputs
	   delay(2);			// a delay of 2 ms
	   digitalWrite(scan[3-j], 1);	// disable scan outputs
	} 
   // #4: LEDs mixing color using PWM output and nested loops
   for(int R=0;R<256;R+=15)		// the outer for loop varies the brightness 
					// levels of red 0~255 in increments of 15 
   {  analogWrite(LED[2], R); 		// light red LEDs (fill red color)
      for(int G=0;G<256;G+=15)		// the middle for loop varies the brightness 
					// levels of green 0~255 in increments of 15
      {	analogWrite(LED[1], G); 	// light green LEDs (fill green color)
	for(int B=0;B<256;B+=15)	// the inner for loop varies the brightness 
					// levels of blue 0~255 in increments of 15 
	{  analogWrite(LED[0], B);	// light blue LEDs (fill blue color)
	for(int i=0;i<4;i++)		// enable scan outputs
	      digitalWrite(scan[i], 0);	
	delay(25);			// a delay of 25 ms
	for(int i=0;i<4;i++)		// disable scan outputs
	      digitalWrite(scan[i], 1);	
	}
      } 
   } 
}

