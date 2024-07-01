volatile int buffer[100];
volatile byte count;
byte prevCount = 0;

void setup() {
  Serial.begin(9600);
  if(PINB & 1) TCCR1B |= (1 << ICNC1);
  else TCCR1B |= (3 << ICES1);
}

void loop() {
  if(count != prevCount){
    for(;prevCount <= count; prevCount++) Serial.println(buffer[prevCount]);
  }
  if(count == 99) {
    count = 0;
    prevCount = 0;
  }
}

ISR(TIMER1_CAPT_vect){
  buffer[count++] = ICR1;
  TCCR1B ^= 1 << ICES1;
}

