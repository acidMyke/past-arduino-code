#define LOG(s) Serial.print("[" + String(millis()) + "] ") + Serial.print(s)
#define PRINT(s) Serial.print(s)
#define IPString(a) (String(a[0], DEC) + "." + String(a[1], DEC) + "." + String(a[2], DEC) + "." + String(a[3], DEC))

#include <SPI.h>
#include <Ethernet.h>
#include "utility/socket.h"

byte mac[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 02};

IPAddress host(192, 168, 1, 254);
int port = 8080;

SOCKET sock;
EthernetClient client = EthernetClient(sock);

uint32_t timeout = 0;

void setup() {
  Serial.begin(9600);
  LOG("Serial Started\r\n");
  Ethernet.begin(mac);
  LOG("Ethernet Started\r\n");
  LOG("IP Address: " + IPString(Ethernet.localIP()) + "\r\n");
}

void loop() {
  if (socketStatus(sock) != SnSR::ESTABLISHED) {
    disconnect(sock);
    LOG("Connecting to Server: " + IPString(host) + ":" + String(port) + "\r\n");
    connect(sock, rawIPAddress(host), port);
    timeout = millis() + 10000;
    while (socketStatus(sock) != SnSR::ESTABLISHED && timeout > millis());
    if (socketStatus(sock) == SnSR::ESTABLISHED) {
      LOG("Server connected");
    }
    else {
      LOG("Connection Failed\r\n");
    }
  }
}

uint8_t* rawIPAddress(IPAddress _ip) {
  uint8_t bytes[4] = {_ip[0], _ip[1], _ip[2], _ip[3]};
  return bytes;
}

