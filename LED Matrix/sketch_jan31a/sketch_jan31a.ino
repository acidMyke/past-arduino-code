int x[] = {13, 12, 11};
int y[] = {9, 8, 7, 6, 5, 4, 3, 2};
int xEn = 10;

char i = 32;

unsigned long delayTime = 100;
unsigned long delayMicro = 0;

byte data[8];

const unsigned char CH[][7] = {  // Data store as no of column (max 5), no of row, column data 1, column data 2, column data 3, column data 4, column data 5
  {3, 8, B00000000, B00000000, B00000000, B00000000, B00000000}, // space
  {1, 8, B01011111, B00000000, B00000000, B00000000, B00000000}, // !
  {3, 8, B00000011, B00000000, B00000011, B00000000, B00000000}, // "
  {5, 8, B00010100, B00111110, B00010100, B00111110, B00010100}, // #
  {4, 8, B00100100, B01101010, B00101011, B00010010, B00000000}, // $
  {5, 8, B01100011, B00010011, B00001000, B01100100, B01100011}, // %
  {5, 8, B00110110, B01001001, B01010110, B00100000, B01010000}, // &
  {1, 8, B00000011, B00000000, B00000000, B00000000, B00000000}, // '
  {3, 8, B00011100, B00100010, B01000001, B00000000, B00000000}, // (
  {3, 8, B01000001, B00100010, B00011100, B00000000, B00000000}, // )
  {5, 8, B00101000, B00011000, B00001110, B00011000, B00101000}, // *
  {5, 8, B00001000, B00001000, B00111110, B00001000, B00001000}, // +
  {2, 8, B10110000, B01110000, B00000000, B00000000, B00000000}, // ,
  {4, 8, B00001000, B00001000, B00001000, B00001000, B00000000}, // -
  {2, 8, B01100000, B01100000, B00000000, B00000000, B00000000}, // .
  {4, 8, B01100000, B00011000, B00000110, B00000001, B00000000}, // /
  {4, 8, B00111110, B01000001, B01000001, B00111110, B00000000}, // 0
  {3, 8, B01000010, B01111111, B01000000, B00000000, B00000000}, // 1
  {4, 8, B01100010, B01010001, B01001001, B01000110, B00000000}, // 2
  {4, 8, B00100010, B01000001, B01001001, B00110110, B00000000}, // 3
  {4, 8, B00011000, B00010100, B00010010, B01111111, B00000000}, // 4
  {4, 8, B00100111, B01000101, B01000101, B00111001, B00000000}, // 5
  {4, 8, B00111110, B01001001, B01001001, B00110000, B00000000}, // 6
  {4, 8, B01100001, B00010001, B00001001, B00000111, B00000000}, // 7
  {4, 8, B00110110, B01001001, B01001001, B00110110, B00000000}, // 8
  {4, 8, B00000110, B01001001, B01001001, B00111110, B00000000}, // 9
  {2, 8, B01010000, B00000000, B00000000, B00000000, B00000000}, // :
  {2, 8, B10000000, B01010000, B00000000, B00000000, B00000000}, // ;
  {3, 8, B00010000, B00101000, B01000100, B00000000, B00000000}, // <
  {3, 8, B00010100, B00010100, B00010100, B00000000, B00000000}, // =
  {3, 8, B01000100, B00101000, B00010000, B00000000, B00000000}, // >
  {4, 8, B00000010, B01011001, B00001001, B00000110, B00000000}, // ?
  {5, 8, B00111110, B01001001, B01010101, B01011101, B00001110}, // @
  {4, 8, B01111110, B00010001, B00010001, B01111110, B00000000}, // A
  {4, 8, B01111111, B01001001, B01001001, B00110110, B00000000}, // B
  {4, 8, B00111110, B01000001, B01000001, B00100010, B00000000}, // C
  {4, 8, B01111111, B01000001, B01000001, B00111110, B00000000}, // D
  {4, 8, B01111111, B01001001, B01001001, B01000001, B00000000}, // E
  {4, 8, B01111111, B00001001, B00001001, B00000001, B00000000}, // F
  {4, 8, B00111110, B01000001, B01001001, B01111010, B00000000}, // G
  {4, 8, B01111111, B00001000, B00001000, B01111111, B00000000}, // H
  {3, 8, B01000001, B01111111, B01000001, B00000000, B00000000}, // I
  {4, 8, B00110000, B01000000, B01000001, B00111111, B00000000}, // J
  {4, 8, B01111111, B00001000, B00010100, B01100011, B00000000}, // K
  {4, 8, B01111111, B01000000, B01000000, B01000000, B00000000}, // L
  {5, 8, B01111111, B00000010, B00001100, B00000010, B01111111}, // M
  {5, 8, B01111111, B00000100, B00001000, B00010000, B01111111}, // N
  {4, 8, B00111110, B01000001, B01000001, B00111110, B00000000}, // O
  {4, 8, B01111111, B00001001, B00001001, B00000110, B00000000}, // P
  {4, 8, B00111110, B01000001, B01000001, B10111110, B00000000}, // Q
  {4, 8, B01111111, B00001001, B00001001, B01110110, B00000000}, // R
  {4, 8, B01000110, B01001001, B01001001, B00110010, B00000000}, // S
  {5, 8, B00000001, B00000001, B01111111, B00000001, B00000001}, // T
  {4, 8, B00111111, B01000000, B01000000, B00111111, B00000000}, // U
  {5, 8, B00001111, B00110000, B01000000, B00110000, B00001111}, // V
  {5, 8, B00111111, B01000000, B00111000, B01000000, B00111111}, // W
  {5, 8, B01100011, B00010100, B00001000, B00010100, B01100011}, // X
  {5, 8, B00000111, B00001000, B01110000, B00001000, B00000111}, // Y
  {4, 8, B01100001, B01010001, B01001001, B01000111, B00000000}, // Z
  {2, 8, B01111111, B01000001, B00000000, B00000000, B00000000}, // [
  {4, 8, B00000001, B00000110, B00011000, B01100000, B00000000}, // \ backslash
  {2, 8, B01000001, B01111111, B00000000, B00000000, B00000000}, // ]
  {3, 8, B00000010, B00000001, B00000010, B00000000, B00000000}, // hat
  {4, 8, B01000000, B01000000, B01000000, B01000000, B00000000}, // _
  {2, 8, B00000001, B00000010, B00000000, B00000000, B00000000}, // `
  {4, 8, B00100000, B01010100, B01010100, B01111000, B00000000}, // a
  {4, 8, B01111111, B01000100, B01000100, B00111000, B00000000}, // b
  {4, 8, B00111000, B01000100, B01000100, B00101000, B00000000}, // c
  {4, 8, B00111000, B01000100, B01000100, B01111111, B00000000}, // d
  {4, 8, B00111000, B01010100, B01010100, B00011000, B00000000}, // e
  {3, 8, B00000100, B01111110, B00000101, B00000000, B00000000}, // f
  {4, 8, B10011000, B10100100, B10100100, B01111000, B00000000}, // g
  {4, 8, B01111111, B00000100, B00000100, B01111000, B00000000}, // h
  {3, 8, B01000100, B01111101, B01000000, B00000000, B00000000}, // i
  {4, 8, B01000000, B10000000, B10000100, B01111101, B00000000}, // j
  {4, 8, B01111111, B00010000, B00101000, B01000100, B00000000}, // k
  {3, 8, B01000001, B01111111, B01000000, B00000000, B00000000}, // l
  {5, 8, B01111100, B00000100, B01111100, B00000100, B01111000}, // m
  {4, 8, B01111100, B00000100, B00000100, B01111000, B00000000}, // n
  {4, 8, B00111000, B01000100, B01000100, B00111000, B00000000}, // o
  {4, 8, B11111100, B00100100, B00100100, B00011000, B00000000}, // p
  {4, 8, B00011000, B00100100, B00100100, B11111100, B00000000}, // q
  {4, 8, B01111100, B00001000, B00000100, B00000100, B00000000}, // r
  {4, 8, B01001000, B01010100, B01010100, B00100100, B00000000}, // s
  {3, 8, B00000100, B00111111, B01000100, B00000000, B00000000}, // t
  {4, 8, B00111100, B01000000, B01000000, B01111100, B00000000}, // u
  {5, 8, B00011100, B00100000, B01000000, B00100000, B00011100}, // v
  {5, 8, B00111100, B01000000, B00111100, B01000000, B00111100}, // w
  {5, 8, B01000100, B00101000, B00010000, B00101000, B01000100}, // x
  {4, 8, B10011100, B10100000, B10100000, B01111100, B00000000}, // y
  {3, 8, B01100100, B01010100, B01001100, B00000000, B00000000}, // z
  {3, 8, B00001000, B00110110, B01000001, B00000000, B00000000}, // {
  {1, 8, B01111111, B00000000, B00000000, B00000000, B00000000}, // |
  {3, 8, B01000001, B00110110, B00001000, B00000000, B00000000}, // }
  {4, 8, B00001000, B00000100, B00001000, B00000100, B00000000} // ~
};

