#define ID 0x02
#define LOG(s) Serial.print("[" + String(millis()) + "] ") +  Serial.print(s)
#define PRINT(s) Serial.print(s)
#define IPString(a) (String(a[0], DEC) + "." + String(a[1], DEC) + "." + String(a[2], DEC) + "." + String(a[3], DEC))

#include <SPI.h>
#include <Ethernet.h>
#include "utility/socket.h"
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
//  LOG(String(analogRead(A1)) + "\r\n");
  printSnSR(client.getSocketNumber());
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

void printSnSR(uint16_t sock) {
  switch (socketStatus(sock)) {
      case SnSR::CLOSED:        LOG("SnSR: CLOSED\r\n"); break;
      case SnSR::INIT:          LOG("SnSR: INIT\r\n"); break;
      case SnSR::LISTEN:        LOG("SnSR: LISTEN\r\n"); break;
      case SnSR::SYNSENT:       LOG("SnSR: SYNSENT\r\n"); break;
      case SnSR::SYNRECV:       LOG("SnSR: SYNRECV\r\n"); break;
      case SnSR::ESTABLISHED:   LOG("SnSR: ESTABLISHED\r\n"); break;
      case SnSR::FIN_WAIT:      LOG("SnSR: FIN_WAIT\r\n"); break;
      case SnSR::CLOSING:       LOG("SnSR: CLOSING\r\n"); break;
      case SnSR::TIME_WAIT:     LOG("SnSR: TIME_WAIT\r\n"); break;
      case SnSR::CLOSE_WAIT:    LOG("SnSR: CLOSE_WAIT\r\n"); break;
      case SnSR::LAST_ACK:      LOG("SnSR: LAST_ACK\r\n"); break;
      case SnSR::UDP:           LOG("SnSR: UDP\r\n"); break;
      case SnSR::IPRAW:         LOG("SnSR: IPRAW\r\n"); break;
      case SnSR::MACRAW:        LOG("SnSR: MACRAW\r\n"); break;
      case SnSR::PPPOE:         LOG("SnSR: PPPOE\r\n"); break;
      default:                  LOG("Unknown: 0x" + String(socketStatus(sock), HEX)  + " \r\n"); break;
  }
}
