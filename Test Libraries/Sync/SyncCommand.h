#include "Arduino.h"

#ifndef SYNC_COMMAND_H
#define SYNC_COMMAND_H

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
    String (*onByteRec)(void);
    String (*onStrRec)(String);
    size_t debug(String);

  public:
    void begin(Stream&);
    void begin(Stream&, Stream&);
    void addDebugStream(Stream&);
    void onByteReceived(String(*)(void));
    void onStringReceived(String(*)(String));
    int addFunction(callBackFunction, byte);
    int available();
    //    int peek();
    //    int read();

    byte getByte();
    char getChar();
    unsigned int getUInt();
    int getInt();
    unsigned long getULong();
    long getLong();
    String getString();

    int run(uint32_t = 5000);

    error_code error = NOTHING;
};

#endif

size_t SyncCommand::debug(String str) {
  if (!debugStream) return 0;
  return (debugStream->print("[" + String(millis()) + "] ") + debugStream->print(str));
}

void SyncCommand::begin(Stream& s) {
  stream = &s;
  fxIndex = 0;
}


void SyncCommand::begin(Stream& s, Stream& d) {
  stream = &s;
  fxIndex = 0;
  addDebugStream(d);
}

void SyncCommand::addDebugStream(Stream& d) {
  debugStream = &d;
  debug("Debug Stream Added\n");
}

void SyncCommand::onByteReceived(String (*f)(void)) {
  onByteRec = f;
}

void SyncCommand::onStringReceived(String (*f)(String)) {
  onStrRec = f;
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

int SyncCommand::available() {
  return stream->available();
}

//Data processing
byte SyncCommand::getByte() {
  if (available() < 1) return 0;
  return (byte)stream->read();
}

char SyncCommand::getChar() {
  if (available() < 1) return 0;
  return (char)stream->read();
}

unsigned int SyncCommand::getUInt() {
  if (available() < 2) return 0;
  return ((unsigned int)stream->read() | (unsigned int)stream->read() << 8);
}

int SyncCommand::getInt() {
  if (available() < 2) return 0;
  return ((int)stream->read() | (int)stream->read() << 8);
}

unsigned long SyncCommand::getULong() {
  if (available() < 4) return 0;
  return ((unsigned long)stream->read() | (unsigned long)stream->read() << 8 | (unsigned long)stream->read() << 16 | (unsigned long)stream->read() << 24);
}

long SyncCommand::getLong() {
  if (available() < 4) return 0;
  return ((long)stream->read() | (long)stream->read() << 8 | (long)stream->read() << 16 | (long)stream->read() << 24);
}

int SyncCommand::run(uint32_t timeout) {
  uint32_t time = millis() + timeout;
  while (stream->available() == 0 && millis() < time) delay(200);
  if (!stream->available()) return -1;

  byte b = stream->peek();
  if ((b != FUNCTION_START) && (b != STRING_START) && (b != BYTE_START))
    return -2;

  stream->read();
  if (b == FUNCTION_START) {                //Excute Function
    debug("FUNCTION_START is detected\n");
    byte c = stream->peek();
    for (int i = 0; i < fxIndex; i++) {
      if (keyByte[i] == c) {
        stream->read();
        fx[i]();
        return keyByte[i];
      }
    }
  }

  else if (b == BYTE_START) {
    debug("BYTE_START is detected\n");
    delay(1000);
    stream->println(onByteRec());
  }

  else if (b == STRING_START) {
    debug("STRING_START is detected\n");
    stream->println(onStrRec(stream->readString()));
  }

  else {
    debug("Available but not keyword: FUNCTION_START or STRING_START or BYTE_START is not detected\n");
    return -1;
  }
}


