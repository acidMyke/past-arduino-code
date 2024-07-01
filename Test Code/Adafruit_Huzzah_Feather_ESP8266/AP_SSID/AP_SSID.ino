#include <ESP8266WiFi.h>

char *ssid;
char *pass;
String req = "";

WiFiServer server(80);
WiFiClient client;

void handleRoot() {

}

void setup() {
  enableAP();
  while(ssid == 0) {
    recieved();
  }
  Serial.println("Hello World");
}

void loop() {
}

void enableAP() {
  WiFi.mode(WIFI_AP);
  delay(1000);
  Serial.begin(115200);
  Serial.println();
  Serial.print("Configuring access point...");
  WiFi.softAP("ESP8266", "123456789");

  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);
  server.begin();
  Serial.println("Server started\n");
}

void recieved() {
  client = server.available();
  if (client) {
    Serial.println("new client\n");
    while (!client.available()) {
      delay(1);
    }
    String html = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n<!DOCTYPE html>\r\n<html>\r\n<style>\r\nform {\r\n    border: 3px solid #f1f1f1; \r\n}\r\n\r\ninput[type=text], input[type=password] {\r\n    width: 100%;\r\n    padding: 12px 20px; \r\n    margin: 8px 0; \r\n    display: inline-block; \r\n    border: 1px solid #ccc; \r\n    box-sizing: \r\norder-box; \r\n}\r\n\r\nbutton {\r\n    background-color: #4CAF50; \r\n    color: white; \r\n    \r\npadding: 14px 20px; \r\n    margin: 8px 0; \r\n    border: none; \r\n    cursor: pointer; \r\n width: 100%;\r\n}\r\n\r\nbutton:hover {\r\n    opacity: 0.8; \r\n}\r\n\r\n.container {\r\n    padding: 16px; \r\n}\r\n\r\nspan.psw {\r\n    float: right; \r\n    padding-top: 16px; \r\n}\r\n\r\n</style>\r\n<body>\r\n<form action= \"/action_page.php\">\r\n  <div class=\"container\">\r\n    <label><b>SSID</b></label>\r\n    <input type=\"text\" placeholder=\"Enter your SSID\" name=\"ssid\" required>\r\n\r\n    <label><b>Password</b></label>\r\n    <input type=\"password\" placeholder=\"Enter your password\" name=\"psw\" required>\r\n\r\n    <button type=\"submit\">Connect</button>\r\n</form>\r\n\r\n</body>\r\n</html>";
    //Serial.println(html);
    client.print(html);
    req = client.readStringUntil('\r');
    req.replace(" HTTP/1.1", "");
    req.replace("GET ", "");
    req.replace("/", " ");
    req.trim();
    Serial.println(req);
    client.flush();

    if (req.startsWith("action_page.php")) {
      req.replace("action_page.php?ssid=", "");
      int n = WiFi.scanNetworks();
      Serial.println("scan done");
      if (n == 0) {
        Serial.println("no networks found");
        Serial.println("Please renter your WiFi SSID and Password");
      }
      else
      {
        Serial.print(n);
        Serial.println(" networks found");
        for (int i = 0; i < n; ++i) {
          if (req.startsWith(WiFi.SSID(i))) {
            Serial.println("Found SSID");
            req.replace(WiFi.SSID(i), "");
            req.replace("&psw=", "");
            html = "<html>\r\n<text>You are now connected</text>\r\n</html>\r\n";
            Serial.println(html);
            client.println(html);
            WiFi.SSID(i).toCharArray(ssid,32);
            req.toCharArray(pass,32);
            
            Serial.println(ssid);
            Serial.println(pass);
            n = 0;
            break;
          }
          else {
            Serial.println("no match found");
          }
        }
        if (n == 0) {
          html = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n<!DOCTYPE html>\r\n<html>\r\n<text>No match SSID, Please make that you have entered a correct SSID</text>\r\n</html>\r\n";
          Serial.println(html);
          client.println(html);
        }else{
          break;
        }
      }
    }
  }
}
/*
  void command() {
  if (req.startsWith("connection")) {
    int n = WiFi.scanNetworks();
    Serial.println("scan done");
    if (n == 0)
      Serial.println("no networks found");
    else
    {
      Serial.print(n);
      Serial.println(" networks found");

      for (int i = 0; i < n; ++i) {
        Serial.print(i + 1);
        Serial.print(": ");
        Serial.print(WiFi.SSID(i));
        Serial.print(" (");
        Serial.print(WiFi.RSSI(i));
        Serial.print(")");
        Serial.println((WiFi.encryptionType(i) == ENC_TYPE_NONE) ? " " : "*");
        delay(10);
        available_SSID += WiFi.SSID(i);
        if (i != n - 1) {
          available_SSID += ",";
        }
      }
      available_SSID += "</p>\r\n</body>\r\n</html>\n";

      req = "";
    }
  }
  }
*/
