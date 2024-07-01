void reset() {
  for (int x = 0; x < 5; x++) {
    for (int y = 0; y < 16; y++) {
      for (int i = 0; i < 3; i++) {
        rowValue[x][y][i] = 0;
      }
    }
  }
}

void all(int i) {
  for (int x = 0; x < 5; x++) {
    for (int y = 0; y < 16; y++) {
      rowValue[x][y][i] = brightness;
    }
  }
}

void ran(int i, int no = 20) {
  for (int a = 0; a < no; a++ ) {
    rowValue[random(0, 5)][random(0, 16)][i] = brightness;
  }
}
