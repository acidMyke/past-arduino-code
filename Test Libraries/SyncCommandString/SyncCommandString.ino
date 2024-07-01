#include "Arduino.h"

typedef void (*callBackFunction)();
typedef enum {NOTHING, KEYWORD_USED, FUNCTION_FULL} error_code;

#ifndef NUM_FUNCTION
#define NUM_FUNCTION 32
#endif

class SyncCommandString {
  private:
    Stream* stream;
    int fxIndex = 0;
    String keyString[NUM_FUNCTION];
    callBackFunction fx[NUM_FUNCTION];

  public:
    void begin(Stream&);
    int add(callBackFunction, String);
    int run(uint32_t = 10000);

    int available() {
      return stream->available();
    }

    int read() {
      return stream->read();
    }

    int peek() {
      return stream->peek();
    }

    String readString() {
      return stream->readString();
    }

    long getInt() {
      return getLong();
    }

    long getLong() {
      return stream->parseInt();
    }

    float getFloat() {
      return stream->parseFloat();
    }

    String getErrorString() {
      switch (error) {
        case KEYWORD_USED: return "KEYWORD_USED";
        case FUNCTION_FULL: return "FUNCTION_FULL";
      }
    }

    error_code error = NOTHING;

    void Debug(String s) {
      Serial.println("[" + String(millis()) + "]" + s);
    }

    int match(String s0, String s1) {
      s0.toLowerCase();
      s1.toLowerCase();
      int length = s0.length();
      if (length > s1.length()) length = s1.length();

      int num = 0;
      for (int l = 0; l < length; l++) {
        if (s0.charAt(l) == s1.charAt(l)) {
          num++;
        }
        else {
          break;
        }
      }
      return num;
    }
};

void SyncCommandString::begin(Stream& s) {
  stream = &s;
  fxIndex = 0;
}

int SyncCommandString::add(callBackFunction p, String key) {
  if (fxIndex > NUM_FUNCTION) {
    error = FUNCTION_FULL;
    return -1;
  }
  if(!key.endsWith("\r")) key += "\r";
  Serial.println("Key: " + key);
  for (int i = 0; i < fxIndex; i++) {
    if (key.equalsIgnoreCase(keyString[i])) {
      error = KEYWORD_USED;
      return -1;
    }
  }
  fx[fxIndex] = p;
  keyString[fxIndex] = key;
  Serial.println("Index: " + String(fxIndex++));
}

int SyncCommandString::run(uint32_t ms) {
  if (!available()) return -1;
  String input;
  for (int i = 0; i < fxIndex; i++) {
    if (peek() == keyString[i].charAt(0)) {
      delayMicroseconds(ms);
      input = stream->readStringUntil('\r') + "\r";
      break;
    }
  }
  if (input == NULL) return -2;
  if (input.indexOf("(") != -1){
    
  }
  int max, function;
  for (int i = 0; i < fxIndex; i++) {
    int matches = match(input, keyString[i]);
    Serial.println("Matching " + input + " to " + keyString[i] + ": " + String(matches));
    if(matches > max){
      function = i;
      max = matches;
    }
  }
  fx[function]();
}

SyncCommandString Call;

void fx0();
void fx1();

void setup() {
  Serial.begin(115200);
  delay(100);
  Call.begin(Serial);
  Call.add(fx0, "delay");
  Call.add(fx1, "delayMicroseconds");
  Call.add(fx2, "pinMode");
  Call.add(fx3, "digitalWrite");
  Call.add(fx4, "digitalRead");

  if(Call.error != NOTHING) {
    Serial.println("Error: " + Call.getErrorString());
  }
}

void loop() {
  //Serial.println(millis());
  if (!Call.run()) {
    Serial.println("Err" + String(Serial.read()));
  }
}

void fx0() {
  Serial.println("delay");
}

void fx1() {
  Serial.println("delayMicroseconds");
}

void fx2(){ 
  Serial.println("pinMode");
}

void fx3() {
  Serial.println("digitalWrite");
}

void fx4() {
  Serial.println("digitalRead"); 
}

