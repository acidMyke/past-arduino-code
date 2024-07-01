#include <Tlc5940.h>
#include <SD.h>

#define NUM_ROW 8
#define NUM_COLUMN 48 // 16 (COLUMN) * 3 (RGB)
#define refreshRate 60 // Hz
#define FPS 30 // Frame per Seconds

int rowPin[3] = {2, 4, 5};
int rowEn = 6;
int brightPin = A0;
int value[NUM_ROW][NUM_COLUMN];
int bright = 2048;

void setup() {
	Serial.begin(115200);
	delay(2500);
  for (int i = 0; i < 3; i++) pinMode(rowPin[i], OUTPUT);
  Tlc.init(bright);
}

void loop() {
	bright = analogRead(brightPin);
  matrixUpdate();
}

void matrixUpdate(){
  for(int r = 0; r < NUM_ROW; r++){
    for (int i = 0; i < 3; i++) digitalWrite(rowPin[i], bitRead(r, i));  // Assign the bit in "row"
    for (int c = 0; c < NUM_COLUMN; c++) Tlc.set(c, map(value[r][c], 0, 4095, 0, bright)); // Assigg the value of "value[row][column]" to TLC
    digitalWrite(rowEn, HIGH); // Enable row
    delayMicroseconds(1000000/(refreshRate*NUM_ROW));
    digitalWrite(rowEn, LOW); // Disable row
  }
}

inline void delayWhile(uint64_t us, void* func(void)){
  int Micros = micros() + us;
  while(Micros > micros()) func();
}

