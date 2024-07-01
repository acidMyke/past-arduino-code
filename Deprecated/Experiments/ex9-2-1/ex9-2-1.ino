//========== ex9-2-1.ino ============
// serial RGB LED connection: pin 7 connected to P10B 
// Bluetooth module connections: pins 11~10 connected to P28A-2~1 
// Humidity/Temperature Sensor connection: pin 12 connected to P27 
//========== Global Declaration ============
const int RGB = 7; 		// serial RGB LED connected to digital pin 7
const int RX = 10; 	// Bluetooth TxD connected to digital pin 10 (cross connection)
const int TX = 11; 	// Bluetooth RxD connected to digital pin 11 (cross connection)
const int dht = 12; 		// DHT11 connected to digital pin 12
#include "DHT.h"		// include the DHT sensor library 
DHT myDHT(dht,DHT11); 		// create a DHT object named myDHT
#include <SoftwareSerial.h>	// include the SoftwareSerial library 
SoftwareSerial myBT(RX, TX);	// create a SoftwareSerial object named myBT
float temp,temp0=0;		// declare variable named temp 
#include <Adafruit_NeoPixel.h> 	// include the Adafruit_NeoPixel library
Adafruit_NeoPixel LED=Adafruit_NeoPixel(20,RGB,NEO_GRB+NEO_KHZ800);
//========== Initialization ============
void setup()
{  myBT.begin(9600); 		// open the software serial port at 9600 bps
   pinMode(RGB,OUTPUT); 	// configure digital pin 7 as an output
   LED.begin(); 		// initialize the Adafruit_NeoPixel library
   LED.show(); 			// update the whole strip
}
//========== Main Code ============
void loop()
{  temp=myDHT.readTemperature(0); // read temperature Celsius 
   if (temp!=temp0) 		  // a change in temperature
   {  myBT.write(temp); 	  // send new temperature to Android (in bytes)
      temp0=temp; 		  // save new temperature value
   }
   delay(100); 			  // wait for 0.1 seconds
   if ( myBT.available()) 		// if an instruction is received,   
   {  int instruction = myBT.read();	// read instruction   
      switch (instruction) 		// run the case statements according to the instruction
      {  case	'A' :			// when instruction equals A,
		knight(); 		// call the knight() function
		break; 			// exit
	 case	'B':			// when instruction equals B, 
		wiper(); 		// call the wiper() function
		break; 			// exit
	 case	'C':			// when instruction equals C, 
		eyebrows(); 		// call the eyebrows() function
		break; 			// exit
	 case	'D':			// when instruction equals D, 
		frog(); 		// call the frog() function
		break; 			// exit
	 case	'E':			// when instruction equals E, 
		for(int i=0;i<8;i++) 	// execute the for loop 8 times
		    rainbow1(50); 	// call the rainbow1() function
		break; 			// exit
	 case	'F':			// when instruction equals F, 
		rainbow2(3,50); 	// call the rainbow2() function (3 times)
		break; 			// exit
       } 
    } 		
} 
//========== Functions ================
//========== knight() function ============
void knight()
{  pili1(LED.Color(50,0,0),50);	// red
   pili1(LED.Color(0,50,0),50);	// green
   pili1(LED.Color(0,0,50),50);	// blue
}
//========== wiper() function ============
void wiper()
{  for(int i=0; i<3;i++)		// call the pili2() 3 times
   {  pili2(LED.Color(30,0,0),100);	// red
      pili2(LED.Color(0,30,0),100);	// green
      pili2(LED.Color(0,0,30),100);	// blue
   } 
}
//========== eyebrows() function ============
void eyebrows()
{  for(int i=0; i<3;i++)		// call the pili3() 3 times
   {  pili3(LED.Color(30,0,0),50);	// red
      pili3(LED.Color(0,30,0),50);	// green
      pili3(LED.Color(0,0,30),50);	// blue
   } 
}
//========== frog() function ============
void frog()
{  for(int i=0; i<3;i++)		// call the jumping() 3 times
   {  jumping(LED.Color(30,0,0),65);	// red
      jumping(LED.Color(0,30,0),65);	// green
      jumping(LED.Color(0,0,30),65);	// blue
   } 
}
//========== pili1() function ============
void pili1(uint32_t c24, uint8_t waiting) 
{  // an ON LED shifts right
   for(int i=0; i<LED.numPixels(); i++)	// fill the pixels one by one with a color
   {  LED.setPixelColor(i, c24);	// set the color of pixels 
      LED.show();			// update the whole strip 
      delay(waiting); 			// a delay of waiting value
      LED.setPixelColor(i, 0); 		// turn all pixels off 
   }
   // an ON LED shifts left 
   for(int i=0; i<LED.numPixels(); i++) 	// fill the pixels one by one with a color
   {  LED.setPixelColor(LED.numPixels()-1-i, c24);  // set the color of pixels
      LED.show();				    // update the whole strip
      delay(waiting); 				    // a delay of waiting value
      LED.setPixelColor(LED.numPixels()-1-i, 0);    // turn all pixels off 
   }
   clearLED();					    // turn all LEDs off 
}
//========== pili2() function ============
void pili2(uint32_t c24, uint8_t waiting) 
{  // turn on pixels from left to middle, turn on pixels from middle to right 
   for(int i=0; i<LED.numPixels()/2; i++) 	// fill the pixels one by one with a color
   {  LED.setPixelColor(i, c24);			// set the left pixels color
      LED.setPixelColor(LED.numPixels()/2+i, c24);	// set the right pixels color
      LED.show();					// update the whole strip
      delay(waiting); 					// a delay of waiting value
   }
   // turn off LEDs from middle to left, and turn off LEDs from right to middle
   for(int i=0; i<LED.numPixels()/2; i++) 	// fill the pixels one by one with a color
   {  LED.setPixelColor(LED.numPixels()/2-1-i, 0);	// turn the left pixels off
      LED.setPixelColor(LED.numPixels()-1-i, 0);	// turn the right pixels off
      LED.show();					// update the whole strip
      delay(waiting); 					// a delay of waiting value
   }
   clearLED();						// turn all LEDs off
}
//========== pili3() function ============
void pili3(uint32_t c24, uint8_t waiting) 
{  // turn on a single pixel from middle to left, and turn on a single pixel from middle to right
   for(int i=0; i<LED.numPixels()/2; i++) 	// fill the pixels one by one with a color
   {  LED.setPixelColor(LED.numPixels()/2-1-i, c24);	// turn the left pixels on 
      LED.setPixelColor(LED.numPixels()/2+i, c24);	// turn the right pixels on
      LED.show();					// update the whole strip
      delay(waiting); 					// a delay of waiting value
      LED.setPixelColor(LED.numPixels()/2-1-i, 0);	// turn the left pixels off
      LED.setPixelColor(LED.numPixels()/2+i, 0);	// turn the right pixels on
    }
    clearLED();						// turn all LEDs off 
}
//========== jumping() function ============
void jumping(uint32_t color, uint8_t waiting) 
{  for (int i=0; i<6; i++)   	  // repeat 6 times
   {  for (int cShift=0; cShift < 3; cShift ++) 
      {  for (int j=0; j < LED.numPixels()/2; j+=3)   // turn every third pixel on
	 {  LED.setPixelColor(LED.numPixels()/2-1-j+cShift, color); // left pixels 
	    LED.setPixelColor(LED.numPixels()/2+j+cShift, color);   // right pixels
	 } 
	 LED.show();		        // update the whole strip
	 delay(waiting);		// a delay of waiting value
	 for (int j=0; j < LED.numPixels()/2; j+=3)     // turn every third pixel off
	 {  LED.setPixelColor(LED.numPixels()/2-1-j+cShift, 0); // left pixels 
	    LED.setPixelColor(LED.numPixels()/2+j+cShift, 0);	// right pixels
	 } 
      }
   }
   clearLED();				    // turn all LEDs off
}
//========== rainbow1() function ============
// static rainbow
void rainbow1(uint8_t waiting) 
{  for(int j=0; j<256; j+=8) 		    // decrease brightness gradually 
   {  LED.setBrightness(j/2);		    // set the brightness
      for(int k=0; k<LED.numPixels(); k++)  // fill the pixels one by one with a color
	  LED.setPixelColor(k, Wheel((k* 256 / LED.numPixels()) & 255));
      LED.show();			    // update the whole strip 
      delay((255-j)/3);			    // a delay of waiting value
   }
   clearLED();				    // turn all LEDs off 
}
//========== rainbow2() function ============
// counts represent the number of cycles
// change the waiting value to adjust the display time
void rainbow2(uint8_t counts, uint8_t waiting) 
{  for(int i=0; i<counts; i++) 	    // cycle the rainbow “counts” times 
   {  LED.setBrightness((i+1)*25);  // set the brightness
      for(int j=0; j<256; j++) 	    // cycle all 256 colors in the wheel
      {  for(int k=0; k< LED.numPixels(); k++)	// fill the pixels one by one with a color
	     LED.setPixelColor(k, Wheel(((k* 256 /LED.numPixels()) + j) & 255));
	 LED.show();		// update the whole strip
	 delay(waiting); 	// a delay of waiting value
      }
   }
   clearLED();    // turn all LEDs off
}
//========== Wheel() function ============
// Input a wheel position between 0 and 255 to create color value
// The colors are a transition: red  blue  green  red
uint32_t  Wheel(byte WheelPos) 
{  WheelPos = 255 - WheelPos;
   if (WheelPos < 85)		// if wheel position < 85
      return LED.Color(255 - WheelPos * 3, 0, WheelPos * 3);
      // fill color: R=255 - 3 x wheel position, G=0, B= 3 x wheel position
      // wheel position =0: R=255, G=0, B= 0; red
      // wheel position =84: R=3, G=0, B= 252; blue
      // The colors are a transition from red to blue
   else if (WheelPos < 170)   // if 85 < wheel position < 170,
   {  WheelPos -= 85; 	      // subtract 85 from the wheel position 
      return LED.Color(0, WheelPos * 3, 255 - WheelPos * 3);
      // fill color: R=0, G= 3 x wheel position, B= 255 - 3 x wheel position
      // wheel position =0 (85): R=0, G=0, B= 255; blue
      // wheel position =84 (169): R=0, G=252, B=3; green
      // The colors are a transition from blue to green.
   } 
   else 		    // if wheel position > 170
   {  WheelPos -= 170; 	    // subtract 170 from the wheel position 
      return LED.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
      // fill color: R=3 x wheel position, G= 255 – 3 x wheel position, B= 0
      // wheel position =0 (170): R=0, G=255, B=0; green
      // wheel position =84 (255): R=252, G=3, B=0; red
      // The colors are a transition from green to red.
   }
}
//========== clearLED() function ============
void  clearLED() 
{  for (int i=0;i<LED.numPixels();i++)	// fill the pixels one by one with a color
   LED.setPixelColor(i,0);		// turn all pixels off
   LED.show();				// update the whole strip
}

