#define ID 0x02 //Unqine for every device
#define LOG(s) Serial.print("[" + String(millis()) + "] ") +  Serial.print(s)
#define PRINT(s) Serial.print(s)
#define IPString(a) (String(a[0], DEC) + "." + String(a[1], DEC) + "." + String(a[2], DEC) + "." + String(a[3], DEC)) // ChangeIPAddress class to string

//keyword
#define STRING_START (byte)0x02 //When string begin
#define STRING_END (byte)0x03   //When string end
#define BYTE_START (byte)0x04   //When byte start
#define HEARTBEAT (byte) 0x7E   //When server send a heartbeat

//#define NUM_FUNCTION 32 //If need more than 32 function, uncomment and change

#include <SPI.h> //Use by Ethernet.h
#include <Ethernet.h> //Use for the communication to the W5100 Chip
#include "StreamFunction.h" //Use to detect keyword in "stream" //Header file can be found in next tab

//Local
IPAddress ip(192, 168, 1, ID); //Static IP if DHCP Fail
byte mac[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, ID}; //Unqine for every device

//Server
IPAddress host(192, 168, 1, 254); //Host/Server IP Address
int port = 80; //Host/Server Port

EthernetClient client; // Create an instance of client
StreamFunction Sync; // Create an instance of class: StreamFunction (Included in StreamFunction.h)

//Timer Duration (Changeable)
uint32_t retry = 30000; //If the arduino is not connected, it will wait for "retry" before reconnecting // in milliseconds
uint32_t heartbeatDuration = 10000; //If the arduino is connected and a heartbeat is not recevied within "heartbeatDuration", it will disconnect

//Variable to store time
uint32_t prevRun = 0;  //Store the previous connection time
uint32_t heartbeatTimer = 0; //Store the previous heartbeat time

void setup() {
  Serial.begin(9600); // For Debugging
  LOG("Serial Started\r\n"); //For Debugging
  if (!Ethernet.begin(mac)) { //Start the ethernet connection with DHCP
    LOG("DHCP Failed\r\nUsing Static IP\r\n");
    Ethernet.begin(mac, ip); //Use static IP if DHCP no available
  }
  LOG("Ethernet Started\r\n"); //For Debugging
  LOG("IP Address: " + IPString(Ethernet.localIP()) + "\r\n");//For Debugging

  //Sync.begin(client);
  Sync.begin(client, Serial); //Send the reference of client to Sync

  //Sync.addFunction(byte, function) //byte is the character to detect. //Function pointer that accepted no parameter and return type String
  Sync.addFunction(STRING_START, onStringRecevied);
  Sync.addFunction(BYTE_START, onByteRecevied);
  Sync.addFunction(HEARTBEAT, onHeartbeatRecevied);
}

void loop() {
  connect(); //Try to connect to server
  //The code start here (Running independently with/without server)
  delay(250);
  if (client && client.connected()) LOG("Connected\r\n"); // For Debugging
  else LOG("Disconnected\t" + String(prevRun - millis()) + " millis to reconnection\r\n");// For Debugging
  if (client.connected() && Serial.available()) { //For Testing (Return info to Server)
    String str = Serial.readString();//
    client.print(str);
    Serial.println("Sending: " + str);
  }
}

void connect() {//Trying to connect to server
  if (!client.connected() && millis() > prevRun) {
    client.stop(); //Stop the ghost connection in order to reconnect
    LOG("Connecting to Server: " + IPString(host) + ":" + String(port) + "\r\n"); // For Debugging
    client.connect(host, port); //Connect to server //Interal incremental timeout around 2-15 seconds
    uint32_t timeout = millis() + 5000; //Timeout if server not connected //Not
    while (!client.connected() && millis() < timeout); //Wait for timeout
    if (!client.connected()) { //if the client fail to connect
      LOG("Connection Failed\r\n"); // For Debugging
      client.stop(); //Stop the connection
    }
    else {//if the client is connected
      LOG("Server Connected\r\n"); // For Debugging
      client.print("Connected\t"); //Prompt the server, can be anything, but required
      heartbeatTimer = millis() + heartbeatDuration; //Set the next heartbeat to be "heartbeatDuration" milliseconds away
    }
    prevRun = millis() + retry; //Set the next retry time
  }
  if (client.connected()) {
    if (millis() > heartbeatTimer) { //If heartbeat no recevied within heartbeatTimeout
      client.stop(); //Disconnect from server
      LOG("Heartbeat Timeout\r\n");// For Debugging
    }
    prevRun = millis() + retry * 0.1; //Set for a small retry time in case of sudden updating of the server
    Sync.run(200); //Sync.run(timeout) will call the function added by .addFunction in setup if the keyword is detected
  }
}

String onByteRecevied() { // If the keyword is detected, Sync.run will call this
  /*Function of StreamFunction:
     available()  //If data is available
     getByte()    //Return the data in byte
     getChar()    //Return the data in char
     getInt()     //Return the data in int
     getUInt()    //Return the data in usigned int
     getLong()    //Return the data in long
     getULong()   //Return the data in usigned long
     getString()  //Return the data in String
  */
  if (Sync.available())
    Serial.println("Byte Recv: 0x" + String(Sync.getByte(), HEX));
  return "INVALID"; //Return will send the string to the server
}

String onStringRecevied() {
  String str = Sync.getString((byte)0x03);
  Serial.println("->" + str);
  return "INVALID";
}

String onHeartbeatRecevied() {
  heartbeatTimer = millis()+ 1000 + heartbeatDuration; //Set the next expected heartbeat time
  LOG("Heartbeat recevied\r\n"); //For Debbuging
  return String((char)HEARTBEAT); //Reply the same heartbeat
}


