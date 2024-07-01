//========== ex4-2-2.ino ============
// serial RGB LED connected to Arduino pin 11 
// V pot connected to Arduino pin A5 
//========== Global Declaration ============
#include <Adafruit_NeoPixel.h>	// include the Adafruit_NeoPixel library
const int pot = A5;		// V pot connected to analog pin A5 
const int LED = 11;		// serial RGB LED connected to digital pin 11
Adafruit_NeoPixel strip=Adafruit_NeoPixel(20,LED,NEO_GRB+ NEO_KHZ800);
//========== Initialization ============	
void setup()
{  strip.begin();		// initialize the Adafruit_NeoPixel library
   strip.show();		// update the whole strip
} 
//========== Main Code ============
void loop()
{  brightness();				// adjust brightness with V pot
   for(int i=0; i<3;i++)			// call the pili() 3 times
   {  pili(strip.Color(255,0,0),80);		// red 
      pili(strip.Color(0,255,0),80);		// green 
      pili(strip.Color(0,0,255),80);		// blue 
      pili(strip.Color(255,255,255),80);	// white 
   } 
   for(int i=0; i<3;i++)			// call the jumping() 3 times 
   {  jumping(strip.Color(255,0,0),70);		// red 
      jumping(strip.Color(0,255,0),70);		// green  
      jumping(strip.Color(0,0,255),70);		// blue 
      jumping(strip.Color(255,255,255),70);	// white 
   } 
}
//========== Functions ============
//========== brightness() function   ============
// pot connected to analog pin, strip is the Adafruit_NeoPixel object name
void brightness()
{  int x=analogRead(pot);
   strip.setBrightness(x/4);
} 
// pili() function
// two ON LEDs run from the middle to both ends, and then from both ends to the middle
// change the waiting value to adjust painting speed 
void pili(uint32_t c24, uint8_t waiting) 
{  // from the middle to both ends 
   for(int i=0; i<strip.numPixels()/2; i++) 		// fill the pixels one by one with a color
   {  brightness(); 					// adjust brightness with V pot
      strip.setPixelColor(strip.numPixels()/2-1-i, c24);// set the left pixels color 
      strip.setPixelColor(strip.numPixels()/2+i, c24);	// set the right pixels color 
      strip.show();					// update the whole strip
      delay(waiting); 					// a delay of waiting value 
      strip.setPixelColor(strip.numPixels()/2-1-i, 0);	// turn the left pixels off
      strip.setPixelColor(strip.numPixels()/2+i, 0); 	// turn the right pixels off 
   }
   // from both ends to the middle
   for(int i=0; i<strip.numPixels()/2; i++) 		// fill the pixels one by one with a color
   {  brightness(); 					// adjust brightness with V pot
      strip.setPixelColor(i, c24); 			// set the color of the left pixels 
      strip.setPixelColor(strip.numPixels()-1-i, c24); 	// set the right pixels color 
      strip.show();					// update the whole strip
      delay(waiting); 					// a delay of waiting value 
      strip.setPixelColor(i, 0); 			// turn the left pixels off
      strip.setPixelColor(strip.numPixels()-1-i, 0); 	// turn the right pixels off
   }
}
// jumping() function
// change the waiting value to adjust the chasing speed
void jumping(uint32_t color, uint8_t waiting) 
{  for (int i=0; i<10; i++)   			// repeat 10 times
   {  brightness(); 				// adjust brightness with V pot
      for (int cShift=0; cShift < 3; cShift ++) 
      {  for (int j=0; j < strip.numPixels()/2; j+=3) // turn every third pixel on 
	 {  strip.setPixelColor(strip.numPixels()/2-1-j+cShift, color); // left pixels
	    strip.setPixelColor(strip.numPixels()/2+j+cShift, color);	// right pixels
	 } 
	 strip.show();				        // update the whole strip
	 delay(waiting); 				// a delay of waiting value 
	 for (int j=0; j < strip.numPixels()/2; j+=3)   // turn every third pixel off 
	 {  strip.setPixelColor(strip.numPixels()/2-1-j+cShift, 0); // left pixels
	    strip.setPixelColor(strip.numPixels()/2+j+cShift, 0);   // right pixels
	 } 
       }
   }
}

