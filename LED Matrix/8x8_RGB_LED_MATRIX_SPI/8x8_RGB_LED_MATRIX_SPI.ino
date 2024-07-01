#include <Arduino.h>
#include <SPI.h>

//TLC5917 pin (using SPI)
#define CLK 13
#define SDO 12
#define SDI 11
#define LE  10
#define OE  9
#define RA  5

#define color(r, c) value[((row & 7) << 3) | (col & 7)]
#define merge(r, g, b) int((red & 15) << 8) | ((green & 15) << 4 | (blue & 15)
#define seperate(r, c, rgb) (value[(r << 3) | c] & ( 15 << (rgb * 4)))
#define assign(row, col, red, green, blue) color(row, col) = merge(red, green, blue)
#define comColor(low, high) (int(high << 6) | (low & 0x3F)) & 0xFFF

volatile byte curRow = 0, PWMCounter = 0, PWMMaster; //Volatile data are use in ISR //PWMMaster = ***(Updating)(PWM)
uint16_t value[64]; //value[position] //Position = **RRRCCC //Value = RRRRGGGGBBBB
byte posIndex;

/*Note:
  Communication protocol (Most Significant Two Bit):
  00: POSITION: 00RRRCCC (Most Significant Two Bit must be LOW)
  10: DELAY: 10SSSSSS (Most Significant Bit must be HIGH while Second Significant Bit must be LOW)
  11: VALUE: LOWBYTE First then HIGHBYTE: ie 11GGBBBB then 11RRRRGG (Most Significant Two Bit must be HIGH)
*/
#ifdef useWire
#include <Wire.h>
#endif

void setup() {
  Serial.begin(9600); //Start Serial Communication
  noInterrupts(); //Disable interrupts
  //Timers (using Timer 1 only)
  TCCR1A = 0x00; //Disable OC1A/OC1B pin, and WGM11:10 for Clear Timer on Compare match (CTC) mode
  TCCR1B = 0x0B; //WGM13:12 for CTC (OCR1A as TOP), CS12:10 for prescaler of 64
  TIMSK1 = 0x02; //Trigger an interrupt on an OCR1A match
  OCR1A = 24; //Set Output Compare Registers A to be 24
  // Timer 1 Setttings: Disable OC1A & OC1B pin, Clear Timer on an OCR1A match
  // Clock is running at 16Mhz/64(prescaler) = 250kHz, which mean timer will increment every 1/250kHz = 4us.
  // With OCR1A as 24, means that interrupt will be call every (24+1)*4us = 100us, which is about 1/100us = 10kHz

  DDRB |= 1 << PB4; //Set 12(PB4) as input
  DDRB &= ~0x2F; //Set 13(PB5), 11(PB3), 10(PB2), 9(PB1), 8(PB0)

  SPI.beginTransaction(SPISettings(SPI_CLOCK_DIV2, MSBFIRST, SPI_MODE0));
  //SPI Setting: Clock 16/2 = 8Mhz, Most Significant Bit First, SPIMODE (https://tinyurl.com/y7esxv65)
  interrupts();
  //Enable interrupts

#ifdef useWire
  Wire.begin(useWire);
  Wire.onReceive(receiveEvent);
#endif
}

void loop() {
  setAll(0);
  PWMMaster = map(analogRead(A0), 0, 1023, 0, 15); //Convert analogRead => 10 bit to 4 bit PWM
#ifdef useSerial
  while (Serial.available())
    switch ((Serial.peek() & 0xC0) >> 6) {
      case 0: posIndex = (Serial.read() & 0x3F);
      case 2: delay((Serial.read() & 0x3F) * 78);
      case 3: if(Serial.available() > 1) value[posIndex++] = comColor(Serial.read(), Serial.read());
    }
#endif
}

#ifdef useWire
void receiveEvent(int numBytes){
  while (Wire.available()){
    switch ((Wire.peek() & 0xC0) >> 6) {
      case 0: posIndex = (Wire.read() & 0x3F);
      case 2: delay((Wire.read() & 0x3F) * 78);
      case 3: if(Wire.available() > 1) value[posIndex++] = comColor(Wire.read(), Wire.read());
    }
  }
}
#endif

ISR(TIMER1_COMPA_vect) {
  if (PWMMaster & 0x10) return;
  volatile byte data[3] = {0, 0, 0};
  if (PWMCounter < (PWMMaster & 0xF)) {
    for (int rgb = 2; rgb > -1; rgb--)
      for (int col = 7; col > -1; col--)
        bitWrite(data[rgb], col, seperate(curRow, col, rgb) > PWMCounter);
  }
  SPI.transfer(data, 3); //Send out data

  PORTB |= 1 << PB1; //Set OE to HIGH //Turn OFF LED
  PORTB |= 1 << PB2; //Set LE to HIGH //Latch Enable
  PORTD = (PORTD & ~(7 << RA)) | ((curRow & 7) << RA); //Set the row
  PORTB &= ~(1 << PB2); //Set LE to LOW //Latch Disable
  PORTB &= ~(1 << PB1); //Set OE to LOW //Turn ON LED

  curRow++;
  if (curRow > 7) {
    PWMCounter++;
    curRow = 0;
  }
  if (PWMCounter > 15) PWMCounter = 0;
}

void testLed() {
  byte data[2] = {0x1D, 0x08};
  for (int i; i < 4; i++) {
    digitalWrite(OE, bitRead(data[0], i));
    digitalWrite(LE, bitRead(data[1], i));
    digitalWrite(CLK, HIGH);
    digitalWrite(CLK, LOW);
  }
  digitalWrite(OE, HIGH);

  for (int r; r < 8; r++) {
    PORTD = (PORTD & 0x1F) | ((r << RA) & 0xE0); //Set the row
    digitalWrite(OE, LOW);
    for (int clk; clk < 8; clk++) digitalWrite(CLK, !digitalRead(CLK)); // Four CLK
    digitalWrite(OE, HIGH);
    PORTB |= 1 << PB1; //Set OE to HIGH
    for (int reg; reg < 3; reg++)
      Serial.print("Row " + String(r) + ":" + String(SPI.transfer(0x00), BIN) + (reg == 2 ? "\r\n" : "\t"));
  }

  data[1] = 0x00;
  for (int i; i < 4; i++) {
    digitalWrite(OE, bitRead(data[0], i));
    digitalWrite(LE, bitRead(data[1], i));
    digitalWrite(CLK, HIGH);
    digitalWrite(CLK, LOW);
  }
}
