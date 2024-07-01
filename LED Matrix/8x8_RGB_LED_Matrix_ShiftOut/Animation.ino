void wipe() {
  //UP (White - Black)
  for (int pos = 63; pos > -1; pos--) value[pos] = 546 * (pos / 8);
  //DOWN (White - Black)
  for (int pos = 0; pos < 64; pos++) value[pos] = 546 * (pos % 8);
  //LEFT (Red - Green)
  for (int col = 0; col < 8; col++) for (int row = 0; row < 8; row++) color(row, col) = (512 * col) + (32 * (7 - col));
  //Right (Blue - Green)
  for (int col = 8; col > -1; col++) for (int row = 0; row < 8; row++) color(row, col) = (2 * col) + (32 * (7 - col));
}
