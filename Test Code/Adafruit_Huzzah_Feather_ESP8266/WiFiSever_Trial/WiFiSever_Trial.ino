/*
    This sketch demonstrates how to set up a simple HTTP-like server.
    The server will set a GPIO pin depending on the request
      http://server_ip/gpio/0 will set the GPIO2 low,
      http://server_ip/gpio/1 will set the GPIO2 high
    server_ip is the IP address of the ESP8266 module, will be
    printed to Serial when the module is connected.
*/

#include <ESP8266WiFi.h>

// Create an instance of the server
// specify the port to listen on as an argument
WiFiServer server(80);

IPAddress myIP;

String ssid, pass;
bool rmem;

void setup() {
  WiFi.mode(WIFI_AP);
  delay(1000);
  Serial.begin(115200);
  while (!Serial)delay(1);
  Serial.println();
  Serial.print("Configuring access point...");
  WiFi.softAP("ESP");

  myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);
  server.begin();
  Serial.println("Server started\n");
  delay(10);
}

void loop() {
  delay(10);
  wifiServer();
  connectWiFi();
}

void wifiServer() {
  WiFiClient client = server.available();
  if (client) {
    Serial.println("[" + String(millis()) + "]" + "New client");
    while (!client.available()) {
      delay(1);
    }
    String req = client.readString();
    req.trim();
    //Serial.println(req);
    client.flush();
    if (req.indexOf("GET") != -1) {
      String reqs = req.substring(0, req.indexOf("\r"));
      if (reqs.indexOf("Home") != -1)
        client.println(HTML("Home"));
      else if (reqs.indexOf("Control") != -1)
        client.println(HTML("Control"));
      else if (reqs.indexOf("WiFi") != -1)
        client.println(HTML("WiFi"));
      else if (reqs.indexOf("favicon.ico") != -1) {
        Serial.println("ERR");
        return;
      }
      client.flush();
      client.stop();
    }
    else if (req.indexOf("POST") != -1) {
      //Serial.println("Index Of: " + String(req.indexOf("Accept-Language: en-SG,en;q=0.9,en-US;q=0.8,zh-CN;q=0.7,zh;q=0.6")));
      //Serial.println(req.substring(req.indexOf("Accept-Language: en-SG,en;q=0.9,en-US;q=0.8,zh-CN;q=0.7,zh;q=0.6") + 68));
      if (req.indexOf("WiFi") != -1)
        client.println(POST("WiFi", req.substring(req.indexOf("Accept-Language: en-SG,en;q=0.9,en-US;q=0.8,zh-CN;q=0.7,zh;q=0.6") + 68)));
    }
    client.flush();
    client.stop();
  }
}

void connectWiFi() {
  if (ssid != NULL) {
    server.stop();
    WiFi.mode(WIFI_STA);
    delay(1000);
    char Ssid[ssid.length()], Pass[pass.length()];
    ssid.toCharArray(Ssid, ssid.length());
    pass.toCharArray(Pass, pass.length());
    delay(1000);
    int oldMillis = millis() + 60000;
    while ( WiFi.status() != WL_CONNECTED && oldMillis > millis()) {
      Serial.println("Attempting to connect to " + ssid);
      if (pass == NULL)
        WiFi.begin(Ssid);
      else
        WiFi.begin(Ssid, Pass);
      delay(5000);
    }
    if (oldMillis > millis()) {
      Serial.println("");
      Serial.println("WiFi connected");
      server.begin();
      Serial.print("IP address: ");
      Serial.println(WiFi.localIP());
    } else {
      WiFi.mode(WIFI_AP);
      delay(1000);
      Serial.println("WiFi not connected");
      Serial.println("Configuring access point...");
      WiFi.softAP("ESP");

      myIP = WiFi.softAPIP();
      Serial.print("AP IP address: ");
      Serial.println(myIP);
      server.begin();
      Serial.println("Server started\n");
      delay(10);
    }
    ssid.remove(0);
    pass.remove(0);
  }
}


