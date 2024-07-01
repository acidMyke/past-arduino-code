//========== ex9-1-1.ino ============
// DC motors: pins 2~7 connected to P18A1-1~P18A1-7 
// Bluetooth module: pins 11~10 connected to P28A-1~2  
// Humidity/Temperature Sensor: pin 12 connected to P27
//========== Global Declaration ============
const int EN_M1 = 2; 	// DCM1 enable pin connected to digital pin 2
const int M1_A = 3; 	// DCM1 A pin connected to digital pin 3
const int M1_B = 4; 	// DCM1 B pin connected to digital pin 4
const int EN_M2 =5; 	// DCM2 enable pin connected to digital pin 5
const int M2_A = 6; 	// DCM2 A pin connected to digital pin 6
const int M2_B = 7; 	// DCM2 B pin connected to digital pin 7
const int RX = 10; // Bluetooth TxD connected to digital pin 10 (cross connection)
const int TX = 11; // Bluetooth RxD connected to digital pin 11 (cross connection)
const int dht = 12; 	// DHT11 connected to digital pin 12
#include "DHT.h"	// include the DHT library 
DHT myDHT(dht,DHT11); 		// create a DHT object named myDHT
#include <SoftwareSerial.h>	// include the SoftwareSerial library 
SoftwareSerial myBT(RX, TX);	// create a SoftwareSerial object named myBT
float temp;			// declare float variable named temp 
//========== Initialization ============
void setup()
{  myBT.begin(9600); 		// open the software serial port at 9600 bps
   pinMode(EN_M1,OUTPUT); 	// configure digital pin 2 as an output  
   pinMode(M1_A,OUTPUT); 	// configure digital pin 3 as an output
   pinMode(M1_B,OUTPUT); 	// configure digital pin 4 as an output
   pinMode(EN_M2,OUTPUT); 	// configure digital pin 5 as an output 
   pinMode(M2_A,OUTPUT); 	// configure digital pin 6 as an output 
   pinMode(M2_B,OUTPUT); 	// configure digital pin 7 as an output 
   digitalWrite(EN_M1, 0); 	// turn off DCM1
   digitalWrite(EN_M2, 0); 	// turn off DCM2
}
//========== Main Code ============
void loop()
{  temp=myDHT.readTemperature(0); 	// read degrees Celsius 
   myBT.write(temp); 			// send temperature to Windows (in bytes)
   delay(100); 				// wait for 0.1 seconds 
   if ( myBT.available()) 		// if an instruction is received,
   {  int instruction = myBT.read();	// read instruction
      switch (instruction) 		// run the case statements according to the instruction 
      {  case	10:			// when instruction equals 10
		digitalWrite(EN_M1, 0); // stop DCM1
		break; 			// exit
	 case	11:			// when instruction equals 11
		digitalWrite(M1_A, 1); 	// DCM1 rotates CW
		digitalWrite(M1_B, 0); 	
		digitalWrite(EN_M1, 1); 	
		break; 			// exit
	 case	12:			// when instruction equals 12
		digitalWrite(M1_A, 0); 	// DCM1 rotates CW 
		digitalWrite(M1_B, 1); 	
		digitalWrite(EN_M1, 1); 	
		break; 			// exit
	 case	20:			// when instruction equals 20
		digitalWrite(EN_M2, 0); // stop DCM2
		break; 			// exit
	 case	21:			// when instruction equals 21
		digitalWrite(M2_A, 1); 	// DCM2 rotates CW
		digitalWrite(M2_B, 0); 	
		digitalWrite(EN_M2, 1); 	
		break; 			// exit
	 case	22:			// when instruction equals 22
		digitalWrite(M2_A, 0); 	// DCM2 rotates CCW 
		digitalWrite(M2_B, 1); 	
		digitalWrite(EN_M2, 1); 	
		break; 			// exit
      } 
    } 		
} 

