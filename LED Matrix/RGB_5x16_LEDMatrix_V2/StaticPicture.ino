void reset() {
  for (int x = 0; x < 5; x++) {
    for (int y = 0; y < 3; y++) {
      for (int i = 0; i < 16; i++) {
        rowValue[x][y][i] = 0;
      }
    }
  }
}

void allRed() {
  for (int x = 0; x < 5; x++) {
    for (int i = 0; i < 16; i++) {
      rowValue[x][0][i] = brightness;
    }
  }
}

void allGreen() {
  for (int x = 0; x < 5; x++) {
    for (int i = 0; i < 16; i++) {
      rowValue[x][1][i] = brightness;
    }
  }
}

void allBlue() {
  for (int x = 0; x < 5; x++) {
    for (int i = 0; i < 16; i++) {
      rowValue[x][2][i] = brightness;
    }
  }
}

void allYellow() {
  for (int x = 0; x < 5; x++) {
    for (int i = 0; i < 16; i++) {
      rowValue[x][0][i] = brightness;
      rowValue[x][1][i] = brightness;
    }
  }
}

void allMagenta() {
  for (int x = 0; x < 5; x++) {
    for (int i = 0; i < 16; i++) {
      rowValue[x][0][i] = brightness;
      rowValue[x][2][i] = brightness;
    }
  }
}

void allCyan() {
  for (int x = 0; x < 5; x++) {
    for (int i = 0; i < 16; i++) {
      rowValue[x][1][i] = brightness;
      rowValue[x][2][i] = brightness;
    }
  }
}

void allWhite() {
  for (int x = 0; x < 5; x++) {
    for (int y = 0; y < 3; y++) {
      for (int i = 0; i < 16; i++) {
        rowValue[x][y][i] = brightness;
      }
    }
  }
}
