PROGMEM const boolean animationFrame[8][5][16] = {
  {
    { 0,  0,  1,  0,  0,  0,  0,  0,  0,  0,  1,  0,  0,  0,  0,  0 },
    { 0,  1,  0,  1,  0,  0,  0,  0,  0,  1,  0,  1,  0,  0,  0,  0 },
    { 1,  0,  0,  0,  1,  0,  0,  0,  1,  0,  0,  0,  1,  0,  0,  0 },
    { 0,  0,  0,  0,  0,  1,  0,  1,  0,  0,  0,  0,  0,  1,  0,  1 },
    { 0,  0,  0,  0,  0,  0,  1,  0,  0,  0,  0,  0,  0,  0,  1,  0 }
  },
  {
    { 0,  1,  0,  0,  0,  0,  0,  0,  0,  1,  0,  0,  0,  0,  0,  0 },
    { 1,  0,  1,  0,  0,  0,  0,  0,  1,  0,  1,  0,  0,  0,  0,  0 },
    { 0,  0,  0,  1,  0,  0,  0,  1,  0,  0,  0,  1,  0,  0,  0,  1 },
    { 0,  0,  0,  0,  1,  0,  1,  0,  0,  0,  0,  0,  1,  0,  1,  0 },
    { 0,  0,  0,  0,  0,  1,  0,  0,  0,  0,  0,  0,  0,  1,  0,  0 }
  },
  {
    { 1,  0,  0,  0,  0,  0,  0,  0,  1,  0,  0,  0,  0,  0,  0,  0 },
    { 0,  1,  0,  0,  0,  0,  0,  1,  0,  1,  0,  0,  0,  0,  0,  1 },
    { 0,  0,  1,  0,  0,  0,  1,  0,  0,  0,  1,  0,  0,  0,  1,  0 },
    { 0,  0,  0,  1,  0,  1,  0,  0,  0,  0,  0,  1,  0,  1,  0,  0 },
    { 0,  0,  0,  0,  1,  0,  0,  0,  0,  0,  0,  0,  1,  0,  0,  0 }
  },
  {
    { 0,  0,  0,  0,  0,  0,  0,  1,  0,  0,  0,  0,  0,  0,  0,  1 },
    { 1,  0,  0,  0,  0,  0,  1,  0,  1,  0,  0,  0,  0,  0,  1,  0 },
    { 0,  1,  0,  0,  0,  1,  0,  0,  0,  1,  0,  0,  0,  1,  0,  0 },
    { 0,  0,  1,  0,  1,  0,  0,  0,  0,  0,  1,  0,  1,  0,  0,  0 },
    { 0,  0,  0,  1,  0,  0,  0,  0,  0,  0,  0,  1,  0,  0,  0,  0 }
  },
  {
    { 0,  0,  0,  0,  0,  0,  1,  0,  0,  0,  0,  0,  0,  0,  1,  0 },
    { 0,  0,  0,  0,  0,  1,  0,  1,  0,  0,  0,  0,  0,  1,  0,  1 },
    { 1,  0,  0,  0,  1,  0,  0,  0,  1,  0,  0,  0,  1,  0,  0,  0 },
    { 0,  1,  0,  1,  0,  0,  0,  0,  0,  1,  0,  1,  0,  0,  0,  0 },
    { 0,  0,  1,  0,  0,  0,  0,  0,  0,  0,  1,  0,  0,  0,  0,  0 }
  },
  {
    { 0,  0,  0,  0,  0,  1,  0,  0,  0,  0,  0,  0,  0,  1,  0,  0 },
    { 0,  0,  0,  0,  1,  0,  1,  0,  0,  0,  0,  0,  1,  0,  1,  0 },
    { 0,  0,  0,  1,  0,  0,  0,  1,  0,  0,  0,  1,  0,  0,  0,  1 },
    { 1,  0,  1,  0,  0,  0,  0,  0,  1,  0,  1,  0,  0,  0,  0,  0 },
    { 0,  1,  0,  0,  0,  0,  0,  0,  0,  1,  0,  0,  0,  0,  0,  0 }
  },
  {
    { 0,  0,  0,  0,  1,  0,  0,  0,  0,  0,  0,  0,  1,  0,  0,  0 },
    { 0,  0,  0,  1,  0,  1,  0,  0,  0,  0,  0,  1,  0,  1,  0,  0 },
    { 0,  0,  1,  0,  0,  0,  1,  0,  0,  0,  1,  0,  0,  0,  1,  0 },
    { 0,  1,  0,  0,  0,  0,  0,  1,  0,  1,  0,  0,  0,  0,  0,  1 },
    { 1,  0,  0,  0,  0,  0,  0,  0,  1,  0,  0,  0,  0,  0,  0,  0 }
  },
  {
    { 0,  0,  0,  1,  0,  0,  0,  0,  0,  0,  0,  1,  0,  0,  0,  0 },
    { 0,  0,  1,  0,  1,  0,  0,  0,  0,  0,  1,  0,  1,  0,  0,  0 },
    { 0,  1,  0,  0,  0,  1,  0,  0,  0,  1,  0,  0,  0,  1,  0,  1 },
    { 1,  0,  0,  0,  0,  0,  1,  0,  1,  0,  0,  0,  0,  0,  1,  0 },
    { 0,  0,  0,  0,  0,  0,  0,  1,  0,  0,  0,  0,  0,  0,  0,  0 }
  }
};


//boolean animationFrame[2][8][5][16];

void triangleWave(int i) {
  for (int t = 0; t < 8; t++ ) {
    for (int x = 0; x < 5; x++) {
      for (int y = 0; y < 16; y++) {
        rowValue[x][y][i] = map ( animationFrame[t][x][y], 0, 1, 0, brightness ) ;
      }
    }
    matrixUpdate(7500);
  }
}


