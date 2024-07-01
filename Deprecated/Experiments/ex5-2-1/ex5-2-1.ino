//========== ex5-2-1.ino ============
// pins 12~10 connected to P13A-1~P13A-3; RS, RW, EN
// pins 5~2 connected to P13A-8~P13A-11, DB4~DB7
// LCD 1602 inserted in P13A1 header 
// pin 13 connected to P27, DHT11
// pin A0 connected to P6A-5, P6A-1 to GND, key 0 
//========== Global Declaration ============
#include <LiquidCrystal.h>		// include the LiquidCrystal library
#define  PB0  A0			// key 0 connected to analog pin A0
#include  "DHT.h"			// include the DHT sensor library
DHT  myDHT(13, DHT11);			// create a DHT object called myDHT
LiquidCrystal  myLCD(12,11,10, 5,4,3,2);// create a LiquidCrystal object named myLCD
//========== Initialization ============
void setup()
{  pinMode(PB0, INPUT); 		// configure analog pin A0 as an input  
   myLCD.begin(16, 2); 			// initialize the LiquidCrystal library
   myDHT.begin(); 			// initialize the DHT sensor library
} 	
//========== Main Code ============
void loop()
{  int pb=digitalRead(PB0);			    // read key 0
   if (!pb)					    // if key 0 is pressed,
   {  float Fahrenheit = myDHT.readTemperature(1);  // read temperature in Fahrenheit
      myLCD.clear(); 				    // clear screen 
      myLCD.setCursor(0,0); 		// set cursor position
      myLCD.print("Temperature: ");	// display string
      myLCD.print(Fahrenheit); 		// display temperature in degrees Fahrenheit
      float Humidity = myDHT.readHumidity();	// read humidity
      float hi = myDHT.computeHeatIndex(Fahrenheit, Humidity);// calculate heat index
      myLCD.setCursor(0,1); 		// set cursor position
      myLCD.print("HI: ");		// display string
      myLCD.print(hi); 			// display heat index
    }
    else 
    {  float Celsius = myDHT.readTemperature(0);  // read temperature in Celsius
       myLCD.clear(); 			// clear screen 
       myLCD.setCursor(0,0); 		// set cursor position
       myLCD.print("Temperature: ");	// display string
       myLCD.print(Celsius); 		// display temperature in degrees Celsius
       float Humidity = myDHT.readHumidity();	// read humidity
       myLCD.setCursor(0,1); 		// set cursor position
       myLCD.print("Humidity: ");	// display string
       myLCD.print(Humidity);	 	// display humidity 
     }
     delay(500); 			// a delay of 0.5 seconds
}

