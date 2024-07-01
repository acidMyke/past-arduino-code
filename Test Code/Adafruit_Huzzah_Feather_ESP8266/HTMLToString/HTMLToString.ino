String s;

void setup() {
  Serial.begin(115200);
  s.reserve(1000);
  Serial.println();
}

void loop() {
  if (Serial.available() > 0) {
    s = Serial.readString();
    if (s.startsWith("Count"))
      Serial.println(s.length() - 5);
  }
  if (s != NULL && !s.startsWith("Count")) {
    Serial.println("\n");
    s.replace("\"", "\\\"");
    if (s.length() <= 200)
      Serial.println("html = \"" + s + "\";");
    else {
      while (s.length() > 200) {
        int index = s.indexOf("\\n", 150) + 3;
        Serial.println("html += \"" + s.substring(0, index) + "\";");
        s.remove(0, index);
      }
      Serial.print("html += \"" + s + "\";");
    }
    s.remove(0);
  }
}
