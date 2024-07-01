/*
   Web Server Adapted from Makezine
*/

#define homeWiFi

#include <ESP8266WiFi.h>
#include "config.h"  // Edit your AP Setting here
String serialRequest;
String httpRequest;

WiFiServer server(80);

void setup() {
  Serial.begin(115200);
  while(!Serial)delay(1);
  // while you are not connected to your AP
  Serial.printf("[%d]\n", millis());
  
  while ( WiFi.status() != WL_CONNECTED) {
    Serial.print("Attempting to connect to Network SSID : ");
    Serial.println(ssid);
    WiFi.disconnect();
    delay(2000);
    WiFi.begin(ssid, password);
    delay(5000);
  }

  server.begin();
  Serial.printf("[%d]", millis());
  Serial.print("To see the device's web interface, go to http://");
  IPAddress ip = WiFi.localIP();
  Serial.println(ip);
}

void loop() {
  // listen for any incomming request
  WiFiClient client = server.available();
  while (client.connected()) {
    if (client.available()) {
      // read the incoming data line:
      httpRequest = client.readString();
      if (!httpRequest.startsWith("GET")) {
        httpRequest.remove(0, httpRequest.indexOf("reply=") + 6);
        httpRequest.remove(httpRequest.indexOf("\n"));
        httpRequest.replace("+", " ");
        Serial.println(httpRequest);
      }
      // if the request is blank line
      client.println(makeRespone());
      delay(100);
      client.stop();
    }
  }
  // listen to Serial Port
  while (Serial.available() > 0 ) {
    serialRequest = Serial.readStringUntil('\n');
    Serial.println(serialRequest);
    if(client.connected())client.println("location.reload()");
  }
}

String makeRespone() {
  String respone = "HTTP/1.1 200\n";
  respone += "Content-Type: text/html\n\n";
  respone += "<!doctype html>\n";
  respone += "<html><head><title>";
  respone += "Hello World</title></head>";
  respone += "\n<body>\n";
  respone += "Serial Port said: ";
  respone += serialRequest;
  respone += "<form method=\"post\">\n";
  respone += "<input type=\"text\" name=\"reply\" required>\n";
  respone += "<button type=\"submit\">Send</button>\n";
  respone += "\n</body>";

  return respone;
}




