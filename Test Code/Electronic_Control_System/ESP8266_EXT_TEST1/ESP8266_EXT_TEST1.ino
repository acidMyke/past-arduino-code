#include <SoftwareSerial.h>

SoftwareSerial ESP(2, 3);

String SSID = "SSID";
String PASS = "PASS";

String reply;

void setup() {
  Serial.begin(115200);
  ESP.begin(9600);
  while (!Serial || !ESP)delay(1);
  reply.reserve(5000);
  ESP_Setup();
}

void loop() {
  
}
