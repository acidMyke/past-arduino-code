#define PRINT(s) Serial.print("[" + String(millis()) + "]" + s)

#include <SPI.h>
#include <Ethernet.h>
#include <SyncCommand.h>
#include "WebInterface.h"

EthernetServer server(80);
EthernetClient client;

byte mac[] = {
  0xAC, 0xAA, 0xBB,  0xCC, 0xDE, 0x02
};

IPAddress ip(192,168,1,2); // if DHCP is not available

String htmlStream;

void setup() {
  Serial.begin(9600);
  delay(100);
  while (!Serial) delay(1);
  Serial.println("Begin");
  if (!Ethernet.begin(mac)) {
    Serial.println("Failed to connect to network\nTrying Again\n");
    Ethernet.begin(mac, ip);
  }
  Serial.println("Ethernet started\n");
  server.begin();
  Serial.println("Server Started");
  Serial.print("IP address: ");
  Serial.println(Ethernet.localIP());

  Interface.begin(client);
}

void loop() {
  client = server.available();
  if (client)
    Interface.run();
}
