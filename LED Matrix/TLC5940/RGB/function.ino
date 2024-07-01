void setAll(int r, int g, int b) {
  for (int r = 0; r < NUM_ROW; r++) {
    for (int c = 0; c < NUM_COLUMN / 3; c++) {
      value[r][c] = r;
      value[r][c + (NUM_COLUMN / 3)] = g;
      value[r][c + 2 * (NUM_COLUMN / 3)] = b;
    }
  }
}

void crazy(int num) {
  for (int i = 0; i < num; i++) {
    for (int r = 0; r < NUM_ROW; r++) {
      for (int c = 0; c < NUM_COLUMN / 3; c++) {
        value[r][c] = random(0, 4095);
        value[r][c + (NUM_COLUMN / 3)] = random(0, 4095);
        value[r][c + 2 * (NUM_COLUMN / 3)] = random(0, 4095);
      }
    }
  }
}

void SD_Animation(String fileName, uint8_t cspin) {
  SD.begin(cspin);
}

void streamToMatrix(const Stream& s){
  if(s.available())
    while(true)
      if(s.read() == '|')
        break;
        uint32_t timeout = millis() + 20000;
  while(s.available() < NUM_ROW*NUM_COLUMN && timeout > millis()) delay(1);
  if(timeout > millis()) return;
  for (int r = 0; r < NUM_ROW; r++) {
    for (int c = 0; c < NUM_COLUMN / 3; c++){
      value[r][c] = s.read();
      value[r][c + (NUM_COLUMN / 3)] = s.read();
      value[r][c + 2 * (NUM_COLUMN / 3)] = s.read();
    }
  }
}

