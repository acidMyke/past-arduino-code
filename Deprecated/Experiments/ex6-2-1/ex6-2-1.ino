//========== ex6-2-1.ino ============
// pins A0~A5 connected to P9-3~P9-8 (LED Bar)
// pins 4~2 connected to P23A-1~P23A-3 (3 IR sensors)
//========== Global Declaration ============
const int IR[]={4,3,2};	//IR sensors connected to digital pins 4~2 (left, middle, right)
const int LED[]={A5,A4,A3,A2,A1,A0};  // LEDs connected to analog pins A5~A0
//========== Initialization ============
void setup()
{  for(int i=0;i<3;i++) 		// configure digital pins 4~2 as inputs  
   pinMode(IR[i], INPUT); 
   for(int i=0;i<6;i++) 		// configure analog pins A5~A0 as outputs 
   pinMode(LED[i], OUTPUT); 
} 	
//========== Main Code ============
void loop()
{  int status,ir;			// declare integer variables status and ir
   status=0;				// reset the status 
   for(int i=0;i<3;i++)			// scan 3 IR sensors’ status
   {  ir=digitalRead(IR[i]);		// read each of IR sensors
      if (!ir) status|=(1<<(2-i));	// record each read status
   } 
   switch (status)			// do the cases according to status value
   {  case 0b011:	 		// status=011
		writeLED(0b001111); 	// output to LED Bar
		break; 			// exit
      case 0b001:	 		// status=001
		writeLED(0b000011); 	// output to LED Bar
		break; 			// exit
      case 0b101: 			// status=101
		writeLED(0b110011); 	// output to LED Bar
		break; 			// exit
      case 0b100: 			// status=100
		writeLED(0b110000); 	// output to LED Bar
		break; 			// exit
      case 0b110: 			// status=110
		writeLED(0b111100); 	// output to LED Bar
		break; 			// exit
      default: 				// other states
		writeLED(0b111111); 	// turn off LEDs 
		break; 			// exit
    }
}
//========== Function ============
void writeLED(int x)
{  for(int i=0;i<6;i++)			// output to LEDs 3 ~ 8 
   {  if(x&(1<<i)) digitalWrite(LED[i], 1); 
      else digitalWrite(LED[i], 0);
   }
}

