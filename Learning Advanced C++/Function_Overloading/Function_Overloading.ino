char inital = 'A';

void setup() {
  Serial.begin(9600);
  delay(100);
  Serial.println(inital);
  change(inital);
  Serial.println(inital);
}

void loop() {
  // put your main code here, to run repeatedly:

}

int change(uint8_t& i){
  i = 8;
}

int change(uint16_t& i){
  i = 500;
}

int change(uint32_t& i){
  i = 700000L;
}

int change(int8_t& i){
  i = -5;
}

int change(int16_t& i){
  i = -29890;
}

int change(int32_t& i){
  i = 5;
}

int change(char& i){
  i = 'H';
}

int change(double& i){
  i = -2.7182818284590452353602874713527;
}

int change(String& str){
  str = "Hello Internet";
}

