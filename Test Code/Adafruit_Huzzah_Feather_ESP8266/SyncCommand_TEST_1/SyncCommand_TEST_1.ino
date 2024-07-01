#include <ESP8266WiFi.h>
#include "Arduino.h"

#ifndef SYNC_COMMAND_H
#define SYNC_COMMAND_H

#ifndef NUM_FUNCTION
#define NUM_FUNCTION 32
#endif

typedef void (*callBackFunction)();
typedef enum {NOTHING, KEYWORD_USED, FUNCTION_FULL} error_code;

class SyncCommand {
  private:
    Stream* stream;
    int fxIndex = 0;
    byte keyByte[NUM_FUNCTION];
    callBackFunction fx[NUM_FUNCTION];

  public:
    void begin(Stream&);
    int add(callBackFunction, byte);
    int run(uint32_t = 10000);
    uint64_t getParam();

    int available() {
      return stream->available();
    }

    int read() {
      return stream->read();
    }

    int peek() {
      return stream->peek();
    }

    void flush(){
      for(int i = 0; i < available(); i++)
        read();
    }

    String getErrorString(){
      switch (error){
        case KEYWORD_USED: return "KEYWORD_USED";
        case FUNCTION_FULL: return "FUNCTION_FULL";
      }
    }

    error_code error = NOTHING;
};

#endif

void SyncCommand::begin(Stream& s) {
  stream = &s;
  fxIndex = 0;
}

int SyncCommand::add(callBackFunction p, byte kb) {
  if (fxIndex > NUM_FUNCTION){
    error = FUNCTION_FULL;
    return -1;
  }
  else {
    for (int i = 0; i < fxIndex; i++)
      if (keyByte[i] == kb){
        error = KEYWORD_USED;
        return -1;
      }
    fx[fxIndex] = p;
    keyByte[fxIndex++] = kb;
  }
}

int SyncCommand::run(uint32_t ms) {
  if (available()) {
    char c = peek();
    for (int i = 0; i < fxIndex; i++) {
      if (keyByte[i] == c) {
        read();
        delayMicroseconds(ms);
        fx[i]();
        return i;
      }
    }
    return -2;
  }
  return -1;
}

uint64_t SyncCommand::getParam() {
  uint64_t param = 0;
  if (available()) {
    int count = (byte) read();
    if (available() > count)
      for (int i = 0; i < count; i++)
        param = ((param << 8) | read());
    return param;
  }
  else return 0;
}

IPAddress host = IPAddress(192, 168, 1, 155);

const int httpPort = 8080;

const char* ssid = "JJ Phone";
const char* pass = "12272000";

WiFiClient client;

SyncCommand stringCall;

void fx0(void);
void fx1(void);

void setup() {
  Serial.begin(115200);
  delay(100);

  stringCall.begin(client);
  delay(100);
  stringCall.add(fx0, 'a');
  stringCall.add(fx1, 'b');

  if(stringCall.error != NOTHING)
    Serial.println(stringCall.getErrorString());

  pinMode(LED_BUILTIN, OUTPUT);

  Serial.println("Connecting to Yong");
  WiFi.mode(WIFI_STA);
  WiFi.begin("Yong", "yong1020");

  while (WiFi.status() != WL_CONNECTED)  delay(500);

  Serial.println("WiFi Connected\nIP address: " + WiFi.localIP().toString());
}

void loop() {
  if(!client) {
    Serial.print("Connecting to host\n");
    if (!client.connect(host, httpPort)) {
      if (WiFi.status() != WL_CONNECTED) {
        Serial.print("Network Disconnected\n");
        setup();
      }
      return;
    }
  }
  
  client.print("2");

  uint64_t timeout = millis() + 5000;
  while (!client.available() && timeout > millis()) delay(10);
  if (timeout < millis()) {
    Serial.print("Connection Timeout\n");
    client.stop();
    return;
  }
  else if (client.available()) {
    if(stringCall.run() == -2); 
      Serial.print("No Match: " + String((char)client.read()) + "\n");
    client.println();
  }
  else
    Serial.print("Unidentified ERROR\n");
  
//  
//  if(stringCall.run() == -2)
//    Serial.println("No Match: " + String((char)Serial.read()));
}

void fx0() {
  Serial.println("Match: a fx0 activated");
}

void fx1() {
  Serial.println("Match: b fx1 activated");
}

