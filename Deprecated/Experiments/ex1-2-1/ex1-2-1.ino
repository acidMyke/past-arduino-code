//========== ex1-2-1.ino ============
//========== Global Declaration ============
// pins 2~11 connected to P9 (LED Bar, active-low drive 
const int LED[]={2,3,4,5,6,7,8,9,10,11};  // LED Bar pins connected to digital pins 2-11 
//========== Initialization ============
void setup()
{	for(int i=0;i<10;i++)
		{	pinMode(LED[i], OUTPUT);  // configure digital pins 2-11 as outputs 
			digitalWrite(LED[i], 1);  // turn all LEDs off
		} 
} 
//========== Main Code ============
void loop()
{	for(int i=0;i<10;i++)
		{	digitalWrite(LED[i], 0);  // turn on LEDs one by one from left to right 
			delay(100);		  // a delay of 0.1 seconds
			digitalWrite(LED[i], 1);  // turn off LEDs one by one from left to right 
		}
		for(int i=9;i>=0;i--)
		{	digitalWrite(LED[i], 0);  // turn on LEDs one by one from right to left
			delay(100);		  // a delay of 0.1 seconds
			digitalWrite(LED[i], 1);  // turn off LEDs one by one from right to left 
		}
}

