// ******** ESP8266 application – Temperature & Humidity Data Logger ********
// =========== ex10-1-1.ino =============
//============ ESP8266 ==============
#include <SoftwareSerial.h> 	// include the SoftwareSerial library
#define PC_bps 9600
#define ESP_bps 115200 		
// The default baud rate of ESP8266 ESP12 is 9,600 bps or 115,200 bps.
// Set the baud rate of EPS12 to 115,200 bps.
#define ESP_TxD 3    		// connect digital pin 3 to TxD of ESP8266 ESP12
#define ESP_RxD 2    		// connect digital pin 2 to RxD of ESP8266 ESP12

SoftwareSerial ESP(ESP_RxD, ESP_TxD); // create a SoftwareSerial object named ESP
#define ssid "happyUno"  	// SSID of your wifi wireless network
#define pass "ac45cc042" 	// password of your wifi wireless network

#define ThingSpeak "184.106.153.149" 
// ThingSpeak IP Address: 184.106.153.149
String  GET = "GET /update?key=C8A99S2P3W2S9L5I"; 
// Write API Key of your ThingSpeak channel

//============ DHT11 =================
#define DHT_p A0	// connect analog pin A0 to DHT11 data pin 
byte MSG;    		// declare a byte variable MSG
byte T_H[5];  		// declare a byte array T_H[] for storing DHT11 data
String Temp,Humi;	// declare strings Temp and Humi 

//============ I2C LCD1602 =================
#include <Wire.h>           	// include the Wire library
#include <LiquidCrystal_I2C.h> 	// include the LiquidCrystal_I2C library

LiquidCrystal_I2C myI2C(0x27,16,2); // create a LiquidCrystal_I2C object named myI2C

//=========================================================
void setup() 
{   //=== Connect to PC ==================  
    Serial.begin(PC_bps);	// open the serial port at 9600 bps
    
    //=== Connect to ESP8266 ==================
    ESP.begin(ESP_bps);		// initialize the ESP8266
    sendCommand("AT+CWMODE=1");	// set Station (STA) mode
    delay(500);
    sendCommand("AT");	// test AT startup 

    // serial monitor displays: SEND:AT  
    delay(1000);
    if(ESP.find("OK")) 		// if ESP8266 has received “OK”,
    {   Serial.println("RECEIVED: OK"); 
        Serial.println("Data ready to send."); 
        // serial monitor displays:
        // RECEIVED: OK
        // Data ready to send.
        connectWiFi(); 	// connect ESP8266 to WiFi
        // serial monitor displays: 
        // SEND: AT+CWJAP="happyUno"," ac45cc042"
        // RECEIVED: OK 
    }   
    else
    {   Serial.println("No Response...");
        // if ESP8266 has not received “OK”, serial monitor displays “No Response...”
    }

    //=== DHT ==================
    pinMode(DHT_p,OUTPUT);		
    digitalWrite(DHT_p,1);

    //=== LCD ==================
    myI2C.begin();		// initialize the LCD 
    myI2C.backlight();	// turn on the backlight 

    delay(2000);		//a delay of 2 seconds
}

//****************************************************************
void loop() {
    readDHT11();	// read temperature and humidity data 
    switch (MSG) 
    {   case 0:  	// valid
          // ======== processing temperature and humidity data ==========
          Humi = String(T_H[0])+'.'+String(T_H[1]);
          Temp = String(T_H[2])+'.'+String(T_H[3]);
          
          // ============== Update data in cloud ================
          updateCloud(Temp, Humi);
 	  // update the temperature & humidity data of logger channel via ESP8266 
          
          // ============== Serial Monitor ===============
          Serial.print("Humidity: "); 
          Serial.println(Humi);
          Serial.print("Temperature: "); 
          Serial.print(Temp);
          Serial.println(" *C");
          Serial.println();
          Serial.println();
          // ============== I2C LCD1602 ===============
          myI2C.home();            // cursor home 
          myI2C.print("Humi:  ");  // display string
          myI2C.print(Humi);       // display humidity
          myI2C.print("   ");      // display spaces
          myI2C.setCursor(0,1);  // set cursor to the first position of line 1, (0,1) 
          myI2C.print("Temp:  ");  // display string
          myI2C.print(Temp);       // display temperature
          myI2C.print("   ");      // display spaces
          break;
       case 1:  // error 1
          // ============== Serial Monitor ===============
          Serial.println();	// next line
          Serial.println();	// next line
          Serial.println();	// next line
          Serial.print("Error1: No Acknowledgement. "); 
          myI2C.home();      		// cursor home 
          myI2C.print("Humi:  "); 	// display string
          // ============== I2C LCD1602 ===============
          myI2C.home();           	// cursor home 
          myI2C.print("== Error 1 =="); // display string
          break;
       case 2:  // error 2
          // ============== Serial Monitor ===============
          Serial.println();	// next line
          Serial.println();	// next line
          Serial.println();	// next line
          Serial.print("Error2: Acknowledgement Error. "); 
          Serial.println();	// next line
          Serial.println();	// next line
          Serial.println();	// next line
          // ============== I2C LCD1602 ===============
          myI2C.home();           	// cursor home 
          myI2C.print("== Error 2 =="); // display string
          break;
       case 3:  // error 3
          // ============== Serial Monitor ===============
          Serial.println();	// next line
          Serial.println();	// next line
          Serial.println();	// next line
          Serial.print("Error3: Checksum error. "); 
          Serial.println();	// next line
          Serial.println();	// next line
          Serial.println();	// next line
          // ============== I2C LCD1602 ==============
          myI2C.home();           	// cursor home 
          myI2C.print("== Error 3 =="); // display string
          break;
    }
    delay(10000);   // pause 10 seconds 
}