void setup() {
  Serial.begin(115200);
  for (int i = 0; i < 8; i++) {
    if (i < 4) {
      pinMode(x[i], OUTPUT);
      pinMode(y[i], OUTPUT);
      digitalWrite(x[i], LOW);
      digitalWrite(y[i], LOW);
    }
    else {
      digitalWrite(y[i], LOW);
    }
  }
}

void loop() {
  if (Serial.available()) {
    delay(5000);
    while (Serial.available()) {
      char ch = Serial.read();
      if (ch >= 32) shiftLetter(ch, 100);
    }
  }
  else shiftLetter(++i, 50);
}

void shiftLetter(char c , uint64_t time) {
  Serial.println("Character: " + String(c));
  c -= 0x20;
  byte buffer[7];
  for (int xyz = 0; xyz < 7; xyz++) buffer[xyz] = CH[c * 7 + xyz];
  //memcpy_P(buffer, CH + 7 * c, 7); // memcpy_P(void* destination, void* source, size_t size);
  if (time != 100) for (int x = 0; x < 8; x++) shiftByte(0x00, 10);
  for (int x = 0; x < buffer[0]; x++) shiftByte( buffer[2 + x], time);
  for (int x = 0; x < 8 - buffer[0]; x++) shiftByte( 0x00, time);
  if (time != 100) for (int x = 0; x < 8; x++) shiftByte(0x00, 10);
  else shiftByte(0x00, 10);
  if (i == 127) i = 32;
}

