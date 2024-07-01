//Red: 24  Green: 32 Blue: 28 MAX
//Red: 8  Green: 8  Blue: 8 MIN

// TCS230 //
const int s[] = {8, 9, 12, 11}, out = 10;
enum {red = 2, green, blue};

int mode = 0;

struct color {
  int r, g, b;
};

void setup() {
  Serial.begin(115200);
  while (!Serial) delay(1);
  //neopixel(0);
  for (int i = 0; i < 4; i++)
    pinMode(s[i], OUTPUT);
  pinMode(out, INPUT);
  digitalWrite(s[0], HIGH);
  digitalWrite(s[1], HIGH);
}

void loop() {
  color rgb = readColor();
  writeColor(rgb);
  SerialCommands();
  delay(1000);
}

void SerialCommands() {
  if (Serial.available() > 0) {
    String serial = Serial.readString();
    if(serial.indexOf("Processing") != -1) mode = 1;
    if(serial.indexOf("ALL") != -1) mode = 0;
  }
}

color readColor() {
  color value;
  digitalWrite(s[2], LOW);
  digitalWrite(s[3], LOW);
  value.r = pulseIn(out, !digitalRead(out));
  digitalWrite(s[3], HIGH);
  value.b = pulseIn(out, !digitalRead(out));
  digitalWrite(s[2], HIGH);
  value.g = pulseIn(out, !digitalRead(out));
  if (!mode) {
    Serial.print("Intensity:\tRed: " + String(value.r));
    Serial.print("\tGreen: " + String(value.g));
    Serial.println("\tBlue: " + String(value.b));
  }
  value.r = map(value.r, 0, 50, 0, 255);
  digitalWrite(s[3], HIGH);
  value.b = map(value.b, 2, 50, 0, 255);
  digitalWrite(s[2], HIGH);
  value.g = map(value.g, 0, 50, 0, 255);
  if (!mode) {
    Serial.print("8-Bit RGB:\tRed: " + String(value.r));
    Serial.print("\tGreen: " + String(value.g));
    Serial.println("\tBlue: " + String(value.b));
  }
  if (mode) {
    value.r = 255 - value.r;
    value.g = 255 - value.g;
    value.g = 255 - value.b;
    Serial.print(value.r != 0 ? value.r > 15 ? String(value.r, HEX) : "0" + String(value.r, HEX) : "00");
    Serial.print(value.g != 0 ? value.g > 15 ? String(value.g, HEX) : "0" + String(value.g, HEX) : "00");
    Serial.print(value.b != 0 ? value.b > 15 ? String(value.b, HEX) : "0" + String(value.b, HEX) : "00");
  }
  return value;
}

void writeColor(color value) {
  analogWrite(red, value.r);
  analogWrite(green, value.g);
  analogWrite(blue, value.b);
}

