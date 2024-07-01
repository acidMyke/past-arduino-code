void switchMode(bool mode) {
  digitalWrite(colOE, HIGH); //Actual Mode
  digitalWrite(colCLK, HIGH);
  digitalWrite(colCLK, LOW);
  digitalWrite(colOE, LOW);
  digitalWrite(colCLK, HIGH);
  digitalWrite(colCLK, LOW);
  digitalWrite(colOE, HIGH);
  digitalWrite(colCLK, HIGH);
  digitalWrite(colCLK, LOW);
  digitalWrite(colLE, mode); // Mode Switching
  digitalWrite(colCLK, HIGH);
  digitalWrite(colCLK, LOW);
  digitalWrite(colLE, LOW);
  digitalWrite(colCLK, HIGH);
  digitalWrite(colCLK, LOW); //New Mode
}

void readErrorCode() {
  digitalWrite(colOE, LOW);
  long oldMicros = micros();
  for (int i; i < 3; i++) {
    digitalWrite(colCLK, HIGH);
    digitalWrite(colCLK, LOW);
  }
  while ((micros() - oldMicros) < 5);
  digitalWrite(colOE, HIGH);
  for (int i; i < 3; i++) Serial.print(shiftIn(colSDO, colCLK, MSBFIRST), BIN);
}

void writeConfigCode() {
  Serial.println("Enter Config Code: ");
  for (int i; i < 3; i++) {
    while (!Serial.available());
    shiftOut(colSDO, colCLK, MSBFIRST, (byte)Serial.parseInt());
  }
  digitalWrite(colLE, HIGH);
  digitalWrite(colLE, LOW);
  
}

