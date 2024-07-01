//========== ex3-1-1.ino ============
//========== Global Declaration ============
// pin A2 connected to V pot’s wiper, pin 3 connected to 1W LED
#define potV  2	  // V pot’s wiper connected to analog pin A2
#define LED  3	  // 1W LED connected to digital pin 3
//========== Initialization ============
void setup()
{  pinMode(potV, INPUT);	// configure analog pin A2 as an input 
   pinMode(LED, OUTPUT); 	// configure digital pin 3 as an output  
   digitalWrite(LED, 1); 	// turn off LED 
} 
//========== Main Code ============
void loop()
{  int analogIn=0,pwm; 		   // declare integer variables analogIn, pwm 
   analogIn = analogRead(potV);	   // read the value of vertical pot, range 0 to 1023 
   pwm=~map(analogIn,0,1023,0,255);// scale it to use it with the PWM, range 0 to 255 
   analogWrite(LED,pwm);	   // PWM output according to the scaled value
}

