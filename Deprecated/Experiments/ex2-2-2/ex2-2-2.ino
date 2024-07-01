//========== ex2-2-2.ino ============
//========== Declaraction ============
// pins 13~11 connected to 74HC138’s pins A~C
// pin 10 connected to 74HC138 G1 (active-high enable)
// pins 9~2 connected to LED matrix R0~R7
const int Row[]={9,8,7,6,5,4,3,2};  // R0~R7 connected to digital pins 9-2
const int HC138[]={13,12,11};	    // 74HC138 A,B,C connected to digital pins 13-11
const int G1=10;		    // 74HC138 G1 connected to digital pin 10
const byte myData[]=
{	0X08,0X1C,0X36,0X77,0X14,0X14,0X1C,0X00,	// arrow
	0X00,0X7C,0X7E,0X02,0X02,0X7E,0X7C,0X00,	// U
	0X00,0X7E,0X7E,0X40,0X40,0X7E,0X3E,0X00,	// n
	0X00,0X3C,0X7E,0X42,0X7E,0X3C,0X00,0X00,	// o
	0X06,0X6F,0XF9,0X99,0X97,0X63,0X05,0X00,	// &
	0X62,0XF3,0XB3,0X91,0X99,0XCF,0X4E,0X00,	// S
	0X1E,0X30,0X30,0X1E,0X30,0X30,0X1E,0X00,	// m
	0X00,0X00,0X00,0X6E,0X6E,0X00,0X00,0X00,	// i
	0X00,0X00,0X00,0X7E,0X7E,0X00,0X00,0X00,	// l
	0X00,0X3C,0X7E,0X52,0X52,0X72,0X34,0X00};	// e
#define  speed  30  // define speed (times of repetition, switching time about 8ms*speed)
//========== Initialization ============
void setup()
{  pinMode(G1, OUTPUT);		  // configure digital pin 10 as an output 
   for(int i=0;i<3;i++) 	  // configure digital pins 13-11 as outputs 
	pinMode(HC138[i], OUTPUT);
   for(int i=0;i<8;i++) 	  // configure digital pins 9-2 as outputs 
	pinMode(Row[i], OUTPUT);
    digitalWrite(G1, 0);	  // turn off LED matrix display (disable 74HC138)
} 
//========== Main Code ============
void loop()
{  int TMP=0;			   // declare an integer variable named TMP
   for(int i=0;i<80;i++)	   // display 10 characters
   {  for(int j=0;j<speed;j++)	   // scan each character 30 times
      {  for(int k=0;k<8;k++)	   // column scanning 
	 {  digitalWrite(G1,0);	   // turn off LED matrix (preventing motion blur)
	    writeColumn(k);	   // send column scan code to 74HC138 inputs 
	    TMP=i+k;		   // calculate the index of display data array
	    if (TMP>=80) TMP-=80;  // if the index>=80, reset it to 0.
	    writeRow(myData[TMP]); // output display data to rows
	    digitalWrite(G1,1);	   // enable the 74HC138 decoder
	    delay(1);		   // a delay of 1 ms
	  }
	}
    }
}
//========== Functions ============
//=== writeColumn() ============
void writeColumn(int x)
{  switch (x)			 
   {  case 0:		// when x=0  
            digitalWrite(HC138[2],0); // C=0
            digitalWrite(HC138[1],0); // B=0
            digitalWrite(HC138[0],0); // A=0
            break; 	// exit
      case 1:		// when x=1  
	    digitalWrite(HC138[2],0); // C=0
	    digitalWrite(HC138[1],0); // B=0
	    digitalWrite(HC138[0],1); // A=1
	    break; 	// exit
      case 2:		// when x=2 
	    digitalWrite(HC138[2],0); // C=0
	    digitalWrite(HC138[1],1); // B=1
	    digitalWrite(HC138[0],0); // A=0
	    break; 	// exit
      case 3:		// when x=3 
	    digitalWrite(HC138[2],0); // C=0
	    digitalWrite(HC138[1],1); // B=1
	    digitalWrite(HC138[0],1); // A=1
	    break; 	// exit
      case 4:		// when x=4 
	    digitalWrite(HC138[2],1); // C=1
	    digitalWrite(HC138[1],0); // B=0
	    digitalWrite(HC138[0],0); // A=0
	    break; 	// exit
       case 5:		// when x=5 
	    digitalWrite(HC138[2],1); // C=1
	    digitalWrite(HC138[1],0); // B=0
	    digitalWrite(HC138[0],1); // A=1
	    break; 	// exit
       case 6:		// when x=6 
	    digitalWrite(HC138[2],1); // C=1
	    digitalWrite(HC138[1],1); // B=1
	    digitalWrite(HC138[0],0); // A=0
	    break; 	// exit
       case 7:		// when x=7 
	    digitalWrite(HC138[2],1); // C=1
	    digitalWrite(HC138[1],1); // B=1
	    digitalWrite(HC138[0],1); // A=1
	    break; 	// exit 
    } 
} 
//=== writeRow() ============
void writeRow(byte x)
{  for(int i=0;i<8;i++)		// output 8-bit display data to rows
   {  if((x&(1<<i))==0) digitalWrite(Row[7-i],0);
      else digitalWrite(Row[7-i],1); 			
   }
}

