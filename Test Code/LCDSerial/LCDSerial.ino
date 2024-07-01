#include <LiquidCrystal.h>

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal LCD(rs, en, d4, d5, d6, d7);

String serial;

void setup() {
  Serial.begin(115200);
  LCD.begin(16, 2);

  LCD.print("Hello");
  LCD.setCursor(0, 1);
  LCD.print("Ready !!");
}

void loop() {
  if (Serial.available() > 0) {
    LCD.clear();
    serial = Serial.readString();
  }
  if (serial != NULL) {
    if (serial == "clear") {
      LCD.clear();
      LCD.print("Hello");
      LCD.setCursor(0, 1);
      LCD.print("Ready !!");
      serial.remove(0);
      return;
    }
    LCD.print("Serial: ");
    LCD.setCursor(0, 0);
    if (serial.length() < 9) {
      LCD.setCursor(8, 0);
      LCD.print(serial);
    } else if (serial.length() < 16) {
      LCD.setCursor(0, 1);
      LCD.print(serial);
    } else if (serial.length() < 33) {
      LCD.clear();
      LCD.setCursor(0, 0);
      LCD.print(serial.substring(0, 16));
      LCD.setCursor(0, 1);
      LCD.print(serial.substring(16));
    } else {
      LCD.clear();
      LCD.setCursor(0, 0);
      LCD.print("ERROR !!*************");
      LCD.setCursor(0, 1);
      LCD.print("Text too long");
    }
    serial.remove(0);
  }

}
