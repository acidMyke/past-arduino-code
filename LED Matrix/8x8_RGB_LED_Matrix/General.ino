void clear() {
  setAll(0);
}

void setAll(uint32_t color) {
  for (int r; r < 8; r++) {
    for (int c; c < 8; c++) {
      value[r][c] = color & 0xFF0000;
      value[r][c] = color & 0x00FF00;
      value[r][c] = color & 0x0000FF;
    }
  }
}


