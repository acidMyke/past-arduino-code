#ifndef multiPress_h
#define multiPress_h

#define LONGPRESS 128

#include <Arduino.h>

class multiPress{
  public:
    bool begin(uint8_t pin, uint8_t maxCount = 10, uint32_t timeout = 5000);
    uint16_t count(uint8_t useLongPress = 0);
  private:
    static uint8_t pressCount;
    static uint8_t _pin, _maxCount;
    static uint32_t _timeout, pressTime;
    static void countPress();
};

#endif
