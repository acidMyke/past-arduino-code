#include <ESP8266WiFi.h> 
#define NUM_FUNCTION 16
#define led LED_BUILTIN

typedef byte (*callBackFunction)(void);

callBackFunction fx[NUM_FUNCTION];

byte keyword[NUM_FUNCTION];
int fxIndex = -1;

void setup() {
  Serial.begin(115200);
}

void loop() {
  
}

int addFunction(callBackFunction p, byte kw) {
  if (++fxIndex > NUM_FUNCTION)
    return -1;
  else {
    for (int i = 0; i < fxIndex; i++)
      if (keyword[i] == kw)
        return -2;
    fx[fxIndex] = p;
    keyword[fxIndex] = kw;
  }
}

WiFiClient runFunction(WiFiClient c) {
  if(c.available()){
    for(int i = 0; i <= fxIndex; i++){
      if(keyword[i] == Serial.peek()){
        fx[i]();
      }
    }
  }
  return c;
}

