#define ID 0x03
#define LOG(s) Serial.print("[" + String(millis()) + "] ") +  Serial.print(s)
#define PRINT(s) Serial.print(s)
#define IPString(a) (String(a[0], DEC) + "." + String(a[1], DEC) + "." + String(a[2], DEC) + "." + String(a[3], DEC))

#include <SPI.h>
#include <Ethernet.h>
#include "SyncCommand.h"

//Local
IPAddress ip(192, 168, 1, ID);
byte mac[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, ID};

//Server
IPAddress host(192, 168, 1, 254);
int port = 80;

EthernetClient client;
SyncCommand Sync;

uint32_t retry = 30000;
uint32_t prevRun = 0;
uint32_t heartbeatTimer = 0;

void setup() {
  Serial.begin(9600); // For Debug
  LOG("Serial Started\r\n");
  if (!Ethernet.begin(mac)) {
    LOG("DHCP Failed\r\nUsing Preset IP\r\n");
    Ethernet.begin(mac, ip);
  }
  LOG("Ethernet Started\r\n");
  LOG("IP Address: " + IPString(Ethernet.localIP()) + "\r\n");
  Sync.begin(client, Serial);
  Sync.addFunction((byte)0x02, onStringRecevied);
  Sync.addFunction((byte)0x04, onByteRecevied);
  Sync.addFunction((byte)'~', heartbeat);
}

void loop() {
  connect();
  //The code start here
  delay(250);
  if (client && client.connected()) LOG("Connected\r\n");
  else LOG("Disconnected\t" + String(prevRun - millis()) + " millis to reconnection\r\n");
  if (client.connected() && Serial.available()){
    String str = Serial.readString();
    client.print(str);
    Serial.println("Sending: " + str);
  }
}

void connect() { // don't change
  if (!client.connected() && millis() > prevRun) {
    client.stop();
    LOG("Connecting to Server: " + IPString(host) + ":" + String(port) + "\r\n");
    client.connect(host, port);
    uint32_t timeout = millis() + 5000;
    while (!client.connected() && millis() < timeout);
    if (!client.connected()) {
      LOG("Connection Timeout\r\n");
      client.stop();
    }
    else {
      LOG("Server Connected\r\n");
      client.print("Connected\t");
    }
    prevRun = millis() + retry;
  }
  if (client.connected()) {
    if(millis() > heartbeatTimer){
      client.stop();
      LOG("Heartbeat Timeout\r\n");
      prevRun = 0;
    }
    prevRun = millis() + retry * 0.1;
    Sync.run(200);
  }
}

String onByteRecevied() {
  Serial.println("Byte Recv: 0x" + String(Sync.getByte(), HEX));
  return "";
}

String onStringRecevied() {
  String str = Sync.getString((byte)0x03);
  Serial.println("->" + str);
  if (str.equalsIgnoreCase("millis")) {
    return String(millis());
  }
  else if (str.equalsIgnoreCase("Status")) {
    return String(analogRead(A1));
  }
  return "NA";
}

String heartbeat() {
  heartbeatTimer = millis() + 11000;
  LOG("Heartbeat recevied\r\n");
  return "~";
}
