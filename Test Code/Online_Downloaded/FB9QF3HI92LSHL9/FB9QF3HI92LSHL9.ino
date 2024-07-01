
// based on 
//Build your own RGB LED Cube v2 Code
//http://www.youtube.com/user/greatscottlab 

// with a LOT of code changes by me...
// I found that GREEN was must too bright and BLUE more than RED - so made an attempt to balance colour intensities.
// i changed scotts pin number for layer one from 14 to 19 due to a soldering malfunction of mine and had to swap pins.


#include "Tlc5940.h"               // don't forget to download the Tlc5940 lib from arduino playground and place it in you lib folder ( http://tlc5940arduino.googlecode.com/files/Tlc5940_r014_2.zip )
#include "digitalIOPerformance.h"  // don't forget to download the digitalIOPerformance lib from arduino playground and place it in you lib folder ( https://github.com/projectgus/digitalIOPerformance )
// the pins on the nano are confusing... 
#define LayerOne 14                // Gate of 1.MOSFET which connects to Layer "a" (anodes of all Strings in Layer "a")
#define LayerTwo 15                // Gate of 2.MOSFET which connects to Layer "b" (anodes of all StringS in Layer "b")
#define LayerThree 16              // Gate of 3.MOSFET which connects to Layer "c" (anodes of all Strings in Layer "c")
#define LayerFour 17               // Gate of 4.MOSFET which connects to Layer "d" (anodes of all Strings in Layer "d")
#define Potentiometer 18           // 10k potentiometer to set the brightness of the cube

#define NUM_PATTERNS 19
			  
int LayerDuration = 4000;   // ON time of each Layer in microseconds      
unsigned long oldMicros = 0;// starting counter to decide when if(micros()>=oldMicros)is true to change active layer, count++1, MatrixUpdate(); don't know what micros() is? Look here: http://arduino.cc/de/Reference/Micros#.UygzAIWmWd4
int count=1;                // starting counter which is included in if() statement to change the shown picture, not necessary when using a static picture
int brightg=2045;              // set brightness for all Strings(4095=20mA, 0=0ma, 1000=4.88mA,....). If you want individually brightness for a String you have to change the value in tab "function"
int brightb=3095;              
int brightr=4095;        // red is much lighter than the other colours - we need to increase it in line with the other colours 
int randred, randgreen, randblue;
int loopcnt=50;
int potent, factor;
int drops;

#define AchR 0 //defines the "A" (RED)string for the tlc5940 -->OUTPUT 0 first TLC5940
#define BchR 1 //defines the "B" (RED)string for the tlc5940 -->OUTPUT 1
#define CchR 2 //defines the "C" (RED)string for the tlc5940 -->OUTPUT 2
#define DchR 3 //defines the "D" (RED)string for the tlc5940 -->OUTPUT 3
#define EchR 4 //defines the "E" (RED)string for the tlc5940 -->OUTPUT 4
#define FchR 5 //defines the "F" (RED)string for the tlc5940 -->OUTPUT 5
#define GchR 6 //defines the "G" (RED)string for the tlc5940 -->OUTPUT 6
#define HchR 7 //defines the "H" (RED)string for the tlc5940 -->OUTPUT 7
#define IchR 8 //defines the "I" (RED)string for the tlc5940 -->OUTPUT 8
#define JchR 9 //defines the "J" (RED)string for the tlc5940 -->OUTPUT 9
#define KchR 10//defines the "K" (RED)string for the tlc5940 -->OUTPUT 10
#define LchR 11//defines the "L" (RED)string for the tlc5940 -->OUTPUT 11
#define MchR 12//defines the "M" (RED)string for the tlc5940 -->OUTPUT 12
#define NchR 13//defines the "N" (RED)string for the tlc5940 -->OUTPUT 13
#define OchR 14//defines the "O" (RED)string for the tlc5940 -->OUTPUT 14
#define PchR 15//defines the "P" (RED)string for the tlc5940 -->OUTPUT 15
#define AchG 16//defines the "A" (GREEN)string for the tlc5940 -->OUTPUT 0 second TLC5940
#define BchG 17//defines the "B" (GREEN)string for the tlc5940 -->OUTPUT 1
#define CchG 18//defines the "C" (GREEN)string for the tlc5940 -->OUTPUT 2
#define DchG 19//defines the "D" (GREEN)string for the tlc5940 -->OUTPUT 3
#define EchG 20//defines the "E" (GREEN)string for the tlc5940 -->OUTPUT 4
#define FchG 21//defines the "F" (GREEN)string for the tlc5940 -->OUTPUT 5
#define GchG 22//defines the "G" (GREEN)string for the tlc5940 -->OUTPUT 6
#define HchG 23//defines the "H" (GREEN)string for the tlc5940 -->OUTPUT 7
#define IchG 24//defines the "I" (GREEN)string for the tlc5940 -->OUTPUT 8
#define JchG 25//defines the "J" (GREEN)string for the tlc5940 -->OUTPUT 9
#define KchG 26//defines the "K" (GREEN)string for the tlc5940 -->OUTPUT 10
#define LchG 27//defines the "L" (GREEN)string for the tlc5940 -->OUTPUT 11
#define MchG 28//defines the "M" (GREEN)string for the tlc5940 -->OUTPUT 12
#define NchG 29//defines the "N" (GREEN)string for the tlc5940 -->OUTPUT 13
#define OchG 30//defines the "O" (GREEN)string for the tlc5940 -->OUTPUT 14
#define PchG 31//defines the "P" (GREEN)string for the tlc5940 -->OUTPUT 15
#define AchB 32//defines the "A" (BLUE)string for the tlc5940 -->OUTPUT 0 third TLC5940
#define BchB 33//defines the "B" (BLUE)string for the tlc5940 -->OUTPUT 1
#define CchB 34//defines the "C" (BLUE)string for the tlc5940 -->OUTPUT 2
#define DchB 35//defines the "D" (BLUE)string for the tlc5940 -->OUTPUT 3
#define EchB 36//defines the "E" (BLUE)string for the tlc5940 -->OUTPUT 4
#define FchB 37//defines the "F" (BLUE)string for the tlc5940 -->OUTPUT 5
#define GchB 38//defines the "G" (BLUE)string for the tlc5940 -->OUTPUT 6
#define HchB 39//defines the "H" (BLUE)string for the tlc5940 -->OUTPUT 7
#define IchB 40//defines the "I" (BLUE)string for the tlc5940 -->OUTPUT 8
#define JchB 41//defines the "J" (BLUE)string for the tlc5940 -->OUTPUT 9
#define KchB 42//defines the "K" (BLUE)string for the tlc5940 -->OUTPUT 10
#define LchB 43//defines the "L" (BLUE)string for the tlc5940 -->OUTPUT 11
#define MchB 44//defines the "M" (BLUE)string for the tlc5940 -->OUTPUT 12
#define NchB 45//defines the "N" (BLUE)string for the tlc5940 -->OUTPUT 13
#define OchB 46//defines the "O" (BLUE)string for the tlc5940 -->OUTPUT 14
#define PchB 47//defines the "P" (BLUEstring for the tlc5940 -->OUTPUT 15

