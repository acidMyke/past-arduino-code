#include "MultiTask.h"

multiTask::multiTask(int interval){
  
}

void multiTask::run() {
  if (_prevMillis < millis()) {
    _prevMillis = millis();
  }
}
