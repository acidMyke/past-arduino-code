int x[] = {13, 12, 11};
int y[] = {9, 8, 7, 6, 5, 4, 3, 2};
int xEn = 10;

byte data[8];

void setup() {
  Serial.begin(115200);
  do delay(500); while (!Serial);
}

void loop() {
  rainGen(2);
  for(int a = 1; a < 8; a++) for(int b = 0; b < 8; b++) bitWrite(data[b], bitRead(data[b], a), a - 1);
  matrixUpdate(10);
}

void rainGen(int number) {
  int place[number];
  for (int no = 0; no < number; no++) {
    place[no] = random(0, 8);
    for (int i = 0; i < number; i++) if (i != no && place[no] == place[i]) {
        no -= 2;
        continue;
      }
    data[place[no]] |= 0x01;
  }
}

void matrixUpdate(uint64_t time) {
  int newMillis = millis() + time;
  while (newMillis > millis())
    for (int a = 0; a < 8; a++) {
      for (int i = 0; i < 3; i++) digitalWrite(x[i], bitRead(a, i));
      for (int b = 0; b < 8; b++) digitalWrite(y[b], bitRead(data[a], b)); //random(0, 2) //bitRead(data[a], 7 - b)
      digitalWrite(xEn, HIGH);
      delayMicroseconds(100);
      digitalWrite(xEn, LOW);
    }
}
