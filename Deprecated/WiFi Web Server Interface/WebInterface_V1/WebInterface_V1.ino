#include <ESP8266WiFi.h>

WiFiServer server(80);

IPAddress myIP;

const char ssid[] = "KEXINPC", pass[] = "19101109";
bool rmem;

int count = 0;

typedef enum {NA, Latch, Momentary} Type;

int vari[32], minV[32], maxV[32];
Type type[32];

//////////
void setup() {
  WiFi.disconnect();
  Serial.begin(115200);
  while (!Serial) delay(1);
  delay(5000);
  begin();
  createSwitch(0, 0, 2, Latch);
  WiFi.mode(WIFI_STA);
  Serial.println("\nConnecting to " + String(ssid));
  WiFi.begin(ssid, pass);
  int newMillis = millis();
  while (WiFi.status() != WL_CONNECTED) {
    if ((Serial.available() && Serial.read() == 0x74) || millis() - newMillis > 10000){
      newMillis = millis();
      WiFi.disconnect();
      delay(500);
      WiFi.begin(ssid, pass);
    }
    Serial.print((char)0x2E);
    delay(1000);
  }
  Serial.println("\nWiFi Connected");
  server.begin();
  Serial.println("Server Started\nIPAddress: " + WiFi.localIP().toString());
  delay(100);
}

void loop() {
  if (Serial.available()) {
    if (Serial.read() == 0x74) {
      Serial.println("Terminated");
      server.close();
      WiFi.disconnect();
    }
    else if (Serial.read() == 0x73) {
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
  }
  wifiServer(server.available());
}

void wifiServer(WiFiClient client) {
  if (client) {
    Serial.println("\n["+ String(millis()) + "][New Client]");
    int newMillis = millis() + 2000;
    while (!client.available() && newMillis > millis()) delay(1);
    String request = client.readString();
    Serial.println("Request: \n\n" + request + "\n\nEnd of Request\n");
    client.println(process(request));
  }
}

