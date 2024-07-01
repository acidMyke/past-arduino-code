#include <SPI.h>
#include <Ethernet.h>

#define PRINT(s) Serial.println("[" + String(millis()) + "]" + s)
#define ID "2"

//IPAddress ip = IPAddress(192, 168, 4, 40);
IPAddress host = IPAddress(192, 168, 1, 155);

const int httpPort = 8080;

byte mac[] = {
  0xAC, 0xAA, 0xBB, 0xCC, 0xDE, 0x02
};


void setup() {
  Serial.begin(115200);
  delay(100);

  PRINT("Begin");
  if(!Ethernet.begin(mac)){
    PRINT("Failed to connect");
    return;
  }
  Serial.print("Ethernet started\nIP Address: ");
  Serial.println(Ethernet.localIP());
}

void loop() {
  PRINT("Connecting to host");

  EthernetClient client;
  if (!client.connect(host, httpPort)) {
    PRINT("Connection Failed");
    return;
  }

  client.print(ID);
  
  uint64_t timeout = millis() + 5000;
  while (!client.available() && timeout > millis()) delay(10);
  if (timeout < millis()) {
    PRINT("Connection Timeout");
    client.stop();
    return;
  }
  else if (client.available()) {
    PRINT("Server connected\nRespone:");
    while (client.available()) Serial.print(client.read(), HEX);
    Serial.println();
    PRINT("\n\nEnd of respond");
    if(Serial.available()) client.print(Serial.read());
    client.println();
  }
  else
    PRINT("Unidentified ERROR");
  delay(500);
  client.stop();
}

