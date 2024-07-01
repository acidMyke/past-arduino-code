char en[][10][14] = {
  {"zero","one","two","three","four","five","six","seven","eight","nine"},
  {"ten","eleven","twelve","thirdteen","fourteen","fifteen","sixteen","seventeen","eighteen","nineteen"},
  {"twenty","twenty-one","twenty-two","twenty-three","twenty-four","twenty-five","twenty-six","twenty-seven","twenty-eight","twenty-nine"},
  {"thirdty","thirdty-one","thirdty-two","thirdty-three","thirdty-four","thirdty-five","thirdty-six","thirdty-seven","thirdty-eight","thirdty-nine"},
  {"fourty","fourty-one","fourty-two","fourty-three","fourty-four","fourty-five","fourty-six","fourty-seven","fourty-eight","fourty-nine"},
  {"fifty","fifty-one","fifty-two","fifty-three","fifty-four","fifty-five","fifty-six","fifty-seven","fifty-eight","fifty-nine"},
  {"sixty","sixty-one","sixty-two","sixty-three","sixty-four","sixty-five","sixty-six","sixty-seven","sixty-eight","sixty-nine"},
  {"seventy","seventy-one","seventy-two","seventy-three","seventy-four","seventy-five","seventy-six","seventy-seven","seventy-eight","seventy-nine"},
  {"eighty","eighty-one","eighty-two","eighty-three","eighty-four","eighty-five","eighty-six","eighty-seven","eighty-eight","eighty-nine"},
  {"ninety","ninety-one","ninety-two","ninety-three","ninety-four","ninety-five","ninety-six","ninety-seven","ninety-eight","ninety-nine"}
};

void setup(){
  Serial.begin(115200);
  for(int a = 0; a < 10; a++){
    for(int b = 0; b < 10; b++){
      Serial.printf("%s \t\t\t", en[a][b]);
      delay(100);
    }
    Serial.println("");
  }
}

void loop(){
  
}