void shiftByte(byte b, uint64_t time) {
  for (int i = 0; i < 7; i++) data[i] = data[i + 1]; // shift the data to the right
  data[7] = b;
  //for (int i = 7; i >= 0; i--) data[i] = data[i - 1]; // shift the data to the right
  //data[0] = b;
  printData("\nShift Bytes: ");
  matrixUpdate(time);
}


void matrixUpdate(uint64_t time) {
  uint64_t prevMillis = millis() + time;
  while (prevMillis > millis())
    for (int a = 0; a < 8; a++) {
      for (int i = 0; i < 3; i++) digitalWrite(x[i], bitRead(a, i));
      for (int b = 0; b < 8; b++) digitalWrite(y[b], bitRead(data[a], b)); //random(0, 2) //bitRead(data[a], 7 - b)
      digitalWrite(xEn, HIGH);
      delayMicroseconds(100);
      digitalWrite(xEn, LOW);
    }
}

void printData(String str) {
  Serial.print(str);
  for (int i = 0; i < 8; i++) Serial.print("\n\t" + Byte(data[i]));
}

String Byte(byte b) {
  String str = String(b, BIN);
  switch (str.length()) {
    case 1: str = "B0000000" + str; break;
    case 2: str = "B000000" + str; break;
    case 3: str = "B00000" + str; break;
    case 4: str = "B0000" + str; break;
    case 5: str = "B000" + str; break;
    case 6: str = "B00" + str; break;
    case 7: str = "B0" + str; break;
    case 8: str = "B" + str; break;
  }
  return str;
}
