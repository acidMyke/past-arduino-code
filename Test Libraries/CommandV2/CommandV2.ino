#define ID 0x02
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
int port = 8080;

EthernetClient client;
SyncCommand Sync;

uint32_t retry = 30000;
uint32_t prevRun = 0;

void setup() {
  Serial.begin(9600);
  LOG("Serial Started\r\n");
  if (!Ethernet.begin(mac)) {
    LOG("DHCP Failed\r\nUsing Preset IP\r\n");
    Ethernet.begin(mac, ip);
  }
  LOG("Ethernet Started\r\n");
  LOG("IP Address: " + IPString(Ethernet.localIP()) + "\r\n");
  Sync.begin(client, Serial);
  Sync.addFunction((byte)0x03, onStringRecevied);
}

void loop() {
  connect();
  //The code start here
  delay(250);
  LOG(String(analogRead(A1)) + "\r\n");
  if (client && client.connected()) LOG("Connected\r\n");
  else LOG("Disconnected\t" + String(prevRun - millis()) + " millis to reconnection\r\n");
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
    if(millis() )
    Sync.run(200);
  }
}

String onStringRecevied() {
  String str = Sync.getString();
  Serial.println("->" + str);
  if (str.equalsIgnoreCase("millis")) {
    return String(millis());
  }
  else if (str.equalsIgnoreCase("Status")) {
    return String(analogRead(A1));
  }
  return "NA";
}


