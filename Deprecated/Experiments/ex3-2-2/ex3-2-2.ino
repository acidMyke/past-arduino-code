//========== ex3-2-2.ino ============
//========== Global Declaration ============
//pin 3 connected to 1W LED
#define LED  3	// LED connected to digital pin 3 
char rec[6];	// declare a character array named rec 
//========== Initialization ============
void setup()
{  Serial.begin(9600);		// open the serial port at 9600 bps
   pinMode(LED, OUTPUT); 	// configure digital pin 3 as an output 
   digitalWrite(LED, 1); 	// turn off LED
} 
//========== Main Code ============
void loop()
{  int i,CNT; 			  // declare integer variables i and CNT 
   byte PC; 			  // declare a byte variable named PC 
   if (Serial.available()>0)	  // if valid data on the serial port, 
   {  for(i=0;i<2;i++) rec[i]=0;  // clear rec array
      CNT = Serial.readBytesUntil(13,rec,2);//read serial port data (2 bytes) 
                                   // and store in rec array (13=enter key)
      if (CNT==1) PC= rec[0]-48;   // if only one byte is read, 
                                   // convert ASCII char to number
      else PC= (rec[0]-48)*10+rec[1]-48;// if the input value > one byte, 
                                // convert two ASCII chars to two-digit number 
      if (PC>=0 && PC<100)	// if the input value is valid, 0 to 99
      {  map(PC,0,99,0,255);// scale it for the controller use, range 0 to 255
	 analogWrite(LED,255-PC);//set the LED brightness using the scaled value
      }
    }
    delay(1000);		//delay 1 second
}

