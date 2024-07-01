#include <Arduino.h>

#define CLK PD7
#define SDI PD6
#define LE PD5
#define OE PD4

#define color(row, col) value[((row & 7) << 3) | (col & 7)]
#define merge(red, green, blue) int((red & 15) << 8) | ((green & 15) << 4 | (blue & 15)
#define seperate(row, col, rgb) (value[((row & 7) << 3) | (col & 7)] & ( 15 << (rgb * 4)))
#define assign(row, col, red, green, blue) color(row, col) = merge(red, green, blue)
#define comColor(low, high) (int(high << 6) | (low & 0x3F)) & 0xFFF

volatile byte curRow = 0, PWMCounter = 0, PWMMaster; //Volatile data are use in ISR //PWMMaster = ***(Updating)(PWM)
uint16_t value[64]; //value[position] //Position = **RRRCCC //Value = RRRRGGGGBBBB

const int brightnessPot = A0;

void setup() {
  Serial.begin(9600);
  noInterrupts();
  //Timers (using Timer 1 only)
  TCCR1A = 0x00; //Disable OC1A/OC1B pin, and WGM11:10 for Clear Timer on Compare match (CTC) mode
  TCCR1B = 0x0B; //WGM13:12 for CTC (OCR1A as TOP), CS12:10 for prescaler of 64
  TIMSK1 = 0x02; //Trigger an interrupt on an OCR1A match
  OCR1A = 24; //Set Output Compare Registers A to be 24
  // Timer 1 Setttings: Disable OC1A & OC1B pin, Clear Timer on an OCR1A match
  // Clock is running at 16Mhz/64(prescaler) = 250kHz, which mean timer will increment every 1/250kHz = 4us.
  // With OCR1A as 24, means that interrupt will be call every (24+1)*4us = 100us, which is about 1/100us = 10kHz
  // I/O-Port Congfig
  DDRD |= 0xF << OE;

  interrupts();
}

void loop() {
  PWMMaster = analogRead(brightnessPot) / 64;
  //wipe();
}

ISR(TIMER1_COMPA_vect) {
  for (int rgb = 2; rgb > -1; rgb--)
    for (int col = 7; col > -1; col--) {
      if (PWMCounter < (PWMMaster & 0xF) && PWMCounter < seperate(curRow, col, rgb)) PORTD |= 1 << SDI;
      else PORTD &= ~(1 << SDI);
      PORTD |= 1 << CLK;
      PORTD &= ~(1 << CLK);
    }
    
  for (int bit = 7; bit > -1; bit++) {
    if(bit == curRow) PORTD |= 1 << SDI;
    else PORTD &= ~(1 << SDI);
    PORTD |= 1 << CLK;
    PORTD &= ~(1 << CLK);
  }
  
  PORTD |= 1 << OE; //Set OE to HIGH //Turn OFF LED
  PORTD |= 1 << LE; //Set LE to HIGH //Latch Enable
  PORTD &= ~(1 << LE); //Set LE to LOW //Latch Disable
  PORTD &= ~(1 << OE); //Set OE to LOW //Turn ON LED

  if (++curRow > 8) {
    PWMCounter++;
    curRow = 0;
  }
  if (PWMCounter > 15) PWMCounter = 0;
}
