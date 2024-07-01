//========== ex3-1-2.ino ============
//========== Global Declaration ============
// pin A0 connected to joystick’s tact switch, pin A2 connected to joystick’s V pot 
// pin 3 connected to 1W LED
#define PB  A0	  // joystick’s tact switch connected to analog pin A0
#define potV  2	  // V pot’s wiper connected to analog pin A2
#define LED  3	  // 1W LED connected to digital pin 3
//========== Initialization ============
void setup()
{  pinMode(PB, INPUT);		// configure analog pin A0 as an input 
   pinMode(potV, INPUT);	// configure analog pin A2 as an input 
   pinMode(LED, OUTPUT); 	// configure digital pin 3 as an output  
   digitalWrite(LED, 1); 	// turn off LED
} 
//========== Main Code ============
void loop()
{  int pb=1,analogIn=0,pwm;	// declare variables pb,analogIn,pwm 
   pb = digitalRead(PB);	// read tact switch’s state
   if (!pb)			// if the tact switch is pressed,
   {  digitalWrite(LED,0);	// 1W LED on, max brightness
      delay(500);		// a delay of 0.5 seconds
      digitalWrite(LED,1);	// turn off 1W LED
   }
   analogIn = analogRead(potV);	  // read the value of vertical pot, range 0 to 1023
   pwm=map(analogIn,0,1023,0,255);// scale it to use it with the pwm, range 0 to 255
   analogWrite(LED,pwm);	  // PWM output according to the scaled value
}

