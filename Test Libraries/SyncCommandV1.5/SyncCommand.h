#include "Arduino.h"

#ifndef SYNC_COMMAND_H
#define SYNC_COMMAND_H

#ifndef BUFFER_SIZE
#define BUFFER_SIZE 512
#endif

#ifndef NUM_FUNCTION
#define NUM_FUNCTION 32
#endif

#if !defined(FUNCTION_START) || !defined(STRING_START) || !defined(BYTE_START) || !defined(END)
#error FUNCTION_START or STRING_START or BYTE_START or END is not define. Please define it before #include "SyncCommand.h"
#endif

typedef void (*callBackFunction)();
typedef enum {NOTHING, KEYWORD_USED, NOT_KEYWORD, FUNCTION_FULL} error_code;

class SyncCommand {
  private:
    Stream* stream;
    Stream* debugStream;
    int fxIndex = 0;
    byte keyByte[NUM_FUNCTION];
    callBackFunction fx[NUM_FUNCTION];
    byte dataType;
    String StringBuffer;
    uint32_t timing;
    size_t debug(String);

  public:
    void begin(Stream&);
    void begin(Stream&, Stream&);
    void addDebugStream(Stream&);
    int addFunction(callBackFunction, byte);
    int run();
    
    int available() {
      return stream->available();
    }

    int read() {
      return stream->read();
    }

    int peek() {
      return stream->peek();
    }

    void flush() {
      for (int i = 0; i < available(); i++)
        read();
    }

    String getErrorString() {
      switch (error) {
        case KEYWORD_USED: return "KEYWORD_USED";
        case FUNCTION_FULL: return "FUNCTION_FULL";
      }
    }

    byte getByte() {
      return (byte)read();
    }
    char getChar() {
      return (char)read();
    }
    unsigned int getUInt() {
      return (uint16_t)((read() << 8 ) | (read()));
    }
    int getInt() {
      return (int)((read() << 8 ) | (read()));
    }
    unsigned long getULong() {
      return (uint32_t)(((long)read() << 24 ) | ((long)read() << 16 ) | ((long)read() << 8 ) | ((long)read()));
    }
    long getLong() {
      return (int32_t)(((long)read() << 24 ) | ((long)read() << 16 ) | ((long)read() << 8 ) | ((long)read()));
    }
    uint64_t get(int count) {
      uint64_t num;
      for (int i = 0; i < count; i++)
        num = (num << 8) | (uint64_t)read();
    }
    String getString(){
      return StringBuffer;
    }

    error_code error = NOTHING;
};

#endif

void SyncCommand::begin(Stream& s) {
  stream = &s;
  fxIndex = 0;
  StringBuffer.reserve(END);
}

void SyncCommand::begin(Stream& s, Stream& d) {
  stream = &s;
  fxIndex = 0;
  StringBuffer.reserve(END);
  addDebugStream(d);
}

void SyncCommand::addDebugStream(Stream& d) {
  debugStream = &d;
  delay(10);
  debug("Sync Command Debug Stream Begin\n");
}

inline size_t SyncCommand::debug(String str) {
  return (debugStream->print("[" + String(millis()) + "] ") + debugStream->print(str));
}

int SyncCommand::addFunction(callBackFunction p, byte kb) {
  if (fxIndex > NUM_FUNCTION) {
    error = FUNCTION_FULL;
    return -1;
  }
  else {
    for (int i = 0; i < fxIndex; i++)
      if (keyByte[i] == kb) {
        error = KEYWORD_USED;
        return -1;
      }
    fx[fxIndex] = p;
    keyByte[fxIndex++] = kb;
  }
}

int SyncCommand::run() {
  if (!available()) return -1;
  timing = millis();

  byte b = peek();
  if ((b == FUNCTION_START) || (b == STRING_START) || (b == BYTE_START))
    read();

  if (b == FUNCTION_START) {
    debug("FUNCTION_START is detected");
    byte c = peek();
    for (int i = 0; i < fxIndex; i++) {
      if (keyByte[i] == c) {
        read();
        fx[i]();
        dataType = FUNCTION_START;
        return keyByte[i];
      }
    }
  }
  else if (b == STRING_START) {
    debug("STRING_START is detected");
    StringBuffer = stream->readStringUntil((char)END);
    dataType = STRING_START;
    return STRING_START;
  }

  else if (b == BYTE_START) {
    debug("BYTE_START is detected");
    dataType = BYTE_START;
    return BYTE_START;
  }

  else {
    debug("Available but not keyword: FUNCTION_START or STRING_START or BYTE_START is not detected");
    dataType = 0;
    return -1;
  }
}