int REDLEDs[]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
				0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
				0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,				
				0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

int GREENLEDs[]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
				0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
				0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,				
				0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
                 
int BLUELEDs[]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
				0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
				0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,				
				0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

void setup()    
{
  pinMode(LayerOne, OUTPUT);                   // declare arduino nano pin A0(LayerOne) as OUTPUT
  pinMode(LayerTwo, OUTPUT);                   // declare arduino nano pin A1(LayerTwo) as OUTPUT
  pinMode(LayerThree, OUTPUT);                 // declare arduino nano pin A2(LayerThree) as OUTPUT
  pinMode(LayerFour, OUTPUT);                      // declare arduino nano pin A3(LayerFour) as OUTPUT
  pinMode(Potentiometer, INPUT);               // declare arduino nano pin A4(Potentiometer) as INPUT for brightness value
  Tlc.init();                                  // configures the arduino to use the tlc5940, be sure to connect the arduino correctly to the tlc 
  Serial.begin(115200);

 
 /*          ARDUINO                                         TLC5940                            
              13|-> SCLK (pin 25)           OUT1 String "B" |1     28| OUT0 String "A"
              12|                           OUT2 String "C" |2     27|-> GND (VPRG)
              11|-> SIN (pin 26)            OUT3 String "D" |3     26|-> SIN (pin 11)
              10|-> BLANK (pin 23)          OUT4 String "E" |4     25|-> SCLK (pin 13)
               9|-> XLAT (pin 24)           OUT5 String "F" |5     24|-> XLAT (pin 9)
               8|                           OUT6 String "G" |6     23|-> BLANK (pin 10)
               7|                           OUT7 String "H" |7     22|-> GND
               6|                           OUT8 String "I" |8     21|-> VCC (+5V)
               5|                           OUT9 String "J" |9     20|-> 2K Resistor -> GND  
               4|                          OUT10 String "K" |10    19|-> +5V (DCPRG)
               3|-> GSCLK (pin 18)         OUT11 String "L" |11    18|-> GSCLK (pin 3)
               2|                          OUT12 String "M" |12    17|-> SOUT (only used when you want to use more than one tlc5940)
               1|                          OUT13 String "N" |13    16|-> XERR (can be used as error report, but not necessary)
               0|                          OUT14 String "O" |14    15| OUT15 String "P"       */
  }

