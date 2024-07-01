typedef const int pin;
typedef enum {MOVE_LEFT, MOVE_RIGHT, MOVE_UP, MOVE_DOWN} move;

pin x[] = {13, 12, 11};
pin y[] = {9, 8, 7, 6, 5, 4, 3, 2};
pin xEn = 10;
pin upDown = A0;
pin leftRight = A1;

byte data[8];

#define threshold 128

void setup() {
  
}

void loop() {
  
}

int moving(uint8_t pieceNo){
  
}

move getInput() {
  int value[] = {analogRead(upDown) - 512, analogRead(upDown) - 512};
  if (value[0] < threshold * -1)return MOVE_DOWN;
  if (value[1] > threshold) return MOVE_LEFT;
  if (value[1] < threshold * -1)return MOVE_RIGHT;
  if (value[0] > threshold * 2) return MOVE_UP; // *2 : make it harder to go up
}

void matrixUpdate(uint64_t time) {
  int prevMillis = millis() + time;
  while (prevMillis > millis())
    for (int a = 0; a < 8; a++) {
      for (int i = 0; i < 3; i++) digitalWrite(x[i], bitRead(a, i));
      for (int b = 0; b < 8; b++) digitalWrite(y[b], bitRead(data[a], b)); //random(0, 2) //bitRead(data[a], 7 - b)
      digitalWrite(xEn, HIGH);
      delayMicroseconds(100);
      digitalWrite(xEn, LOW);
    }
}
