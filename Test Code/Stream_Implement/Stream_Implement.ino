#ifndef NUM_FUNCTION
#define NUM_FUNCTION 32
#endif

typedef void (*callBackFunction)();
typedef enum {NOTHING, OVERLOAD, KEYWORD_USED, NOT_KEYWORD, FUNCTION_FULL} error_code;

class callFunction {
  private:
    Stream* stream;
    int fxIndex = 0;
    byte keyByte[NUM_FUNCTION];
    callBackFunction fx[NUM_FUNCTION];

  public:
    void begin(const Stream&);
    void add(callBackFunction, byte);
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

    error_code error = 0;
};

void callFunction::begin(const Stream& s) {
  stream = &s;
  fxIndex = 0;
}

void callFunction::add(callBackFunction p, byte kb) {
  if (fxIndex > NUM_FUNCTION) error = OVERLOAD;
  else {
    fx[fxIndex] = p;
    keyByte[fxIndex++] = kb;
  }
}

int callFunction::run(uint32_t ms) {
  if (available()) {
    char c = peek();
    for (int i = 0; i < fxIndex; i++) {
      if (keyByte[i] == c) {
        read();
        delayMicroseconds(ms);
        fx[i]();
        break;
      }
    }
  }
}

uint64_t callFunction::getParam() {
  uint64_t param = 0;
  if (available()) {
    int count = (byte) read();
    if (available() > count)
      for (int i = 0; i < count; i++)
        param = ((param << 8) | read());
    return param;
  }
}

callFunction serialCall;

void setup() {
  Serial.begin(115200);
  serialCall.begin(Serial);
  serialCall.add(fx0, (byte)0x20);
  serialCall.add(fx1, (byte)0x21);
  //  serialCall.add(fx2, 0x22);
  Serial.print((byte)0x01);
}

void loop() {
  serialCall.run();
}

void fx0() {
  uint8_t pin = LED_BUILTIN;
  pinMode(pin, OUTPUT);
  for (int i = 0; i < 100; i++) {
    digitalWrite(pin, !digitalRead(pin));
    delay(100);
  }
};

void fx1() {
  uint8_t pin = LED_BUILTIN;
  long delayTime = serialCall.getParam();
  pinMode(pin, OUTPUT);
  for (int i = 0; i < 10; i++) {
    digitalWrite(pin, !digitalRead(pin));
    delay(delayTime);
  }
}

//int decodeInt() {
//  if (Serial.available() >= 2) {
//    return ((Serial.read() << 8) | Serial.read() << 0);
//  }
//  else if (Serial.available() == 1) {
//    return Serial.read();
//  }
//}

