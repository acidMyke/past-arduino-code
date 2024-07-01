template<typename L> class Lambda{
  public: 
  Lambda(L fx){
    run = fx;
  }

  L *run;
};

template <class Ret>
struct ParamFunc {
    ParamFunc();
    template <typename... Args> ParamFunc(Ret(*f)(Args...), Args... args) {
      func = Lambda<Ret(void)>([f, args...](void)->Ret{
        return (f)(args...);
      });
    }
    
    Ret run() {
      return func.run();
    }
    
    Ret operator()(){
      return run();
    }
    
  private:
    Lambda<Ret(void)> func;
};
