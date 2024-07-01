#define PRINTM(s) Serial.print(s)
#define PRINTMLN(s) Serial.println(s)
#define PRINT(s) Serial.print("[" + String(millis()) + "] " + s)
#define PRINTLN(s) Serial.println("[" + String(millis()) + "] " + s)

#define FUNCTION_START (byte)0x46
#define STRING_START (byte)0x57
#define BYTE_START (byte)0x42
#define END (byte)0x04 

#include <SPI.h>
#include <Ethernet.h>
#include "SyncCommand.h"

//Any MAC address that aren't use in local network
byte mac[] = {
  0xAC, 0xAA, 0xBB, 0xCC, 0xDE, 0x02
};

SyncCommand Sync;
EthernetClient client;
IPAddress ip(192, 168, 4, 2);

IPAddress host(192, 168, 4, 1);

int hostPort = 80;

String input;

void setup() {
  Serial.begin(115200);
  delay(100);
  PRINT("BEGIN\n");

  Ethernet.begin(mac, ip);
  PRINT("Ethernet Started\n");
  PRINT("IPAddress: ");
  PRINTMLN(Ethernet.localIP());

  Sync.begin(client, Serial);
}

void loop() {
  if (!client || !client.connected()) {
    PRINT("Connecting to host: ");
    PRINTM(host);
    PRINTM(":" + String(hostPort) + "\n");
    if(!client.connect(host, hostPort)){
      PRINT("Connection Failed\n");
//    int error = client.connect(host, hostPort);
//    if (!error) {
//      PRINT("Connection Failed\n");
//      switch(error){
//        case  1: PRINTLN("Success"); break;
//        case -1: PRINTLN("Timed Out"); break;
//        case -2: PRINTLN("Invalid Server"); break;
//        case -3: PRINTLN("Truncated"); break;
//        case -4: PRINTLN("Invalid Respone"); break;
//        default: PRINTLN("Error code: " + String(error)); break;
//      }
      return;
    }
    PRINT("Host connected\n");
  }

  client.print("2");

  uint64_t timeout = millis() + 5000;
  while (!client.available() && timeout > millis()) delay(10);
  if (timeout < millis()) {
    PRINT("Connection Timeout\n");
    client.stop();
    return;
  }
  else if (client.available()) {
    int code = Sync.run();
    if(code == -1) Serial.println("No Match");
    if(code == BYTE_START) Serial.println(Sync.getByte(), HEX);
    if(code == STRING_START) Serial.println(Sync.getString());
  }
  else
    PRINT("Unidentified ERROR\n");
  delay(500);

  client.flush();
}

