

void setup() {
  Serial.begin(9600);
//  ParamFunc<String> HW = ParamFunc<String>(addWorld, String("Hello"));
//  
//  Serial.println(HW.run());
}

void loop() {
  
}

String addWorld(String str){
  return str + " world";
}



