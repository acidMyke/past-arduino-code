#define LOG(s) Serial.print("[" + String(millis()) + "] " + s)
#define PRINT(s) Serial.print(s)
#define IPString(a) (String(a[0], DEC) + "." + String(a[1], DEC) + "." + String(a[2], DEC) + "." + String(a[3], DEC))

#define FUNCTION_START (byte)0x46
#define STRING_START (byte)0x57
#define BYTE_START (byte)0x42

#include <SPI.h>
#include <Ethernet.h>
#include "SyncCommand.h"

IPAddress ip(192, 168, 1, 3);
byte mac[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0x03};

IPAddress host(192, 168, 1, 254);
unsigned int port = 8080;

EthernetClient client;
SyncCommand Sync;

uint32_t retry = 30000;
uint32_t prevRun = 0;

void setup() {
  Serial.begin(9600);
  LOG("BEGIN\r\n");
  delay(1000);
  if(Ethernet.begin(mac) == 0){
    LOG("DHCP Failed\r\nUsing Preset IP\r\n");
    Ethernet.begin(mac, ip);
  }
  delay(1000);
  LOG("BEGIN\r\n");
  LOG("Ethernet Started\r\nIPAddress: " + IPString(Ethernet.localIP()) + "\r\n");
  Sync.begin(client, Serial);
  Sync.onByteReceived(byteReceive);  //Sync.onByteReceived(function)
  Sync.onStringReceived(strReceive); //Sync.onStringReceived(function)
  //delay(15000);
  //The code start here
  
}

void loop() {
  connect();
  //The code start here
  delay(250);
  LOG(analogRead(A1) + "\r\n");
}

void connect() { // don't change
  if ((!client || !client.connected()) && millis() > prevRun) {
    client.stop();
    LOG("Connecting to Server: " + IPString(host) + ":" + String(port) + "\r\n");
    client.connect(host, port);
    uint32_t timeout = millis() + 5000;
    //while (!client.connected() && millis() < timeout);
    if (!client.connected()) {
      LOG("Timeout\r\n");
      client.stop();
    }
    else {
      LOG("Server Connected\r\n");
      client.print("Connected\t");
    }
    prevRun = millis() + retry;
  }
  if (client && client.connected()) {
    prevRun = millis() + retry;
    client.print("Request\n");
    Sync.run();
  }
}

String byteReceive() { //When byte is receive
  unsigned time = Sync.getUInt();
  Serial.println("Receive: " + String(time) + " = " + String(time / 3600) + ":" + String((time % 3600) / 60) + ":" + String(time % 60));
  return "Receive: " + String(time / 3600) + ":" + String((time % 3600) / 60) + ":" + String(time % 60);
}

String strReceive(String str) { //When String is receive
  Serial.println("Received: " + str);
  return "Received";
}

String Byte(byte b) {
  String str = String(b, BIN);
  switch (str.length()) {
    case 1: str = "0000000" + str; break;
    case 2: str = "000000" + str; break;
    case 3: str = "00000" + str; break;
    case 4: str = "0000" + str; break;
    case 5: str = "000" + str; break;
    case 6: str = "00" + str; break;
    case 7: str = "0" + str; break;
    case 8: str = str; break;
  }
  return str;
}
