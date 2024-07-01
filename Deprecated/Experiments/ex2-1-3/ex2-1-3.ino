//========== ex2-1-3.ino ============
//========== Global Declaration ============
// pin 2 connected to key 0
// pin 5 connected to external drive buzzer 
#define  PB0 2		// key 0 connected to digital pin 2  
#define  BZ1 5		// external drive buzzer connected to digital pin 5 
#define  speed 50	// define speed
// declare the frequency array    
const int tone0[]={494,523,587,659,698,784,880,988,1046,1175,1318};
// declare the note array 
const int song0[]={ 2,2,3,5,  6,5,6,7,  9,7,7,6,5,  6,
               7,9,9,7,9,  5,6,6,  2,7,7,6,5,  5,
               6,6,7,6,5,  3,2,3,5,  3,5,6,7,  9,
               9,9,10,9,7,  7,6,5,3,  2,7,7,6,5,  5, 100}; //100= termination number
// declare the beat array 
const int beat0[]={ 12,4,8,8,  8,4,4,16,  12,4,4,4,8,  32, 
               12,4,8,4,4,  12,4,16,  12,4,8,4,4,  32,
               12,4,8,4,4,  8,4,4,16,  12,8,8,8,  32,
               12,4,8,4,4,  8,4,4,16,  12,4,8,4,4,  32};
//========== Initialization ============
void setup()
{	pinMode(PB0, INPUT);	// configure digital pin 2 as an input 
	pinMode(BZ1, OUTPUT);	// configure digital pin 5 as an output 
} 
//========== Main Code ============
void loop()
{  int PB;			// declare an integer variable named PB 
   PB=digitalRead(PB0); 	// read and store key 0 state in PB 
   if (!PB)			// if key 0 is pressed,
   {  int i=0; 			// declare an integer variable i (array index)
      while(song0[i]!=100) // if not a termination character, execute the while loop
      {	int duration = speed*beat0[i]; 	     // calculate beats 
	tone(BZ1,tone0[song0[i]],duration);  // play the music
	delay(duration*1.3);	 	     // pause 
	i++;				// next tone 
      }
      noTone(BZ1); 			// muting
    }
}

