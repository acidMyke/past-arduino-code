#include "AdafruitIO_WiFi.h"

//Go to https://io.adfruit.com/

#define IO_USERNAME    "JJyong"
#define IO_KEY         "3f68dc6396f3466c8697fc74295d5be3"

#define WIFI_SSID      "Yong"
#define WIFI_PASS      "yong1020"

AdafruitIO_WiFi io(IO_USERNAME, IO_KEY, WIFI_SSID, WIFI_PASS);

AdafruitIO_Dashboard *dashboard = io.dashboard("Test2");

AdafruitIO_Feed *digital_feed = io.feed("digital");

AdafruitIO_Feed *analog_feed = io.feed("analog");

#define LED_PIN LED_BUILTIN
#define PHOTOCELL_PIN A0

int current = 0;
int last = -1;

void setup() {
  Serial.begin(115200);

  while (!Serial);

  Serial.println();
  Serial.println("Connecting to Adafruit IO");
  io.connect();

  digital_feed->onMessage(handleMessage);

  while (io.status() < AIO_CONNECTED) {
    Serial.print(".");
    delay(10);
  }

  Serial.println();
  Serial.println(io.statusText());

  if (digital_feed->exists()) {
    Serial.println("Digital Feed Exist");
  } else {
    Serial.println("Creating Digital Feed");
    Serial.println("...");
    if (digital_feed->create()) {
      Serial.println("Digital Feed Created");
    } else {
      Serial.println("Digital Feed Creation Failed");
    }
  }

  if (analog_feed->exists()) {
    Serial.println("Analog Feed Exist");
  } else {
    Serial.println("Creating Analog Feed");
    Serial.println("...");
    if (analog_feed->create()) {
      Serial.println("Analog Feed Created");
    } else {
      Serial.println("Analog Feed Creation Failed");
    }
  }

  if (dashboard->exists()) {
    Serial.println("Test2 dashboard exists.");
  } else {
    Serial.println("Creating Test2 Dashboard");
    Serial.println("...");
    if (dashboard->create()) {
      Serial.println("Test2 dashboard Created");
      addBlocks();
    } else {
      Serial.println("Test2 dashboard Creation Failed");
    }
  }
}

void loop() {
  io.run();

  current = analogRead(PHOTOCELL_PIN);
  current = map(0, 1024, 1024, 0, current); 

  if (current == last) {
    return;
  }

  Serial.print("sending->");
  Serial.println(current);
  analog_feed->save(current);

  last = current;

  delay(100);

}

void handleMessage(AdafruitIO_Data *data) {
  Serial.print("received <- ");

  if (data->toPinLevel() == HIGH)
    Serial.println("HIGH");
  else
    Serial.println("LOW");

  // write the current state to the led
  digitalWrite(LED_PIN, !data->toPinLevel());
}
void addBlocks() {

  bool added = false;
  
  Serial.print("Adding toggle button block... ");
  ToggleBlock *toggle = dashboard->addToggleBlock(digital_feed);
  toggle->onText = "1";
  toggle->offText = "0";
  added = toggle->save();
  Serial.println(added ? "added" : "failed");

  Serial.print("Adding gauge block... ");
  GaugeBlock *gauge = dashboard->addGaugeBlock(analog_feed);
  gauge->min = 0;
  gauge->max = 1024;
  gauge->ringWidth = "thin"; // thin or thick
  gauge->label = "";
  added = gauge->save();
  Serial.println(added ? "added" : "failed");
  
}

