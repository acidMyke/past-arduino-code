const int segment[] = {13, 12, 11, 10, 9, 8, 7}; // segments a~g connected to digital pins 13-7
const int digit[] = {5, 4, 3, 2};    // digit enables D0~D3 connected to digital pins 5-2

byte CH[] { // CH[0x30 <= ascii <= 0x7A] // ABCDEFG(DP)
  B11111100, //0
  B01100000, //1
  B11011010, //2
  B11110010, //3
  B01100110, //4
  B10110110, //5
  B10111110, //6
  B11100000, //7
  B11111110, //8
  B11110110, //9
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // :, ;, <, > ?, @ (NA)
  B11101110, //A
  0x00, //B
  B10011100, //C
  0x00, //D
  B10011110, //E
  B10001110, //F
  B10111100, //G
  B01101110, //H
  B00001100, //I
  B11111000, //J
  0x00, //K
  B00011100, //L
  0x00, //M, N, O
  B11001110, //P
  0x00, //Q
  B11001100, //R
  B10110110, //S
  0x00, //T
  B01111100, //U
  0x00, //V, W, X
  B11011010, //Z
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // [, \, ], ^, _, ` (NA)
  B10111110, //a
  B00111110, //b
  B01111010, //c
  B01111010, //d
  B11011110, //e
  0x00, 0x00, //f, g
  B00101110, //h
  B00001000, //i
  B01111000, //j
  0x00, 0x00, 0x00,//k, l, m
  B00101010, //n
  B00111010, //o
  0x00, //p
  B11100110, //q
  B00001010, //r
  0x00, //s
  B00011110, //t
  B00111000, //u
  0x00, 0x00, 0x00, //v, w, x
  B01110110, //y
  0x00 //z
};

String input;
byte data[4]; //4 for 0~z, 1 for DP

void setup() {
  Serial.begin(115200);
  Serial.setTimeout(10000);
  for (int s = 0; s < 7; s++)
    pinMode(segment[s], OUTPUT);
  for (int d = 0; d < 4; d++)
    pinMode(digit[d], OUTPUT);
}

void loop() {
  makeData();
  segmentUpdate(5000);
}

void serialEvent() {
  if (Serial.available()) {
    input = Serial.readString();
  }
}

byte getCH(char c) {
  if (CH[c] == 0x00) {
    if (0x41 <= c <= 0x5A) return CH[c + 0x20];
    else if (0x61 <= c <= 0x7A) return CH[c - 0x20];
    else if (0x30 <= c <= 0x39) return CH[c];
    else return 0x00;
  }
  else return CH[c];
}

void makeData() {
  int size = input.length();
  int decimal = input.indexOf(0x2E);
  if (decimal != -1) input.remove(decimal, 1);
  if (size <= 4) for (int i = 0; i < size - 1; i++) data[i] = getCH(input.charAt(i));
  else  {
    Serial.println("ERR: Too Long!!");
    input = "Err";
    decimal = -1;
    for (int i = 0; i < size - 1; i++) data[i] = getCH(input.charAt(i)) + 1;
  }
  if (decimal != -1) data[decimal - 1] += 1;
}

void segmentUpdate(uint64_t time) {
  int newMillis = millis() + time;
  while (newMillis > millis())
    for (int d = 0; d < 4; d++) {
      for (int s = 0; s < 8; s++) digitalWrite(segment[s], bitRead(data[d], s));
      delayMicroseconds(250);
    }
}

