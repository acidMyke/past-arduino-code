/*
    This sketch demonstrates how to scan WiFi networks.
    The API is almost the same as with the WiFi Shield library,
    the most obvious difference being the different file you need to include:
*/
#include "ESP8266WiFi.h"

const char* ssid1     = "ITElab1";
const char* password1 = "12345678901234567890123456";

const char* ssid2     = "Yong";
const char* password2 = "yong1020";

const char* ssid3     = "JJ Phone";
const char* password3 = "20001227";

int oldmillis;

void setup() {
  Serial.begin(115200);

  // Set WiFi to station mode and disconnect from an AP if it was previously connected
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);

  Serial.println("Setup done");
}

void loop() {
  Serial.println("\n\nscan start");

  // WiFi.scanNetworks will return the number of networks found
  int n = WiFi.scanNetworks();
  Serial.println("scan done");
  if (n == 0)
    Serial.println("no networks found");
  else
  {
    Serial.print(n);
    Serial.println(" networks found");
    for (int i = 0; i < n; ++i) {
      // Print SSID and RSSI for each network found
      Serial.print(i + 1);
      Serial.print(": ");
      Serial.print(WiFi.SSID(i));
      Serial.print(" (");
      Serial.print(WiFi.RSSI(i));
      Serial.print(")");
      Serial.println((WiFi.encryptionType(i) == ENC_TYPE_NONE) ? " " : "*");
      delay(10);
    }
    for (int i = 0; i < n; ++i) {
      if (WiFi.SSID(i) == ssid1) {
        WIFIconnect(ssid1, password1);
      }
    }
    if (WiFi.status() != WL_CONNECTED) {
      for (int i = 0; i < n; ++i) {
        if (WiFi.SSID(i) == ssid2) {
          WIFIconnect(ssid2, password2);
        }
      }
    }
    if (WiFi.status() != WL_CONNECTED) {
      for (int i = 0; i < n; ++i) {
        if (WiFi.SSID(i) == ssid3) {
          WIFIconnect(ssid3, password3);
        }
      }
    }
    /*for (int i = 0; i < n; ++i)
      {
      if (WiFi.SSID(i) == ssid1) {
        WIFIconnect(ssid1, password1);
        break;
      } else if (WiFi.SSID(i) == ssid2) {
        WIFIconnect(ssid2, password2);
        break;
      } else if (WiFi.SSID(i) == ssid3) {
        WIFIconnect(ssid3, password3);
        break;
      }*/
  }
  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("\n\n\n\n\nWiFi Disconected");
    WiFi.disconnect();
  }
  // Wait a bit before scanning again
  delay(5000);
}

void WIFIconnect(const char* ssid, const char* password) {
  Serial.print("\n\nConnecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);
  oldmillis = millis();
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    if (millis() - oldmillis >= 10000) {
      Serial.println("\n\nWiFi connection TIMEOUT");
      return;
    }
  }
  Serial.println("\n\nWiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

