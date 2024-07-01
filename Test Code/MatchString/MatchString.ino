String s[5] = {"delay", "delayMciroseconds", "pinMode", "digitalRead", "digitalWrite"};

void setup() {
  Serial.begin(115200);
  while (!Serial);
  Serial.println("Ready");
}

void loop() {
  if (Serial.available()) {
    matchString();
  }
}

void matchString() {
  uint32_t code = 0;
  char c = Serial.peek();
  for (int i = 0; i < 5; i++) {
    if (c == s[i].charAt(0)) {
      code = code * 6 + i + 1;
    }
    else {
      code = code * 6;
    }
  }
  if (code == 0) return -1;
  Serial.read();
  Serial.println(code);

  uint32_t newCode = 0;
  int index = 1;
  while (code > 5) {
    c = Serial.peek();
    Serial.print("Matching ");
    Serial.print(c);
    Serial.print(" to ");
    Serial.print(s[(code % 6) - 1].charAt(index));
    Serial.print(" in ");
    Serial.println(s[(code % 6) - 1]);
    if (c = s[(code % 6) - 1].charAt(index)) {
      Serial.println("Match " + String(c) + " to " + String(s[(code % 6) - 1].charAt(index)));
      newCode = (newCode * 6) + (code % 6);
    }
    code = (code - (code % 6)) / 6;
    if (code <= 5) {
      code = newCode;
      newCode = 0;
      index++;
      Serial.read();
    }
  }
  if (code <= 5) {
    Serial.println("Only Match " + s[code - 1]);
  }
  else {
    Serial.println("No match");
    return -2;
  }
  //  int stringIndex = 0;
  //  int matches = 0;
  //  int function = -1;
  //  while (matches != 1) {
  //    char c = Serial.peek();
  //    if(c == -1) c = 0;
  //    for(int i = 0; i < 5; i++) {
  //      Serial.println("Matching " + String(s[i]) + ": " + String((char)s[i].charAt(stringIndex))  + " to " + String(c));
  //      if(c == s[i].charAt(stringIndex)){
  //        Serial.println("Matched: " + String(s[i]));
  //        matches++;
  //        function = i;
  //      }
  //    }
  //    if(matches > 1){
  //      stringIndex++;
  //      matches++;
  //      Serial.read();
  //      function = -1;
  //    }
  //    else if (matches == 0){
  //      return -2;
  //    }
  //  }
  //  if(matches == 1 && function > 0){
  //    Serial.println("Match: " + s[function]);
  //    Serial.find('(');
  //  }
}

