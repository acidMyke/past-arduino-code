#include "Arduino.h"

#ifndef SYNC_COMMAND_H
#define SYNC_COMMAND_H

#ifndef NUM_FUNCTION
#define NUM_FUNCTION 32
#endif

typedef String (*callBackFunction)(void);

class SyncCommand {
  private:
    Stream* stream;
    Print* debugStream;
    int fxIndex = 0;
    byte keyByte[NUM_FUNCTION];
    callBackFunction fx[NUM_FUNCTION];
    size_t debug(String);
  public:
    void begin(Stream&);
    void begin(Stream&, Print&);
    void addDebugStream(Print&);
    int addFunction(byte, callBackFunction);

    int available();
    byte getByte();
    char getChar();
    unsigned int getUInt();
    int getInt();
    unsigned long getULong();
    long getLong();
    String getString(byte = 0);

    int run(uint32_t = 2000);
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

void SyncCommand::begin(Stream& s, Print& d) {
  stream = &s;
  fxIndex = 0;
  addDebugStream(d);
}

void SyncCommand::addDebugStream(Print& d) {
  debugStream = &d;
  debug("Debug Stream Added\n");
}

int SyncCommand::addFunction(byte kb, callBackFunction p) {
  if (fxIndex > NUM_FUNCTION) {
    return -1;
  }
  else {
    for (int i = 0; i < fxIndex; i++)
      if (keyByte[i] == kb) {
        return -1;
      }
    fx[fxIndex] = p;
    keyByte[fxIndex] = kb;
    debug("Function added at index of " + String(fxIndex++) + " with keyByte: 0x" + String(kb, HEX) + "\r\n");
  }
}

//Data Processing
int SyncCommand::available() {
  return stream->available();
}

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

String SyncCommand::getString(byte terminator) {
  String str;
  while (available()) {
    if(stream->peek() == terminator){
      stream->read();
      break;
    }
    str += (char)stream->read();
  }
  return str;
}

int SyncCommand::run(uint32_t timeout) {
  uint32_t time = millis() + timeout;
  while (!stream->available() && millis() < time);
  if (!stream->available()) return -1;

  byte c = stream->peek();
  debug("Byte recevied: 0x" + String(c, HEX) + "\r\n");
  for (int i = 0; i < fxIndex; i++) {
    if (keyByte[i] == c) {
      stream->read();
      delay(500);
      stream->print(fx[i]());
      return keyByte[i];
    }
  }
  debug("Byte available but not a keyByte!\r\n");
  return stream->read();
}
