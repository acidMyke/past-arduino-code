#ifndef MultiTask_h
#define MultiTask_h

class multiTask {
  public:
  multiTask(int interval);
  void run();
  private:
  uint32_t _previousMillis;
};

#endif
