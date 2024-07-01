void setup() {
  Serial.begin(9600);
  DDRB |= 1 << PB1;
  TCCR1A |= (1 << COM1A1);
  OCR1A = 128;
}

void loop() {
  if(Serial.available()){
    int value = Serial.parseInt();
    value = constrain(value, 0, 255);
    Serial.println(value);
    OCR1A = value;
    delay(5000);
  }
//  for(int i; i < 256; i++){
  for(int i, x = 1; i > -1; i += x){
    OCR1A = i;
    delay(5);
    if(i == 255) x *= -1;
  }
}
