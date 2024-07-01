const int segmentPin[] = {2, 3, 4, 5, 6, 7, 8, 9}; // a, b, c, d, e, f, g, dp
const int digitPin[] = {10, 11, 12, 13};

const byte data[] {
  B11111100,  //0
  B01100000,  //1
  B11011010,  //2
  B11110010,  //3
  B01100110,  //4
  B10110110,  //5
  B10111110,  //6
  B11100000,  //7
  B11111110,  //8
  B11100110,  //9
  B00000000   //Nothing
};

const bool logic = HIGH;

void setup() {
  Serial.begin(115200);
  while (!Serial) delay (1);
  for (int i = 0; i < 8; i++)
    pinMode(segmentPin[i], OUTPUT);
  for (int i = 0; i < 4; i++)
    pinMode(digitPin[i], OUTPUT);
  testSegment();
}

void loop() {

}

void testSegment() {
  for (int i = 0; i < 10; i++)
    for (int d = 0; d < 4; d++)
      if (i < 5)displaySegment(d, data[i]);
      else displaySegment(d, data[i - d]);
}

void displaySegment(int digit, byte noData) {
  for (int b = 0; b < 8; b++)
    digitalWrite(digitPin[b], bitRead(noData, b));
  digitalWrite(segmentPin[digit], logic);
  delayMicroseconds(10);
  digitalWrite(segmentPin[digit], !logic);
}

