#define PRINT(s) Serial.print("[" + String(millis()) + "]" + s)

#include <ESP8266WiFi.h>
#include "WebInterface.h"

WiFiServer server(80);
WiFiClient client;

void setup() {
  Serial.begin(115200);
  while (!Serial) delay(1);
  Interface.begin(client);
  WiFi.mode(WIFI_STA);
  WiFi.begin("Yong", "yong1020");
  Serial.println("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) delay(1);
  Serial.println("WiFi Connected");
  server.begin();
  Serial.print("Server Started\nIP Address: ");
  Serial.println(WiFi.localIP());
  delay(100);
}

void loop() {
  client = server.available();
  if (client)
    Interface.run();

}
