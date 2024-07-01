//========== ex4-2-3.ino ============
// serial RGB LED connected to pin 11
// key 0 connected to pin 10 
//========== Global Declaration ============
#include  <Adafruit_NeoPixel.h>	// include the Adafruit_NeoPixel library
const int  PB = 10;		// key 0 connected to digital pin 10 (pressure sw)
const int  LED = 11;		// serial RGB LED connected to digital pin 11
Adafruit_NeoPixel strip=Adafruit_NeoPixel(20,LED,NEO_GRB+ NEO_KHZ800);
int  pb;			// declare integer variable named pb 
//========== Initialization ============
void setup()
{  strip.begin();		// initialize the Adafruit_NeoPixel library
   strip.show();		// update the whole strip
   pinMode(PB, INPUT);		// configure digital pin 10 as an input 
} 
//========== Mian Code ============
void loop()
{  pb = digitalRead(PB);	// read key 0 state 
   if (!pb)  rainbowFlash();	// if key 0 is pressed, call the rainbowFlash() 
   delay(150);			// pause 0.15 seconds 
}
//========== Functions ============
// static rainbow
// change the waiting value to adjust the display time
void rainbowFlash() 
{  for(int j=255; j>0; j/=2) 		// brightness decreases gradually 
   {  strip.setBrightness(j);		// adjust brightness
      for(int k=0; k< strip.numPixels(); k++)// fill the pixels one by one with a color
            strip.setPixelColor(k, Wheel((k* 256 / strip.numPixels()) & 255));
      strip.show();			// update the whole strip
      delay((255-j)/3);			// a delay of waiting value
   }
   for(int k=0; k< strip.numPixels(); k++)  // turn off all pixels
	strip.setPixelColor(k, 0);
   strip.show();			    // update the whole strip 
}
// Wheel() function  
// Input a wheel position between 0 and 255 to create color value
// The colors are a transition: red  blue  green  red
uint32_t  Wheel(byte WheelPos) 
{  WheelPos = 255 - WheelPos;
   if (WheelPos < 85)		// if wheel position < 85,
  	return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
	// fill color: R=255-3 x wheel position, G=0, B= 3 x wheel position
	// wheel position =0: R=255, G=0, B= 0; red 
	// wheel position =84: R=3, G=0, B= 252; blue 
	// The colors are a transition from red to blue.
    else if (WheelPos < 170)  // if 85 < wheel position < 170, 
    {  WheelPos -= 85; 	      // subtract 85 from the wheel position 
   	return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
	// fill color: R=0, G= 3 x wheel position, B= 255-3 x wheel position
	// wheel position =0 (85): R=0, G=0, B= 255; blue
	// wheel position =84 (169): R=0, G=252, B=3; green
	// The colors are a transition from blue to green.
    } 
    else 				// if wheel position > 170,
    {  WheelPos -= 170; 	// subtract 170 from the wheel position 
    	return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
	// fill color: R=3 x wheel position, G= 255 – 3 x wheel position, B= 0
	// wheel position =0 (170): R=0, G=255, B=0; green
	// wheel position =84 (255): R=252, G=3, B=0; red
	// The colors are a transition from green to red.
    }
}

