#define ID 0x04
#define LOG(s) Serial.print("[" + String(millis()) + "] ") +  Serial.print(s)
#define PRINT(s) Serial.print(s)
#define IPString(a) (String(a[0], DEC) + "." + String(a[1], DEC) + "." + String(a[2], DEC) + "." + String(a[3], DEC))

#include <ESP8266WiFi.h>
#include "SyncCommand.h"

const char* ssid     = "NoNetwork";
const char* password = "123456789";

//Local
IPAddress ip(192, 168, 1, ID);
byte mac[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, ID};

//Server
IPAddress host(192, 168, 1, 254);
int port = 8080;

WiFiClient client;
SyncCommand Sync;

uint32_t retry = 30000;
uint32_t prevRun = 0;

void setup() {
  Serial.begin(9600);
  LOG("Serial Started\r\n");
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) delay(50);
  LOG("WiFi Started\r\n");
  LOG("IP Address: " + WiFi.localIP().toString() + "\r\n");
  Sync.begin(client, Serial);
  Sync.addFunction((byte)0x03, onStringRecevied);
}

void loop() {
  connect();
  //The code start here
  delay(250);
  LOG(String(random(0, 1023)) + "\r\n");
  if (client && client.connected()) LOG("Connected\r\n");
  else LOG("Disconnected\t" + String(prevRun - millis()) +" millis to reconnection\r\n");
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
    Sync.run(200);
  }
}

String onStringRecevied(){
  Serial.println("->" + Sync.getString());
  return "NA";
}

