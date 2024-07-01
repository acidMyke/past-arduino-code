#define LOG(s) Serial.print("[" + String(millis()) + "] " + s)
#define PRINT(s) Serial.print(s)
#define IPString(a) (String(a[0], DEC) + "." + String(a[1], DEC) + "." + String(a[2], DEC) + "." + String(a[3], DEC))

#define FUNCTION_START (byte)0x46
#define STRING_START (byte)0x57
#define BYTE_START (byte)0x42
#define END (byte)0x04

#include <SPI.h>
#include <Ethernet.h>
#include "SyncCommand.h"

byte mac[] = {
  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED
};

IPAddress ip(192, 168, 2, 177);

IPAddress host(192, 168, 2, 1);
unsigned int port = 8080;

EthernetClient client;
SyncCommand Sync;

void setup() {
  Serial.begin(115200);
  Ethernet.begin(mac, ip);
  Sync.begin(client);
  Sync.onByteReceived(byteReceive);
  Sync.onStringReceived(strReceive);
  delay(15000);
  LOG("BEGIN\r\n");
}

void loop() {
  if (!client || !client.connected()) {
    client.stop();
    LOG("Connecting to Server: " + IPString(host) + ":" + String(port));
    client.connect(host, port);
    uint32_t timeout = millis() + 5000;
    while (!client.connected() && millis() < timeout) {
      delay(250);
      PRINT(".");
    }
    PRINT("\r\n");
    if (!client.connected()) {
      LOG("Timeout\r\n");
      return;
    }
    LOG("Server Connected\r\n");
    client.print("Connected");
  }
  client.print("Request\n");
  Sync.run();
}

String byteReceive() {
  unsigned time = Sync.getUInt();
  Serial.println("Receive: " + String(time) + " = " + String(time/3600) + ":" + String((time%3600)/60) + ":" + String(time%60));
  return "Received";
}

String strReceive(String str) {
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



