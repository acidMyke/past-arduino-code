#define ROW 1
#define COLUME 2
#define SINGLE 3
#define LED 4

void reset(int mode = 0, int i = 0, int ii = 0) {
  switch (mode) {
    case LED: Tlc.clear(); break;
    case ROW:
      for (int rgb = 0; rgb < NUM_TLCS ; rgb++) {
        for (int x = 0; x < 16; x++) {
          ledValue[rgb][x][i] = 0;
        }
      }
      break;
    case COLUME:
      for (int rgb = 0; rgb < NUM_TLCS ; rgb++) {
        for (int y = 0; y < NUM_ROWS; y++) {
          ledValue[rgb][i][y] = 0;
        }
      }
      break;
    case SINGLE:
      for (int rgb = 0; rgb < NUM_TLCS ; rgb++) {
        ledValue[rgb][i][ii] = 0;
      }
      break;
    case 0:
      for (int rgb = 0; rgb < NUM_TLCS ; rgb++) {
        for (int x = 0; x < 16; x++) {
          for (int y = 0; y < NUM_ROWS; y++) {
            ledValue[rgb][x][y] = 0;
          }
        }
      }
      break;
  }
}

void matrixUpdate() {
  for (int row = 0; row < NUM_ROWS; row++) {
    for (int colour = 0; colour < NUM_TLCS; colour++) {
      for (int colume = 0; colume < 16; colume++) {
        Tlc.set(  TLC[colour][colume]  , ledValue[colour][colume][row] );
      }
    }
    for (int i = 0; i < 3; i++) {
      digitalWrite(rowPin[i], bitRead(row, i));
    }
    delayMicroseconds(500);
    for (int i = 0; i < 3; i++) {
      digitalWrite(rowPin[i], 0);
    }
  }
  reset(LED);
}

void serialToLedValue(String str) {
  Serial.println(str);
  for (int rgb = 0; rgb < NUM_TLCS ; rgb++) {
    for (int x = 0; x < 16; x++) {
      for (int y = 0; y < NUM_ROWS; y++) {
        int i = (rgb * 16 * NUM_ROWS) + (x * NUM_ROWS) + y;
        String value = str.substring((i * 4) + 1, (i + 1) * 4 );
        int hex[3];
        for (int c = 0; c < 3; c++) {
          int buffer;
          switch (value.charAt(c)) {
            case 48: buffer = 0; break;
            case 49: buffer = 1; break;
            case 50: buffer = 2; break;
            case 51: buffer = 3; break;
            case 52: buffer = 4; break;
            case 53: buffer = 5; break;
            case 54: buffer = 6; break;
            case 55: buffer = 7; break;
            case 56: buffer = 8; break;
            case 57: buffer = 9; break;
            case 65: buffer = 10; break;
            case 66: buffer = 11; break;
            case 67: buffer = 12; break;
            case 68: buffer = 13; break;
            case 69: buffer = 14; break;
            case 70: buffer = 15; break;
          }
          hex[i] = buffer;
        }
        ledValue[rgb][x][y] = map((hex[0] * 16 * 16) + (hex[1] * 16) + hex[2], 0, 4095, 0, bright);
      }
    }
  }
  str.remove(0, 1538);
  oldMillis = millis();
}

