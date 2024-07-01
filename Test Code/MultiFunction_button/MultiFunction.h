#ifndef MultiFunction_h
#define MultiFunction_h

#include "Arduino.h"

class MultiFunction
{
  public:
    unsigned long oldMicros[5];
    void begin(int pin, int interval = 5000, int state = HIGH, int mode = INPUT_PULLUP);
    int get();
    void buttonDec();

  private:
    int _interval;
};

#endif

