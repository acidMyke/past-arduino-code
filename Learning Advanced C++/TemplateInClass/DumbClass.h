class Dumb {
  public:
    template<class Arg> static Arg add(Arg x) {
      return x;
    }

    template<class Arg, class... Args> static Arg add(Arg x, Args... rest) {
      return x + add(rest...);
    }
};
