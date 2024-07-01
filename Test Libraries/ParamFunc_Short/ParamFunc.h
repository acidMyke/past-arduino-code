template <typename Ret, typename... Args> class Lambda {
  public:
    template <typename T> Lambda(T const &lambda) : lambda(lambda){
    }

    template <typename T> Lambda<Ret, Args...>& operator =(T const &lambda) {
      this(lambda);
      return *this;
    }
    run();
  private:
    void *lambda;
};



template <class Ret>
class ParamFunc {
  public:
    template <typename... Args> ParamFunc(Ret(*f)(Args...), Args... args) {
      func = [f, args...](void)->Ret{
        return (f)(args...);
      };
    }
    Ret run() {
      return func();
    }

    Lambda<Ret, void> func; 
};
