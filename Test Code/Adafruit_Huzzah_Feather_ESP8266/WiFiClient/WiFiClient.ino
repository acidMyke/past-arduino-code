#include <ESP8266WiFi.h>

const char* ssid = "Yong";
const char* pass = "yong1020";

IPAddress host = IPAddress(192, 168, 1, 155);
const int httpPort = 8080;

String input;

void setup() {
  Serial.begin(115200);
  delay(100);

  Serial.print("\n\nConnecting to " + String(ssid));
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, pass);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\n\nWiFi Connected\nIP address: " + WiFi.localIP().toString());
}

void loop() {
  Serial.println("Connecting to " + host.toString() + ":" + httpPort);

  WiFiClient client;
  if (!client.connect(host, httpPort)) {
    Serial.println("Connection to " + host.toString() + ":" + httpPort + " has FAILED");
    return;
  }

  client.print("GET / HTTP/1.1\r\nHost: " + host.toString() + ":" + httpPort + "\r\nConnection: close\r\n\r\n");

  uint64_t timeout = millis() + 5000;
  while (!client.available() && timeout > millis()) delay(10);
  if (timeout < millis()) {
    Serial.println("Timeout !!");
    client.stop();
    return;
  }
  else if (client.available()) {
    input = client.readString();
    Serial.println(host.toString() + " connected\r\nRespond from Server: \r\n" + input + "\r\n\r\nClosing Connection");
    client.stop();
  }
  else Serial.println("Unidentified ERROR");
  delay(5000);
}
