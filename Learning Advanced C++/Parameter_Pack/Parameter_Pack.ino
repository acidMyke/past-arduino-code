void setup() {
  Serial.begin(9600);
  Serial.println(sum(1, 2, 3, 4, 5, 6, 7));
}

void loop() {
  
}

template <typename T> double sum(T t) {
  return t;
}

template <typename T, typename... Rest> double sum(T t, Rest... rest) {
  return t + sum(rest...);
}
