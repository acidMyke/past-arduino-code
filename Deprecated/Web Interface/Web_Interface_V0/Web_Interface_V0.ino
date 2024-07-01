#define PRINT(s) Serial.print("[" + String(millis()) + "]" + s)

#include <SPI.h>
#include <Ethernet.h>
#include <SyncCommand.h>
#include "WebInterface.h"

EthernetServer server(80);
EthernetClient client;

IPAddress ip(192, 168, 4, 2);

byte mac[] = {
  0xAC, 0xAA, 0xBB,  0xCC, 0xDE, 0x02
};

void setup() {
  Serial.begin(115200);
  delay(100);
  while (!Serial) delay(1);
  Ethernet.begin(mac, ip);
  Serial.println("Ethernet started");
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
