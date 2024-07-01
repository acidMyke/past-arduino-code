#define IO_USERNAME    "JJyong"
#define IO_KEY         "fb0b276fcf954efd98a0bcbee26a91b6"
#define WIFI_SSID       "Yong"
#define WIFI_PASS       "yong1020"
#include "AdafruitIO_WiFi.h"
AdafruitIO_WiFi io(IO_USERNAME, IO_KEY, WIFI_SSID, WIFI_PASS);

AdafruitIO_Feed *V1 = io.feed("V1");
AdafruitIO_Feed *V2 = io.feed("V2");
AdafruitIO_Feed *V3 = io.feed("V3");
AdafruitIO_Feed *V4 = io.feed("V4");
AdafruitIO_Feed *V5 = io.feed("V5");
AdafruitIO_Feed *V6 = io.feed("V6");
AdafruitIO_Feed *V7 = io.feed("V7");
AdafruitIO_Feed *V8 = io.feed("V8");
AdafruitIO_Feed *V9 = io.feed("V9");

int IOData[9];

void setup() {
  Serial.begin(115200);
  while (!Serial);

  Serial.println("Connecting to Adafruit IO");
  io.connect();

  V1->onMessage(handleV1);
  V2->onMessage(handleV2);
  V3->onMessage(handleV3);
  V4->onMessage(handleV4);
  V5->onMessage(handleV5);
  V6->onMessage(handleV6);
  V7->onMessage(handleV7);
  V8->onMessage(handleV8);
  V9->onMessage(handleV9);

  while (io.status() < AIO_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  Serial.println("\n" + String(io.statusText()));
}

void loop() {
  io.run();
  for(int i = 0; i < 9; i++){
    Serial.println("V" + String(i + 1) + ": " + String(IOData[i]));
  }
  delay(1000);
}

void handleV1(AdafruitIO_Data *data) {
  IOData[0] = data->toInt();
}
void handleV2(AdafruitIO_Data *data) {
  IOData[1] = data->toInt();
}
void handleV3(AdafruitIO_Data *data) {
  IOData[2] = data->toInt();
}
void handleV4(AdafruitIO_Data *data) {
  IOData[3] = data->toInt();
}
void handleV5(AdafruitIO_Data *data) {
  IOData[4] = data->toInt();
}
void handleV6(AdafruitIO_Data *data) {
  IOData[5] = data->toInt();
}
void handleV7(AdafruitIO_Data *data) {
  IOData[6] = data->toInt();
}
void handleV8(AdafruitIO_Data *data) {
  IOData[7] = data->toInt();
}
void handleV9(AdafruitIO_Data *data) {
  IOData[8] = data->toInt();
}


