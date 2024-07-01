//========== ex7-2-1.ino ============
// pin A4 (SDA) connected to P26-1
// pin A5 (SCL) connected to P26-2
//========== Global Declaration ============
#include <Wire.h>  	    // include the Wire library  
#include <SFE_MMA8452Q.h>   // include the SFE_MMA8452Q library 
MMA8452Q myMMA; 	    // create an MMA8452Q object named myMMA
//========== Initialization ============
void setup()
{  myMMA.init();	    // initialize the MMA8452Q chip 
   Serial.begin(9600);	    // open the serial port at 9600 bps
} 
//========== Main Code ============
void loop()
{  if(myMMA.available());   // if MMA8452Q data is ready,
   {  myMMA.read(); 	    // read MMA8452Q acceleration data
      // display X-axis acceleration value
      Serial.print("Accelerometer X:"); 
      Serial.println(myMMA.x, 3);	
      // display Y-axis acceleration value
      Serial.print("Accelerometer Y:");
      Serial.println(myMMA.y, 3);	
      // display Z-axis acceleration value
      Serial.print("Accelerometer Z:"); 
      Serial.println(myMMA.x, 3);
      Serial.println();	
      // display g value 
      Serial.println("Rescale:");
      Serial.print(myMMA.cx, 3);
      Serial.print(",  ");
      Serial.print(myMMA.cy, 3);
      Serial.print(",  ");
      Serial.println(myMMA.cz, 3);
      Serial.println();
      // display MMA8452Q Landscape/Portrait orientation
      int dir = myMMA.readPL(); 
      switch (dir)
      {  case PORTRAIT_U:
	      Serial.println("PORTRAIT UP");
	      break;
	 case PORTRAIT_D:
	      Serial.println("PORTRAIT DOWN");
	      break;
	 case LANDSCAPE_L:
	      Serial.println("LANDSCAPE LEFT");
	      break;
	 case LANDSCAPE_R:
	      Serial.println("LANDSCAPE RIGHT");
	      break;
	 case LOCKOUT:
	      Serial.println("FLAT");
	      break;
      }
      delay(1000);
   }
}

