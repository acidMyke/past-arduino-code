#include <ESP8266WiFi.h>

WiFiServer server(80);

IPAddress myIP;

const char ssid[] = "KEXINPC", pass[] = "19101109";
bool rmem;

int i = 0;

void setup() {
  Serial.begin(115200);
  while (!Serial) delay(1);
  delay(5000);
  WiFi.mode(WIFI_STA);
  Serial.println("\nConnecting to " + String(ssid));
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print((char)0x2E);
    delay(1000);
  }
  Serial.println("\nWiFi Connected");
  server.begin();
  Serial.println("Server Started\nIPAddress: " + WiFi.localIP().toString());
  delay(100);
}

void loop() {
  if (Serial.available())
    if (Serial.read() == 0x74) {
      Serial.println("Terminated");
      server.close();
      WiFi.disconnect();
    }
  wifiServer(server.available());
  delay(100);
}

void wifiServer(WiFiClient client) {
  if (client) {
    Serial.println("\n[New Client]");
    int newMillis = millis() + 3000;
    while (!client.available() && newMillis > millis()) delay(1);
    String request = client.readString();
    Serial.println("Request: \n\n" + request + "End of Request\n");
    client.println(process(request));
  }
}

