template<typename L> class Lambda{
  public: 
  Lambda(L fx){
    run = fx;
  }

  L *run;
};
