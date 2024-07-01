void setAll(int color) {
  for (int led; led < 64; led++) {
    value[led] = color;
  }
}
/*
void setMultiple(byte position, int color) {
  for(byte pos : position) value[pos] = color;
}*/