void loop(){


Serial.print (count);
Serial.print ("\n");	

	oldMicros=micros()+LayerDuration;          

// random colours all over	
	if(count==1){
		for(int j=0;j<50; j++) {
			reset();
			randomall(brightr, brightg, brightb); // sets 10 of each colour randomly
			for(int j=0;j<15; j++) {					
				for(int i=1;i<5;i++) {
					while(micros() < oldMicros) {
					}
					oldMicros=micros()+LayerDuration;           								
					CubeUpdate(i);                                                 // sets the values for the tlc5940 Outputs and puts all MOSFET Gates HIGH (not active) except for one MOSFET Low (active) -->this layer is ON, also look under tab "function"  
				}		
			}			
		}
	}
	
// light the whole cube in green 
	if(count==2){
		reset();
    	all(0, brightg, 0); // green
		for(int j=0;j<loopcnt; j++) {		
			for(int i=1;i<5;i++) {
				while(micros() < oldMicros) {
				}
				oldMicros=micros()+LayerDuration;           								
				CubeUpdate(i);                                                 // sets the values for the tlc5940 Outputs and puts all MOSFET Gates HIGH (not active) except for one MOSFET Low (active) -->this layer is ON, also look under tab "function"  
			}
		}
	}	

// light the whole cube in blue	
	if(count==3){
		reset();
		all(0,0, brightb);
		for(int j=0;j<loopcnt; j++) {				
			for(int i=1;i<5;i++) {
				while(micros() < oldMicros) {
				}
				oldMicros=micros()+LayerDuration;           								
				CubeUpdate(i);                                                 // sets the values for the tlc5940 Outputs and puts all MOSFET Gates HIGH (not active) except for one MOSFET Low (active) -->this layer is ON, also look under tab "function"  
			}
		}			
	}	
	
// light the whole cube in red	
	if(count==4){
		reset();
		all(brightr,0,0);
		for(int j=0;j<loopcnt; j++) {
			for(int i=1;i<5;i++) {
				while(micros() < oldMicros) {
				}
				oldMicros=micros()+LayerDuration;           								
				CubeUpdate(i);                                                 // sets the values for the tlc5940 Outputs and puts all MOSFET Gates HIGH (not active) except for one MOSFET Low (active) -->this layer is ON, also look under tab "function"  
			}		
		}
	}	


// Marches blue thru each of 64 LED's
	if(count==5){
		reset();
		for(int j=0;j<64; j++) {
			BLUELEDs[j]=brightb;
			for(int i=1;i<5;i++) {
				while(micros() < oldMicros) {
				}
				oldMicros=micros()+LayerDuration;           								
				CubeUpdate(i);                                                 // sets the values for the tlc5940 Outputs and puts all MOSFET Gates HIGH (not active) except for one MOSFET Low (active) -->this layer is ON, also look under tab "function"  
			}		
			BLUELEDs[j]=0;							
		}
		for(int j=63;j>-1;j--) {
			BLUELEDs[j]=brightb;		
			for(int i=1;i<5;i++) {
				while(micros() < oldMicros) {
				}
				oldMicros=micros()+LayerDuration;           								
				CubeUpdate(i);                                                 // sets the values for the tlc5940 Outputs and puts all MOSFET Gates HIGH (not active) except for one MOSFET Low (active) -->this layer is ON, also look under tab "function"  
			}		
			BLUELEDs[j]=0;							
		}			
	}	
	
// Marches green thru each of 64 LED's
	if(count==6){
		reset();
		for(int j=0;j<64; j++) {
			GREENLEDs[j]=brightg;		
			for(int i=1;i<5;i++) {
				while(micros() < oldMicros) {
				}
				oldMicros=micros()+LayerDuration;           								
				CubeUpdate(i);                                                 // sets the values for the tlc5940 Outputs and puts all MOSFET Gates HIGH (not active) except for one MOSFET Low (active) -->this layer is ON, also look under tab "function"  
//				delay(10);						
			}		
			GREENLEDs[j]=0;							
		}
		for(int j=63;j>-1;j--) {
			GREENLEDs[j]=brightg;		
			for(int i=1;i<5;i++) {
				while(micros() < oldMicros) {
				}
				oldMicros=micros()+LayerDuration;           								
				CubeUpdate(i);                                                 // sets the values for the tlc5940 Outputs and puts all MOSFET Gates HIGH (not active) except for one MOSFET Low (active) -->this layer is ON, also look under tab "function"  
//				delay(10);						
			}		
			GREENLEDs[j]=0;							
		}			
	}	

// Marches red thru each of 64 LED's	
	if(count==7){
		reset();
		for(int k=0;k<1;k++) {
			for(int j=0;j<64; j++) {
				REDLEDs[j]=brightr;			
				for(int i=1;i<5;i++) {
					while(micros() < oldMicros) {
					}
					oldMicros=micros()+LayerDuration;           								
					CubeUpdate(i);                                                 // sets the values for the tlc5940 Outputs and puts all MOSFET Gates HIGH (not active) except for one MOSFET Low (active) -->this layer is ON, also look under tab "function"  
//					delay(10);						
				}		
				REDLEDs[j]=0;								
			}
			for(int j=63;j>-1;j--) {
				REDLEDs[j]=brightr;			
				for(int i=1;i<5;i++) {
					while(micros() < oldMicros) {
					}
					oldMicros=micros()+LayerDuration;           								
					CubeUpdate(i);                                                 // sets the values for the tlc5940 Outputs and puts all MOSFET Gates HIGH (not active) except for one MOSFET Low (active) -->this layer is ON, also look under tab "function"  
//					delay(10);						
				}		
				REDLEDs[j]=0;								
			}			
		}
	}	
	
	
// WALL - moves around the outside	for each colour
	if(count==8){
		for(int k=0;k<2; k++) {
			for(int j=0;j<12; j++) {
				reset();		
				wall(brightr, 0,0, j);		// not bright - i want to see it XXXXX
				while(micros() < oldMicros) {
				}
				oldMicros=micros()+LayerDuration;           								
				CubeUpdate(0);                                                 // sets the values for the tlc5940 Outputs and puts all MOSFET Gates HIGH (not active) except for one MOSFET Low (active) -->this layer is ON, also look under tab "function"  
				delay(80);
			}
		}
		for(int k=0;k<2; k++) {		
			for(int j=12;j>0; j--) { // backwards
				reset();		
				wall(brightr, 0,0, j-1);		
				while(micros() < oldMicros) {
				}
				oldMicros=micros()+LayerDuration;           								
				CubeUpdate(0);                                                 // sets the values for the tlc5940 Outputs and puts all MOSFET Gates HIGH (not active) except for one MOSFET Low (active) -->this layer is ON, also look under tab "function"  
				delay(80);
			}
		}
		for(int k=0;k<2; k++) {		
			for(int j=0;j<12; j++) {
				reset();				
				wall(0,brightg, 0,j);		// not bright - i want to see it XXXXX
				while(micros() < oldMicros) {
				}
				oldMicros=micros()+LayerDuration;           								
				CubeUpdate(0);                                                 // sets the values for the tlc5940 Outputs and puts all MOSFET Gates HIGH (not active) except for one MOSFET Low (active) -->this layer is ON, also look under tab "function"  
				delay(80);
			}
		}
		for(int k=0;k<2; k++) {		
			for(int j=12;j>0; j--) { // backwards
				reset();		
				wall(0,brightg,0, j-1);		
				while(micros() < oldMicros) {
				}
				oldMicros=micros()+LayerDuration;           								
				CubeUpdate(0);                                                 // sets the values for the tlc5940 Outputs and puts all MOSFET Gates HIGH (not active) except for one MOSFET Low (active) -->this layer is ON, also look under tab "function"  
				delay(80);
			}
		}
		for(int k=0;k<2; k++) {
			for(int j=0;j<12; j++) {
				reset();				
				wall(0,0,brightb, j);		// not bright - i want to see it XXXXX
				while(micros() < oldMicros) {
				}
				oldMicros=micros()+LayerDuration;           								
				CubeUpdate(0);                                                 // sets the values for the tlc5940 Outputs and puts all MOSFET Gates HIGH (not active) except for one MOSFET Low (active) -->this layer is ON, also look under tab "function"  
				delay(80);
			}
		}
		for(int k=0;k<2; k++) {		
			for(int j=12;j>0; j--) { // backwards
				reset();		
				wall(0,0, brightb, j-1);		
				while(micros() < oldMicros) {
				}
				oldMicros=micros()+LayerDuration;           								
				CubeUpdate(0);                                                 // sets the values for the tlc5940 Outputs and puts all MOSFET Gates HIGH (not active) except for one MOSFET Low (active) -->this layer is ON, also look under tab "function"  
				delay(80);
			}
		}
	}		

// does the ns slice for each colour
	if(count==9){
		for(int j=0;j<4; j++) {
			reset();		
			nsslice(brightr, 0,0,j);		// not bright - i want to see it XXXXX				
			while(micros() < oldMicros) {
			}
			oldMicros=micros()+LayerDuration;           								
			CubeUpdate(0);                                                 // sets the values for the tlc5940 Outputs and puts all MOSFET Gates HIGH (not active) except for one MOSFET Low (active) -->this layer is ON, also look under tab "function"  
			delay(200);
		}
		for(int j=4;j>0; j--) {
			reset();		
			nsslice(brightr, 0,0,j-1);		
			while(micros() < oldMicros) {
			}
			oldMicros=micros()+LayerDuration;           								
			CubeUpdate(0);                                                 // sets the values for the tlc5940 Outputs and puts all MOSFET Gates HIGH (not active) except for one MOSFET Low (active) -->this layer is ON, also look under tab "function"  
			delay(200);
		}
		
		for(int j=0;j<4; j++) {
			reset();				
			nsslice(0,brightg, 0,j);		// not bright - i want to see it XXXXX				
			while(micros() < oldMicros) {
			}
			oldMicros=micros()+LayerDuration;           								
			CubeUpdate(0);                                                 // sets the values for the tlc5940 Outputs and puts all MOSFET Gates HIGH (not active) except for one MOSFET Low (active) -->this layer is ON, also look under tab "function"  
			delay(200);
		}
		for(int j=4;j>0; j--) {
			reset();		
			nsslice(0, brightg, 0,j-1);		
			while(micros() < oldMicros) {
			}
			oldMicros=micros()+LayerDuration;           								
			CubeUpdate(0);                                                 // sets the values for the tlc5940 Outputs and puts all MOSFET Gates HIGH (not active) except for one MOSFET Low (active) -->this layer is ON, also look under tab "function"  
			delay(200);
		}
		
		for(int j=0;j<4; j++) {
			reset();				
			nsslice(0,0,brightb, j);		// not bright - i want to see it XXXXX				
			while(micros() < oldMicros) {
			}
			oldMicros=micros()+LayerDuration;           								
			CubeUpdate(0);                                                 // sets the values for the tlc5940 Outputs and puts all MOSFET Gates HIGH (not active) except for one MOSFET Low (active) -->this layer is ON, also look under tab "function"  
			delay(200);
		}
		for(int j=4;j>0; j--) {
			reset();		
			nsslice(0,0, brightb,j-1);		
			while(micros() < oldMicros) {
			}
			oldMicros=micros()+LayerDuration;           								
			CubeUpdate(0);                                                 // sets the values for the tlc5940 Outputs and puts all MOSFET Gates HIGH (not active) except for one MOSFET Low (active) -->this layer is ON, also look under tab "function"  
			delay(200);
		}
		
	}		

// does the ew slice for each colour	
	if(count==10){
		for(int i=0;i<2;i++) {
			for(int j=0;j<4; j++) {
				reset();		
				ewslice(brightr, 0,0, j);		// not bright - i want to see it XXXXX				
				while(micros() < oldMicros) {
				}
				oldMicros=micros()+LayerDuration;           								
				CubeUpdate(0);                                                 // sets the values for the tlc5940 Outputs and puts all MOSFET Gates HIGH (not active) except for one MOSFET Low (active) -->this layer is ON, also look under tab "function"  
				delay(100);
			}
			for(int j=4;j>0; j--) {
				reset();		
				ewslice(brightr, 0,0, j-1);		// not bright - i want to see it XXXXX				
				while(micros() < oldMicros) {
				}
				oldMicros=micros()+LayerDuration;           								
				CubeUpdate(0);                                                 // sets the values for the tlc5940 Outputs and puts all MOSFET Gates HIGH (not active) except for one MOSFET Low (active) -->this layer is ON, also look under tab "function"  
				delay(100);
			}
			
			for(int j=0;j<4; j++) {
				reset();				
				ewslice(0,brightg, 0, j);		// not bright - i want to see it XXXXX				
				while(micros() < oldMicros) {
				}
				oldMicros=micros()+LayerDuration;           								
				CubeUpdate(0);                                                 // sets the values for the tlc5940 Outputs and puts all MOSFET Gates HIGH (not active) except for one MOSFET Low (active) -->this layer is ON, also look under tab "function"  
				delay(100);
			}
			for(int j=4;j>0; j--) {
				reset();		
				ewslice(0,brightg, 0, j-1);		// not bright - i want to see it XXXXX				
				while(micros() < oldMicros) {
				}
				oldMicros=micros()+LayerDuration;           								
				CubeUpdate(0);                                                 // sets the values for the tlc5940 Outputs and puts all MOSFET Gates HIGH (not active) except for one MOSFET Low (active) -->this layer is ON, also look under tab "function"  
				delay(100);
			}
			
			for(int j=0;j<4; j++) {
				reset();				
				ewslice(0,0,brightb, j);		// not bright - i want to see it XXXXX		
				while(micros() < oldMicros) {
				}
				oldMicros=micros()+LayerDuration;           								
				CubeUpdate(0);                                                 // sets the values for the tlc5940 Outputs and puts all MOSFET Gates HIGH (not active) except for one MOSFET Low (active) -->this layer is ON, also look under tab "function"  
				delay(100);
			}
			for(int j=4;j>0; j--) {
				reset();		
				ewslice(0,0,brightb , j-1);		// not bright - i want to see it XXXXX				
				while(micros() < oldMicros) {
				}
				oldMicros=micros()+LayerDuration;           								
				CubeUpdate(0);                                                 // sets the values for the tlc5940 Outputs and puts all MOSFET Gates HIGH (not active) except for one MOSFET Low (active) -->this layer is ON, also look under tab "function"  
				delay(100);
			}
		}	
	}		

// a cross NS and EW and up and down.....
	if(count==11){
		for(int m=0;m<1;m++) {
			getrand();
			for(int k=0;k<2;k++) { 
				for(int l=0;l<4;l++) {    // 4 rows 
					reset();			  // CLEAR ALL
//					nsx(brightr, 0, 0, l);
					nsx(randred, randgreen,randblue, l);
					for (int n=1;n<10;n++) {				// keep displaying the 4 layers 
						for(int i=1;i<5;i++) {				// DISPLAY THEM
							while(micros() < oldMicros) {
							}
							oldMicros=micros()+LayerDuration;           								
							CubeUpdate(i);                                                 // sets the values for the tlc5940 Outputs and puts all MOSFET Gates HIGH (not active) except for one MOSFET Low (active) -->this layer is ON, also look under tab "function"  
						}						
					}
				}
				for(int l=4;l>0;l--) {    // 4 rows 
					reset();			  // CLEAR ALL
					nsx(randred, randgreen,randblue, l-1);					
//					nsx(brightr, 0, 0, l-1);
					for (int n=1;n<10;n++) {				// keep displaying the 4 layers 
						for(int i=1;i<5;i++) {				// DISPLAY THEM
							while(micros() < oldMicros) {
							}
							oldMicros=micros()+LayerDuration;           								
							CubeUpdate(i);                                                 // sets the values for the tlc5940 Outputs and puts all MOSFET Gates HIGH (not active) except for one MOSFET Low (active) -->this layer is ON, also look under tab "function"  
						}						
					}
				}
			}
			getrand();
			for(int k=0;k<2;k++) { 
				for(int l=0;l<4;l++) {    // 4 rows 
					reset();			  // CLEAR ALL
					ewx(randred, randgreen,randblue, l);					
//					ewx(0, brightg, 0, l);
					for (int n=1;n<10;n++) {				// keep displaying the 4 layers 
						for(int i=1;i<5;i++) {				// DISPLAY THEM
							while(micros() < oldMicros) {
							}
							oldMicros=micros()+LayerDuration;           								
							CubeUpdate(i);                                                 // sets the values for the tlc5940 Outputs and puts all MOSFET Gates HIGH (not active) except for one MOSFET Low (active) -->this layer is ON, also look under tab "function"  
						}						
					}
				}
				for(int l=4;l>0;l--) {    // 4 rows 
					reset();			  // CLEAR ALL
//					ewx(0, brightg, 0, l-1);
					ewx(randred, randgreen,randblue, l-1);					
					for (int n=1;n<10;n++) {				// keep displaying the 4 layers 
						for(int i=1;i<5;i++) {				// DISPLAY THEM
							while(micros() < oldMicros) {
							}
							oldMicros=micros()+LayerDuration;           								
							CubeUpdate(i);                                                 // sets the values for the tlc5940 Outputs and puts all MOSFET Gates HIGH (not active) except for one MOSFET Low (active) -->this layer is ON, also look under tab "function"  
						}						
					}
				}
			}
			getrand();
			for(int k=0;k<2;k++) { 			
				for(int j=0;j<4; j++) {
					reset();				
//					udx(0,0,brightb, j);		
					udx(randred, randgreen,randblue, j);					
					while(micros() < oldMicros) {
					}
					oldMicros=micros()+LayerDuration;           								
					CubeUpdate(j+1);                                                 // sets the values for the tlc5940 Outputs and puts all MOSFET Gates HIGH (not active) except for one MOSFET Low (active) -->this layer is ON, also look under tab "function"  
					delay(100);
				}
				for(int j=4;j>0; j--) {
					reset();		
					udx(randred, randgreen,randblue, j-1);										
//					udx(0,0,brightr, j-1);		
					while(micros() < oldMicros) {
					}
					oldMicros=micros()+LayerDuration;           								
					CubeUpdate(j);                                                 // sets the values for the tlc5940 Outputs and puts all MOSFET Gates HIGH (not active) except for one MOSFET Low (active) -->this layer is ON, also look under tab "function"  
					delay(100);
				} 
			}
		}	
	}		
	
	
	
// MOVES UP AND DOWN LAYERS for each colour
	if(count==12){
		
		for(int k=0;k<3;k++){
			reset();
			if(k==0) {all(brightr,0,0);}
			if(k==1) {all(0,0,brightb);}
			if(k==2) {all(0,brightg,0);}
			for(int j=0;j<2; j++) {
				for(int i=1;i<5;i++) {
					while(micros() < oldMicros) {
					}
					oldMicros=micros()+LayerDuration;           								
					CubeUpdate(i);                                                 // sets the values for the tlc5940 Outputs and puts all MOSFET Gates HIGH (not active) except for one MOSFET Low (active) -->this layer is ON, also look under tab "function"  
					delay(50);								
				}		
				for(int i=4;i>0;i--) {
					while(micros() < oldMicros) {
					}
					oldMicros=micros()+LayerDuration;           								
					CubeUpdate(i);                                                 // sets the values for the tlc5940 Outputs and puts all MOSFET Gates HIGH (not active) except for one MOSFET Low (active) -->this layer is ON, also look under tab "function"  
					delay(100);								
				}		
			}					
		}
	}		

// mix colours march all the way up and down
	if(count==13){
		reset();
		for(int j=0;j<64; j++) {
			BLUELEDs[j]=brightb;
			REDLEDs[j]=brightr;					
			for(int i=1;i<5;i++) {
				while(micros() < oldMicros) {
				}
				oldMicros=micros()+LayerDuration;           								
				CubeUpdate(i);                                                 // sets the values for the tlc5940 Outputs and puts all MOSFET Gates HIGH (not active) except for one MOSFET Low (active) -->this layer is ON, also look under tab "function"  
			}		
			BLUELEDs[j]=0;				
			REDLEDs[j]=0;										
		}
		for(int j=63;j>-1;j--) {
			REDLEDs[j]=brightr;
			GREENLEDs[j]=brightg;												
			for(int i=1;i<5;i++) {
				while(micros() < oldMicros) {
				}
				oldMicros=micros()+LayerDuration;           								
				CubeUpdate(i);                                                 // sets the values for the tlc5940 Outputs and puts all MOSFET Gates HIGH (not active) except for one MOSFET Low (active) -->this layer is ON, also look under tab "function"  
//				delay(10);						
			}		
			REDLEDs[j]=0;				
			GREENLEDs[j]=0;				
		}			
	}	

// RAIN.....
	if(count==14){
		reset();
		for(int k=0;k<50;k++) {
			drops = random(0,4); 				// random number of drops 
			for (int i=0;i<=drops;i++){ 			// set random leds 
				int j=random(48,63);
				REDLEDs[j]=random(0,1048);
				GREENLEDs[j]=random(0,750);
				BLUELEDs[j]=random(0,1250);
			}				
			for (int m=0;m<10;m++) {
				for(int i=4;i>-1;i--) {  // show them
					while(micros() < oldMicros) {
					}
					oldMicros=micros()+LayerDuration;           								
					CubeUpdate(i);
				}		
			}
			// now scoffel them down before starting again and generating another random number of drops
			for(int i=0;i<47;i++) {   
				REDLEDs[i]=REDLEDs[i+16];
				GREENLEDs[i]=GREENLEDs[i+16];				
				BLUELEDs[i]=BLUELEDs[i+16];				
			}		
			// now set the top layer to blank in preparation for new random layer
			for(int i=48;i<63;i++) {   
				BLUELEDs[i]=0;
				REDLEDs[i]=0;
				GREENLEDs[i]=0;				
			}		
		}
	}	

	
// NOAH....
	if(count==15){
		for(int j=0;j<2; j++) {      // LETS DO IT THIS MANY TIMES
			for(int l=1;l<5;l++) {    // 4 SIDES OF THE CUBE - ROTATE EACH SIDE
				reset();			  // CLEAR ALL
									  // SET THE PILLARS 
				REDLEDs[19]=brightr;
				REDLEDs[32]=brightr;			
				REDLEDs[0]=brightr;
				REDLEDs[3]=brightr;
				REDLEDs[16]=brightr;
				REDLEDs[35]=brightr;
				REDLEDs[48]=brightr;
				REDLEDs[51]=brightr;
				REDLEDs[12]=brightr;
				REDLEDs[28]=brightr;
				REDLEDs[44]=brightr;
				REDLEDs[60]=brightr;
				REDLEDs[15]=brightr;
				REDLEDs[31]=brightr;
				REDLEDs[47]=brightr;
				REDLEDs[63]=brightr;
										// NOW DO THE LETTERS - DEPENDING ON THE COUNT 1->4 FOR EACH SIDE
				if(l==1) { 
					// N
					REDLEDs[18]=brightr;
					REDLEDs[33]=brightr;			
					// O
					REDLEDs[4]=brightr;
					REDLEDs[8]=brightr;			
					REDLEDs[52]=brightr;
					REDLEDs[56]=brightr;
					// A
					REDLEDs[45]=brightr;
					REDLEDs[46]=brightr;
					REDLEDs[61]=brightr;
					REDLEDs[62]=brightr;			
					//H
					REDLEDs[39]=brightr;
					REDLEDs[43]=brightr;
				}
				if(l==2) { 
					// N
					REDLEDs[23]=brightr;
					REDLEDs[43]=brightr;			
					// O
					REDLEDs[1]=brightr;
					REDLEDs[2]=brightr;			
					REDLEDs[49]=brightr;
					REDLEDs[50]=brightr;
					// A
					REDLEDs[36]=brightr;
					REDLEDs[40]=brightr;
					REDLEDs[52]=brightr;
					REDLEDs[56]=brightr;			
					//H
					REDLEDs[45]=brightr;
					REDLEDs[46]=brightr;
				}
				if(l==3) { 
					// N
					REDLEDs[30]=brightr;
					REDLEDs[45]=brightr;			
					// O
					REDLEDs[7]=brightr;
					REDLEDs[11]=brightr;			
					REDLEDs[55]=brightr;
					REDLEDs[59]=brightr;
					// A
					REDLEDs[33]=brightr;
					REDLEDs[34]=brightr;
					REDLEDs[49]=brightr;
					REDLEDs[50]=brightr;			
					//H
					REDLEDs[36]=brightr;
					REDLEDs[40]=brightr;
				}
				if(l==4) { 
					// N
					REDLEDs[24]=brightr;
					REDLEDs[36]=brightr;			
					// O
					REDLEDs[13]=brightr;
					REDLEDs[14]=brightr;			
					REDLEDs[61]=brightr;
					REDLEDs[62]=brightr;
					// A
					REDLEDs[39]=brightr;
					REDLEDs[43]=brightr;
					REDLEDs[55]=brightr;
					REDLEDs[59]=brightr;			
					//H
					REDLEDs[33]=brightr;
					REDLEDs[34]=brightr;
				}
				for (int n=1;n<loopcnt;n++) {				// keep displaying the 4 layers 
					for(int i=1;i<5;i++) {				// DISPLAY THEM
						while(micros() < oldMicros) {
						}
						oldMicros=micros()+LayerDuration;           								
						CubeUpdate(i);                                                 // sets the values for the tlc5940 Outputs and puts all MOSFET Gates HIGH (not active) except for one MOSFET Low (active) -->this layer is ON, also look under tab "function"  
					}						
				}
			}
		}
	}	
	
// centre to outside 	
	if(count==16){
		for(int j=0;j<2; j++) {   // do this 
			for(int l=1;l<5;l++) {    // internal rotation 
				reset();			  // CLEAR ALL
				if(l==1) { 
					REDLEDs[21]=brightr;
					REDLEDs[42]=brightr;			
					GREENLEDs[25]=brightg;
					GREENLEDs[38]=brightg;
					BLUELEDs[22]=brightb;
					BLUELEDs[41]=brightb;

					REDLEDs[26]=brightr;
					BLUELEDs[26]=brightg;										
					REDLEDs[37]=brightr;
					BLUELEDs[37]=brightg;										
				}				
				if(l==2) { 
					REDLEDs[26]=brightr;
					REDLEDs[37]=brightr;			
					GREENLEDs[21]=brightg;
					GREENLEDs[42]=brightg;
					BLUELEDs[25]=brightb;
					BLUELEDs[38]=brightb;

					REDLEDs[22]=brightr;
					BLUELEDs[22]=brightg;										
					REDLEDs[41]=brightr;
					BLUELEDs[41]=brightg;										
				}				
				if(l==3) { 
					REDLEDs[22]=brightr;
					REDLEDs[41]=brightr;			
					GREENLEDs[26]=brightg;
					GREENLEDs[37]=brightg;
					BLUELEDs[21]=brightb;
					BLUELEDs[42]=brightb;

					REDLEDs[25]=brightr;
					BLUELEDs[25]=brightg;										
					REDLEDs[38]=brightr;
					BLUELEDs[38]=brightg;										
				}				
				if(l==4) { 
					REDLEDs[25]=brightr;
					REDLEDs[38]=brightr;			
					GREENLEDs[22]=brightg;
					GREENLEDs[41]=brightg;
					BLUELEDs[26]=brightb;
					BLUELEDs[37]=brightb;

					REDLEDs[21]=brightr;
					BLUELEDs[21]=brightg;										
					REDLEDs[42]=brightr;
					BLUELEDs[42]=brightg;										
				}			
				for(int j=0;j<25; j++) {						
					for(int i=1;i<5;i++) { // layers
							while(micros() < oldMicros) {
							}
							oldMicros=micros()+LayerDuration;           								
							CubeUpdate(i);                                                 // sets the values for the tlc5940 Outputs and puts all MOSFET Gates HIGH (not active) except for one MOSFET Low (active) -->this layer is ON, also look under tab "function"  
					}
				}					
			} // end internal rotation
		}
		for(int l=1;l<3;l++) {    // big small 
			for (int m=1;m<3;m++) {
				reset();			  // CLEAR ALL
				if(m==1) { // inner circle
					REDLEDs[21]=brightr;
					REDLEDs[42]=brightr;			
					GREENLEDs[25]=brightg;
					GREENLEDs[38]=brightg;
					BLUELEDs[22]=brightb;
					BLUELEDs[41]=brightb;

					REDLEDs[26]=brightr;
					BLUELEDs[26]=brightg;										
					REDLEDs[37]=brightr;
					BLUELEDs[37]=brightg;										
				}
				if(m==2) { // outter circle
					REDLEDs[0]=brightr;
					REDLEDs[1]=brightr;			
					REDLEDs[2]=brightr;
					REDLEDs[16]=brightr;
					REDLEDs[17]=brightr;
					REDLEDs[18]=brightr;			
					REDLEDs[32]=brightr;
					REDLEDs[33]=brightr;
					REDLEDs[34]=brightr;
					REDLEDs[48]=brightr;			
					REDLEDs[49]=brightr;
					REDLEDs[50]=brightr;
					
					GREENLEDs[3]=brightg;
					GREENLEDs[7]=brightg;
					GREENLEDs[11]=brightg;
					GREENLEDs[19]=brightg;
					GREENLEDs[23]=brightg;
					GREENLEDs[27]=brightg;
					GREENLEDs[35]=brightg;
					GREENLEDs[39]=brightg;
					GREENLEDs[43]=brightg;
					GREENLEDs[51]=brightg;
					GREENLEDs[55]=brightg;
					GREENLEDs[59]=brightg;
											
					BLUELEDs[13]=brightb;
					BLUELEDs[14]=brightb;
					BLUELEDs[15]=brightb;
					BLUELEDs[29]=brightb;
					BLUELEDs[30]=brightb;
					BLUELEDs[31]=brightb;
					BLUELEDs[45]=brightb;
					BLUELEDs[46]=brightb;
					BLUELEDs[47]=brightb;
					BLUELEDs[61]=brightb;
					BLUELEDs[62]=brightb;
					BLUELEDs[63]=brightb;

					REDLEDs[4]=brightr;
					BLUELEDs[4]=brightg;										
					REDLEDs[8]=brightr;
					BLUELEDs[8]=brightg;										
					REDLEDs[12]=brightr;
					BLUELEDs[12]=brightg;										
					REDLEDs[20]=brightr;
					BLUELEDs[20]=brightg;										
					REDLEDs[24]=brightr;
					BLUELEDs[24]=brightg;										
					REDLEDs[28]=brightr;
					BLUELEDs[28]=brightg;										
					REDLEDs[36]=brightr;
					BLUELEDs[36]=brightg;										
					REDLEDs[40]=brightr;
					BLUELEDs[40]=brightg;										
					REDLEDs[44]=brightr;
					BLUELEDs[44]=brightg;										
					REDLEDs[52]=brightr;
					BLUELEDs[52]=brightg;										
					REDLEDs[56]=brightr;
					BLUELEDs[56]=brightg;										
					REDLEDs[60]=brightr;
					BLUELEDs[60]=brightg;										
				}
				for(int j=0;j<25; j++) {						
					for(int i=1;i<5;i++) {
							while(micros() < oldMicros) {
							}
							oldMicros=micros()+LayerDuration;           								
							CubeUpdate(i);                                                 // sets the values for the tlc5940 Outputs and puts all MOSFET Gates HIGH (not active) except for one MOSFET Low (active) -->this layer is ON, also look under tab "function"  
					}
				}					
			} 
		} // big small 
	} // end 15

// internal loop
	if(count==17){
		for(int j=0;j<10; j++) {   // do this 10 times
			for(int l=1;l<2;l++) {
				for(int m=1;m<9;m++) {    // internal rotation 				
					reset();			  // CLEAR ALL
					if(l==1) { 
						if(m==1) {REDLEDs[21]=brightr;}
						if(m==2) {REDLEDs[42]=brightr;}	
						if(m==3) {GREENLEDs[25]=brightg;}
						if(m==4) {GREENLEDs[38]=brightg;}
						if(m==5) {BLUELEDs[22]=brightb;}
						if(m==6) {BLUELEDs[41]=brightb;}

						if(m==7) {REDLEDs[26]=brightr;
								BLUELEDs[26]=brightg;
								}
						if(m==8) {REDLEDs[37]=brightr;
								BLUELEDs[37]=brightg;										
								}
					}				
					if(l==2) { 
						if(m==1) {	REDLEDs[26]=brightr;}
						if(m==2) {	REDLEDs[37]=brightr;}		
						if(m==3) {	GREENLEDs[21]=brightg;}
						if(m==4) {	GREENLEDs[42]=brightg;}
						if(m==5) {	BLUELEDs[25]=brightb;}
						if(m==6) {	BLUELEDs[38]=brightb;}

						if(m==7) {	REDLEDs[22]=brightr;
								BLUELEDs[22]=brightg;										
							}
						if(m==8) {	REDLEDs[41]=brightr;
								BLUELEDs[41]=brightg;										
							}
					}				
					if(l==3) { 
						if(m==1) {	REDLEDs[22]=brightr;}
						if(m==2) {	REDLEDs[41]=brightr;}		
						if(m==3) {	GREENLEDs[26]=brightg;}
						if(m==4) {	GREENLEDs[37]=brightg;}
						if(m==5) {	BLUELEDs[21]=brightb;}
						if(m==6) {	BLUELEDs[42]=brightb;}

						if(m==7) {	REDLEDs[25]=brightr;
								BLUELEDs[25]=brightg;										
							}
						if(m==8) {	REDLEDs[38]=brightr;
								BLUELEDs[38]=brightg;										
							}
					}				
					if(l==4) { 
						if(m==1) {	REDLEDs[25]=brightr;}
						if(m==2) {	REDLEDs[38]=brightr;}		
						if(m==3) {	GREENLEDs[22]=brightg;}
						if(m==4) {	GREENLEDs[41]=brightg;}
						if(m==5) {	BLUELEDs[26]=brightb;}
						if(m==6) {	BLUELEDs[37]=brightb;}

						if(m==7) {	REDLEDs[21]=brightr;
								BLUELEDs[21]=brightg;										
							}
						if(m==8) {	REDLEDs[42]=brightr;
								BLUELEDs[42]=brightg;										
							}
					}								
					for(int j=0;j<5; j++) {							
						for(int i=1;i<5;i++) {
								while(micros() < oldMicros) {
								}
								oldMicros=micros()+LayerDuration;           								
								CubeUpdate(i);                                                 // sets the values for the tlc5940 Outputs and puts all MOSFET Gates HIGH (not active) except for one MOSFET Low (active) -->this layer is ON, also look under tab "function"  
						}
					}
				} // end lm inside
			} // end lm outside
		} // j times
	} // end 16
	
// internal loop
	if(count==18){
		for(int j=0;j<2; j++) {   // do this 2 times
			for(int l=1;l<2;l++) {
				for(int m=1;m<9;m++) {    // internal rotation 				
					reset();			  // CLEAR ALL
					if(l==1) { 
						if(m==1) {REDLEDs[21]=brightr;}
						if(m==2) {REDLEDs[42]=brightr;}	
						if(m==3) {GREENLEDs[25]=brightg;}
						if(m==4) {GREENLEDs[38]=brightg;}
						if(m==5) {BLUELEDs[22]=brightb;}
						if(m==6) {BLUELEDs[41]=brightb;}

						if(m==7) {REDLEDs[26]=brightr;
								BLUELEDs[26]=brightg;
								}
						if(m==8) {REDLEDs[37]=brightr;
								BLUELEDs[37]=brightg;										
								}
					}				
					if(l==2) { 
						if(m==1) {	REDLEDs[26]=brightr;}
						if(m==2) {	REDLEDs[37]=brightr;}		
						if(m==3) {	GREENLEDs[21]=brightg;}
						if(m==4) {	GREENLEDs[42]=brightg;}
						if(m==5) {	BLUELEDs[25]=brightb;}
						if(m==6) {	BLUELEDs[38]=brightb;}

						if(m==7) {	REDLEDs[22]=brightr;
								BLUELEDs[22]=brightg;										
							}
						if(m==8) {	REDLEDs[41]=brightr;
								BLUELEDs[41]=brightg;										
							}
					}				
					if(l==3) { 
						if(m==1) {	REDLEDs[22]=brightr;}
						if(m==2) {	REDLEDs[41]=brightr;}		
						if(m==3) {	GREENLEDs[26]=brightg;}
						if(m==4) {	GREENLEDs[37]=brightg;}
						if(m==5) {	BLUELEDs[21]=brightb;}
						if(m==6) {	BLUELEDs[42]=brightb;}

						if(m==7) {	REDLEDs[25]=brightr;
								BLUELEDs[25]=brightg;										
							}
						if(m==8) {	REDLEDs[38]=brightr;
								BLUELEDs[38]=brightg;										
							}
					}				
					if(l==4) { 
						if(m==1) {	REDLEDs[25]=brightr;}
						if(m==2) {	REDLEDs[38]=brightr;}		
						if(m==3) {	GREENLEDs[22]=brightg;}
						if(m==4) {	GREENLEDs[41]=brightg;}
						if(m==5) {	BLUELEDs[26]=brightb;}
						if(m==6) {	BLUELEDs[37]=brightb;}

						if(m==7) {	REDLEDs[21]=brightr;
								BLUELEDs[21]=brightg;										
							}
						if(m==8) {	REDLEDs[42]=brightr;
								BLUELEDs[42]=brightg;										
							}
					}								
					for(int j=0;j<5; j++) {							
						for(int i=1;i<5;i++) {
								while(micros() < oldMicros) {
								}
								oldMicros=micros()+LayerDuration;           								
								CubeUpdate(i);                                                 // sets the values for the tlc5940 Outputs and puts all MOSFET Gates HIGH (not active) except for one MOSFET Low (active) -->this layer is ON, also look under tab "function"  
						}
					}
				} // end lm inside
				for(int q=0; q<2;q++) {  // the ourside pieces
					reset();			  // CLEAR ALL
					// do outside corners
					REDLEDs[0]=brightr;
					REDLEDs[3]=brightr;	
					GREENLEDs[12]=brightg;
					GREENLEDs[15]=brightg;
					BLUELEDs[48]=brightb;
					BLUELEDs[51]=brightb;

					REDLEDs[60]=brightr;
					BLUELEDs[60]=brightg;
					
					REDLEDs[63]=brightr;
					BLUELEDs[63]=brightg;										
					for(int j=0;j<25; j++) {							
						for(int i=1;i<5;i++) {
								while(micros() < oldMicros) {
								}
								oldMicros=micros()+LayerDuration;           								
								CubeUpdate(i);                                                 // sets the values for the tlc5940 Outputs and puts all MOSFET Gates HIGH (not active) except for one MOSFET Low (active) -->this layer is ON, also look under tab "function"  
						}
					}
					reset();			  // CLEAR ALL
					// do inner squares
					REDLEDs[5]=brightr;
					REDLEDs[6]=brightr;	
					GREENLEDs[9]=brightg;
					GREENLEDs[10]=brightg;
					BLUELEDs[20]=brightb;
					BLUELEDs[24]=brightb;
					
					REDLEDs[29]=brightr;
					BLUELEDs[29]=brightg;
					
					REDLEDs[30]=brightr;
					BLUELEDs[30]=brightg;										
					
					REDLEDs[27]=brightr;
					REDLEDs[23]=brightr;	
					GREENLEDs[18]=brightg;
					GREENLEDs[17]=brightg;
					BLUELEDs[33]=brightb;
					BLUELEDs[34]=brightb;

					REDLEDs[39]=brightr;
					BLUELEDs[39]=brightg;
					
					REDLEDs[43]=brightr;
					BLUELEDs[43]=brightg;										
					
					REDLEDs[45]=brightr;
					REDLEDs[46]=brightr;	
					GREENLEDs[40]=brightg;
					GREENLEDs[36]=brightg;
					BLUELEDs[53]=brightb;
					BLUELEDs[54]=brightb;

					REDLEDs[57]=brightr;
					BLUELEDs[57]=brightg;
					
					REDLEDs[58]=brightr;
					BLUELEDs[58]=brightg;										
					for(int j=0;j<25; j++) {							
						for(int i=1;i<5;i++) {
								while(micros() < oldMicros) {
								}
								oldMicros=micros()+LayerDuration;           								
								CubeUpdate(i);                                                 // sets the values for the tlc5940 Outputs and puts all MOSFET Gates HIGH (not active) except for one MOSFET Low (active) -->this layer is ON, also look under tab "function"  
						}
					} 
						
					reset();			  // CLEAR ALL
					// do outer edges no corners
					REDLEDs[1]=brightr;
					REDLEDs[2]=brightr;	
					GREENLEDs[4]=brightg;
					GREENLEDs[8]=brightg;
					BLUELEDs[13]=brightb;
					BLUELEDs[14]=brightb;
					
					REDLEDs[11]=brightr;
					BLUELEDs[11]=brightg;
					
					REDLEDs[7]=brightr;
					BLUELEDs[7]=brightg;										
					
					REDLEDs[16]=brightr;
					REDLEDs[19]=brightr;	
					GREENLEDs[28]=brightg;
					GREENLEDs[31]=brightg;
					BLUELEDs[32]=brightb;
					BLUELEDs[35]=brightb;

					REDLEDs[47]=brightr;
					BLUELEDs[47]=brightg;
					
					REDLEDs[44]=brightr;
					BLUELEDs[44]=brightg;										
					
					REDLEDs[52]=brightr;
					REDLEDs[56]=brightr;	
					GREENLEDs[61]=brightg;
					GREENLEDs[62]=brightg;
					BLUELEDs[59]=brightb;
					BLUELEDs[55]=brightb;

					REDLEDs[49]=brightr;
					BLUELEDs[49]=brightg;
					
					REDLEDs[50]=brightr;
					BLUELEDs[50]=brightg;										
					for(int j=0;j<25; j++) {							
						for(int i=1;i<5;i++) {
								while(micros() < oldMicros) {
								}
								oldMicros=micros()+LayerDuration;           								
								CubeUpdate(i);                                                 // sets the values for the tlc5940 Outputs and puts all MOSFET Gates HIGH (not active) except for one MOSFET Low (active) -->this layer is ON, also look under tab "function"  
						}
					}
					// try adding the inside squares
					REDLEDs[21]=brightr;
					REDLEDs[22]=brightr;	
					GREENLEDs[25]=brightg;
					GREENLEDs[26]=brightg;
					BLUELEDs[37]=brightb;
					BLUELEDs[38]=brightb;
					
					REDLEDs[42]=brightr;
					BLUELEDs[42]=brightg;
					
					REDLEDs[41]=brightr;
					BLUELEDs[41]=brightg;										
					for(int j=0;j<25; j++) {							
						for(int i=1;i<5;i++) {
								while(micros() < oldMicros) {
								}
								oldMicros=micros()+LayerDuration;           								
								CubeUpdate(i);                                                 // sets the values for the tlc5940 Outputs and puts all MOSFET Gates HIGH (not active) except for one MOSFET Low (active) -->this layer is ON, also look under tab "function"  
						}
					}
					reset();			  // CLEAR ALL
					// do inner squares and inner squares
					REDLEDs[5]=brightr;
					REDLEDs[6]=brightr;	
					GREENLEDs[9]=brightg;
					GREENLEDs[10]=brightg;
					BLUELEDs[20]=brightb;
					BLUELEDs[24]=brightb;
					
					REDLEDs[29]=brightr;
					BLUELEDs[29]=brightg;
					
					REDLEDs[30]=brightr;
					BLUELEDs[30]=brightg;										
					
					REDLEDs[27]=brightr;
					REDLEDs[23]=brightr;	
					GREENLEDs[18]=brightg;
					GREENLEDs[17]=brightg;
					BLUELEDs[33]=brightb;
					BLUELEDs[34]=brightb;

					REDLEDs[39]=brightr;
					BLUELEDs[39]=brightg;
					
					REDLEDs[43]=brightr;
					BLUELEDs[43]=brightg;										
					
					REDLEDs[45]=brightr;
					REDLEDs[46]=brightr;	
					GREENLEDs[40]=brightg;
					GREENLEDs[36]=brightg;
					BLUELEDs[53]=brightb;
					BLUELEDs[54]=brightb;

					REDLEDs[57]=brightr;
					BLUELEDs[57]=brightg;
					
					REDLEDs[58]=brightr;
					BLUELEDs[58]=brightg;										
					// try adding the inside squares
					REDLEDs[21]=brightr;
					REDLEDs[22]=brightr;	
					GREENLEDs[25]=brightg;
					GREENLEDs[26]=brightg;
					BLUELEDs[37]=brightb;
					BLUELEDs[38]=brightb;
					
					REDLEDs[42]=brightr;
					BLUELEDs[42]=brightg;
					
					REDLEDs[41]=brightr;
					BLUELEDs[41]=brightg;										
					for(int j=0;j<25; j++) {							
						for(int i=1;i<5;i++) {
								while(micros() < oldMicros) {
								}
								oldMicros=micros()+LayerDuration;           								
								CubeUpdate(i);                                                 // sets the values for the tlc5940 Outputs and puts all MOSFET Gates HIGH (not active) except for one MOSFET Low (active) -->this layer is ON, also look under tab "function"  
						}
					}
					
				} // q show in outside
			} // end lm outside
		} // j times
	} // end 17

// circle
	if(count==19){
		for(int j=0;j<10; j++) { // do it this many times
			for(int k=0;k<3;k++) {  // do the rotation 3 positions - the firth position is the same as the first iff all the same colour
				reset();
				rotate(brightr, brightg, 0, k); 
				for(int j=0;j<15; j++) {					
					for(int i=1;i<5;i++) {
						while(micros() < oldMicros) {
						}
						oldMicros=micros()+LayerDuration;           								
						CubeUpdate(i);                                                 // sets the values for the tlc5940 Outputs and puts all MOSFET Gates HIGH (not active) except for one MOSFET Low (active) -->this layer is ON, also look under tab "function"  
					}		
				}			
			}	
		}
	}
	
	count++;                                                           // count counter +1, to change the picture in next if() cycle
    if (count>NUM_PATTERNS){
		count=0;
	}                                    // we have 8 static picture for the moving sine wave, so if count counter would hit the 9.(not existing) pic, it goes back to count=0

}
