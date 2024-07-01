void setup() {
  Serial.begin(9600);
}

void loop() {
  println("[", millis(), "] ", "Hello world");

}

size_t println(){
  return Serial.println();
}

template <typename Arg> size_t print(Arg arg){
  return Serial.print(arg);
}

template <typename Arg, typename... Args> size_t print(Arg arg0, Arg arg1, Args... args){
  return print(arg0) + print(arg1) +print(args...);
}

template <typename... Args> size_t println(Args... args ){
  return print(args...) + println();
}

template <typename Arg, typename... Args> size_t printf(const char *format, ...){
  size_t n = print(format.substring(0, format.indexOf("%")));
  
}

