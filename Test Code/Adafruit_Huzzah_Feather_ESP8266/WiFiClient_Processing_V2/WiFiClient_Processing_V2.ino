#include <ESP8266WiFi.h>

#define PRINT(s) Serial.println("[" + String(millis()) + "]" + s)
#define ID "2"

const char* ssid = "Yong";
const char* pass = "yong1020";

IPAddress host = IPAddress(192, 168, 1, 155);
const int httpPort = 8080;

String generate (String = "");

void setup() {
  Serial.begin(115200);
  delay(100);

  PRINT("\n\nConnecting to " + String(ssid));
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, pass);

  while (WiFi.status() != WL_CONNECTED)  delay(500);

  PRINT("\n\nWiFi Connected\nIP address: " + WiFi.localIP().toString());
}

void loop() {
  PRINT("Connecting to " + host.toString() + ":" + httpPort);
  
  WiFiClient client;
  if (!client.connect(host, httpPort)) {
    PRINT("Connection to " + host.toString() + ":" + httpPort + " has FAILED");
    return;
  }
  client.print(ID);

  uint64_t timeout = millis() + 5000;
  while (!client.available() && timeout > millis()) delay(10);
  if (timeout < millis()) {
    PRINT(host.toString() + ":" + httpPort + "Timeout !!");
    client.stop();
    return;
  }
  else if (client.available()) {
    PRINT(host.toString() + " connected\r\nRespond from Server: \r\n");
    while(client.available()) Serial.print(client.read(), HEX);
    Serial.println();
    client.println();
  }
  else PRINT("Unidentified ERROR");
  delay(500);
}


