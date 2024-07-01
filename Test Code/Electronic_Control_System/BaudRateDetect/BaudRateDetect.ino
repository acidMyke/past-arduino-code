#include <SoftwareSerial.h>

SoftwareSerial SoftSerial (2, 3);

uint32_t baudRate[] = {9600, 57600, 115200, 230400, 460800};
uint32_t presetBaudRate = 0;

void setup() {
  Serial.begin(115200);
  while (!Serial) delay(1);
  Serial.println("Testing Serial Baud Rates");
  for (int i = 0; i  < (sizeof(baudRate) / sizeof(uint32_t)); i++) {
    SoftSerial.begin(baudRate[i]);
    Serial.println("Testing baud rate:" + String(baudRate[i]));
    while (!SoftSerial) delay(1);
    SoftSerial.println("AT");
    int start = millis() + 20000;
    while (SoftSerial.available() < 1 && start > millis()) delay(1);
    if (SoftSerial.available() > 0) {
      if (SoftSerial.find("OK")) {
        Serial.println(String(baudRate[i]) + " is working");
        presetBaudRate = baudRate[i];
        break;
      }
      else Serial.println(String(baudRate[i]) + " not working");
    }
    else Serial.println(String(baudRate[i]) + " not working");
    SoftSerial.end();
  }
  if (presetBaudRate) {
    SoftSerial.begin(presetBaudRate);
    SoftSerial.println("AT+UART?");
    while (SoftSerial.available() < 1) delay(1);
    if (Serial.available() > 0)Serial.println(SoftSerial.readString());
  }
  else Serial.println("The Test Failed\n\nCheck the connection\n\nCheck the available Baud Rate\n");
}

void loop() {
  if (presetBaudRate) {
    if (SoftSerial.available()) Serial.write(SoftSerial.read());
    if (Serial.available()) SoftSerial.write(Serial.read());
  }
}