//**************************************************************
// ====== readDHT11() =========== 
void readDHT11()
{  MSG=0; // valid by default
   // a 20ms (at least 18ms) LOW, followed by a 20us~40us HIGH--Start signal to DHT11
   // microcontroller sends out a 20ms LOW, followed by a 40us HIGH,
   // then waits for (40us) an ACK from DHT11 
   digitalWrite(DHT_p,0);delay(20);		// a 20ms LOW
   digitalWrite(DHT_p,1);delayMicroseconds(40);
   // a 40us HIGH, let DHT11 to pull LOW (ACK)
   
   // ======= valid ACK signal is a 80us LOW ===================
   pinMode(DHT_p,INPUT);	// configure analog pin A0 as input
   byte DHT_in=digitalRead(DHT_p);	// read DHT11 (ACK) 
   
   // if a HIGH is read (error 1)
   if(DHT_in) { MSG=1;return; } 	// No ACK
   
   // ====== if a LOW is read, it should be a HIGH after 80us ======
   delayMicroseconds(80);
   DHT_in=digitalRead(DHT_p);	 	// read DHT11
   
   // if a LOW is read (error 2)
   if(!DHT_in)  { MSG=2;return; }
	   // if not a HIGH, ACK invalid

   // ======= after 80us, ACK valid ========
   delayMicroseconds(80);

   // ======= continue to receive data =========
   for(byte i=0; i<5; i++) T_H[i]=readDHT_byte(); // read DHT11 data (5 bytes) 
   pinMode(DHT_p,OUTPUT);	// respond to DHT11 ACK
   digitalWrite(DHT_p,1);	// terminate data transmission 

   // Checksum 
   byte dht_check_sum = T_H[0]+T_H[1]+T_H[2]+T_H[3];
   if(T_H[4]!= dht_check_sum)    MSG=3;	// Checksum Error(3)
}
 
// ========== readDHT_byte() ==================
byte readDHT_byte()
{  byte result=0;
   // code 0: a 50us LOW, followed by a 26us~28us HIGH 
   // code 1: a 50us LOW, followed by a 70us HIGH 
   for(byte i=0;i<8;i++)
   {  while(!digitalRead(DHT_p));
      delayMicroseconds(30);
      if (digitalRead(DHT_p))  result |= (1<<(7-i));
      while (digitalRead(DHT_p));	// wait for a LOW
   }
   return result;
}

// ==== sendCommand() ======
void sendCommand(String cmd)	// send command to ESP8266 
{   Serial.print("SEND: ");   	// serial monitor displays “SEND:”  
    Serial.println(cmd);      	// serial monitor displays command 
    ESP.println(cmd);  		// send command to ESP8266
} 

// ==== connectWiFi() ======
boolean connectWiFi()		// connect ESP8266 to WiFi
{   ESP.println("AT+CWMODE=1");	// set Station (STA) mode
    delay(2000);
    String cmd="AT+CWJAP=\"";	// AT+CWJAP="
    cmd+=ssid;  		// AT+CWJAP="ssid
    cmd+="\",\""; 		// AT+CWJAP="ssid","
    cmd+=pass;			// AT+CWJAP="ssid","pass
    cmd+="\""; 			// AT+CWJAP="ssid","pass"
    // AT+CWJAP="ssid","pass"
    sendCommand(cmd);		// connect to WiFi
    delay(5000);
    if(ESP.find("OK")) 		// if ok,
    {   Serial.println("RECEIVED: OK");
        return true;
    }
    else			// if not ok,
    {   Serial.println("RECEIVED: Error");
        return false;
    }

    // set single connection mode
    cmd = "AT+CIPMUX=0"; 
    sendCommand(cmd);
    if(ESP.find("Error"))	// if error occurs,
    {   Serial.print("RECEIVED: Error");
        return false;
    }
}

//============ updateCloud() ====================
void updateCloud(String T, String H)
{   // set ESP8266 as Client, connected to ThingSpeak website 
    String cmd = "AT+CIPSTART=\"TCP\",\"";	// AT+CIPSTART="TCP","
    cmd += ThingSpeak; 	// AT+CIPSTART="TCP","ThingSpeak
    cmd += "\",80";     	// AT+CIPSTART="TCP","ThingSpeak",80
    // AT command: AT+CIPSTART="TCP","ThingSpeak",80
    sendCommand(cmd);
    if( ESP.find( "Error" ) ) 	// if ESP8266 connection error occurs, 
    {   Serial.print( "RECEIVED: Error\nExit1" );
  		// display error message in the serial monitor window
        return;
    }
    cmd = GET + "&field1=" + T + "&field2=" + H +"\r\n";
    // webpage command: GET+field1 data+T+field2 data+H+(CR+NL)
    // GET&field1=T&field2=H
    ESP.print( "AT+CIPSEND=" );	// send AT+CIPSEND command to ESP8266
    // AT+CIPSEND=length
    ESP.println( cmd.length() );   // send command to ESP8266
    if(ESP.find( ">" ) ) 	   // if ESP8266 finds the prompt >, 
    {   Serial.print(">");	   // serial monitor displays the prompt >
        Serial.print(cmd);	   // serial monitor displays commands
        // > GET&field1=T&field2=H
        ESP.print(cmd);  	   // send command to ESP8266
    }
    // If ESP8266 does not find the prompt >, close ESP8266
    else  ESP.print("AT+CIPCLOSE");
    
    if(ESP.find("OK")) Serial.println("RECEIVED: OK");
    else Serial.println("RECEIVED: Error\nExit2");
}

