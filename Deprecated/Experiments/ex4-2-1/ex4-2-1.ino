//========== ex4-2-1.ino ============
// serial RGB LED connected to pin 11
// V pot connected to pin A5, key 0 connected to pin 10
//========== Global Declaration ============
#include <Adafruit_NeoPixel.h>		// include the Adafruit_NeoPixel library
const int  pot = A5;			// V pot’s wiper connected to analog pin A5 
const int  PB = 10;			// key 0 connected to digital pin 10
const int  LED = 11;			// serial RGB LED connected to digial pin 11
Adafruit_NeoPixel strip=Adafruit_NeoPixel(20,LED,NEO_GRB+ NEO_KHZ800);
int sel=0,pb;				// declare integer variables sel and pb 
//========== Initialization ============
void setup()
{  strip.begin();			// initialize the Adafruit_NeoPixel library
   strip.show();			// update the whole strip
   pinMode(PB, INPUT);			// configure digital pin 10 as an input 
   pinMode(pot, INPUT);			// configure analog pin A5 as an input 
} 
//========== Main Code ============
void loop()
{  brightness();			// adjust brightness with V pot
   pb=digitalRead(PB);			// read and store key 0 state in pb 
   if (!pb)				// if key 0 is pressed, 
   {  delay(20);			// wait for 20 ms (debouncing)
      if(++sel==6) sel=0;		// increment the sel (x of switch statement) 
      display(sel);			// call the display()  
   } 
}
//========== Functions ============
//========== display() function ============
void display(int x)					
{  switch(x)			// run the case statements according to the x value
   {  case 0:				// when x equals 0,
	    painter(strip.Color(0,0,0),100);	// turn all LEDs off
	    break;
      case 1:				// when x equals 1,
	    scan(strip.Color(255,0,0),100);	// red LEDs testing
	    break;
      case 2:				// when x equals 2,
	    scan(strip.Color(0,255,0),100);	// green LEDs testing
	    break;
      case 3:				// when x equals 3,
	    scan(strip.Color(0,0,255),100);	// blue LEDs testing
	    break;
      case 4:				// when x equals 4,
	    theaterChase(strip.Color(127,0,0),40); // red LEDs chasing
	    theaterChase(strip.Color(0,127,0),40); // green LEDs chasing
	    theaterChase(strip.Color(0,0,127),40); // blue LEDs chasing
	    break;
      case 5:					// when x equals 5,
	    rainbow(25);			// rainbow pattern
	    rainbowCycle(10, 20);	        // rainbow cycle pattern
	    break;
    } 
} 
//==========  brightness() function   ============
// pot connected to analog input pin; strip is the name of Adafruit_NeoPixel object
void brightness()
{  int x=analogRead(pot);
   strip.setBrightness(x/4);
} 
// a single color painting
// fill color from left to right
// change the waiting value to adjust the painting speed
void painter(uint32_t c24, uint8_t waiting) 
{  for(int i=0; i<strip.numPixels(); i++)  // fill the pixels one by one with a color
   {  brightness(); 			   // adjust brightness with V pot
      strip.setPixelColor(i, c24); 	   // set pixel color 
      strip.show();			   // update the whole strip
      delay(waiting); 			   // a delay of waiting value 
   }
}
// scan() function
// fill color from left to right, and then turn off pixels from right to left
// change the waiting value to adjust the painting speed 
void scan(uint32_t c24, uint8_t waiting) 
{  for(int i=0; i<strip.numPixels(); i++)  // fill the pixels one by one with a color
   {  brightness(); 			   // adjust brightness with V pot
      strip.setPixelColor(i, c24); 	   // set pixel color 
      strip.show();			   // update the whole strip
      delay(waiting); 			   // a delay of waiting value 
   }
   for(int i=0; i<strip.numPixels(); i++) // fill the pixels one by one with a color
   {  brightness(); 			  // adjust brightness with V pot
      strip.setPixelColor(strip.numPixels()-1-i, 0);	// turn off all pixels
      strip.show();				// update the whole strip
      delay(waiting);				// a delay of waiting value 
   }
}
// theaterChase() function
// change the waiting value to adjust the chasing speed 
void theaterChase(uint32_t color, uint8_t waiting) 
{  for (int i=0; i<10; i++)   			   // repeat 10 times
   {  brightness(); 				   // adjust brightness with V pot
      for (int cShift=0; cShift < 3; cShift ++) 
      {  for (int j=0; j < strip.numPixels(); j+=3)// turn every third pixel on
	 strip.setPixelColor(j+cShift, color); 
	 strip.show();			          // update the whole strip
	 delay(waiting); 			  // a delay of waiting value 
	 for (int j=0; j < strip.numPixels(); j+=3) // turn every third pixel off
	 strip.setPixelColor(j+cShift, 0);
      }
    }
    for (int j=0; j < 20; j++)	// turn all pixels off
        strip.setPixelColor(j, 1);
    strip.show();		// update the whole strip
}
// rainbow() function 
// change the waiting value to adjust the display time 
void rainbow(uint8_t waiting) 
{  for(int i=0; i<256; i++) 		  // cycle all 256 colors in the wheel
   {  brightness(); 			  // adjust brightness with V pot
   for(int j=0; j<strip.numPixels(); j++) // turn every pixel on 
   strip.setPixelColor(j, Wheel((i+j) & 255));
   strip.show();			  // update the whole strip
   delay(waiting); 			  // a delay of waiting value 
   }
}
// rainbowCycle() function
// counts represent the number of rainbow cycles
// change the waiting value to adjust the display time
void rainbowCycle(uint8_t counts, uint8_t waiting) 
{  for(int i=0; i<counts; i++) 		// cycle the rainbow “counts” times
	for(int j=0; j<256; j++) 	// cycle all 256 colors in the wheel 
	{  brightness(); 		// adjust brightness with V pot
	   for(int k=0; k< strip.numPixels(); k++)//fill the pixels one by one with a color 
		strip.setPixelColor(k, Wheel(((k* 256 / strip.numPixels()) + j) & 255));
	   strip.show();		// update the whole strip
	   delay(waiting); 		// a delay of waiting value 
	}
}
// Wheel() function  
// Input a wheel position between 0 and 255 to create color value
// The colors are a transition: red  blue  green  red
uint32_t  Wheel(byte WheelPos) 
{  WheelPos = 255 - WheelPos;
   if (WheelPos < 85)			// if wheel position < 85,
  	  return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
	  // fill color: R=255-3 x wheel position, G=0, B= 3 x wheel position
	  // wheel position=0: R=255, G=0, B= 0; red
	  // wheel position=84: R=3, G=0, B= 252; blue
	  // The colors are a transition from red to blue.
   else if (WheelPos < 170) 	// if 85 < wheel position < 170, 
   {  WheelPos -= 85; 		// subtract 85 from the wheel position 
          return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
          // fill color: R=0, G= 3 x wheel position, B= 255-3 x wheel position
	  // wheel position =0 (85): R=0, G=0, B= 255; blue
	  // wheel position =84 (169): R=0, G=252, B=3; green
	  // The colors are a transition from blue to green.
   } 
   else 			// if wheel position is greater than 170,
   {  WheelPos -= 170; 		// subtract 170 from the wheel position  
      return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
      // fill color: R=3 x wheel position, G= 255-3 x wheel position, B= 0
      // wheel position =0 (170): R=0, G=255, B=0; green
      // wheel position =84 (255): R=252, G=3, B=0; red
      // The colors are a transition from green to red.
   }
}

