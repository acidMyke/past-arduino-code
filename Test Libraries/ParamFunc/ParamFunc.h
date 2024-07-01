#include "Lambda.h"

template <class Ret>
struct ParamFunc {
    ParamFunc();
    template <typename... Args> ParamFunc(Ret(*f)(Args...), Args... args) {
      func = [f, args...](void)->Ret{
        return (f)(args...);
      };
    }
    Ret run() {
      return func();
    }
    Ret operator()(){
      return run();
    }
  private:
    Lambda<Ret(void)> func;
};
