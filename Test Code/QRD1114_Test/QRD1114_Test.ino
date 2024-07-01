#include <EEPROM.h>
const int motorPin[2][2] = {{2, 3}, {4, 5}};
const int QRD1114_PIN = A0; // Sensor output voltage
int oldMillis[128],  proximity[128], gradient[128];
int i = 0;

void setup() {
  EEPROM.begin();
  Serial.begin(115200);
  pinMode(QRD1114_PIN, INPUT);
  for(int i = 0; i < 128; i++){
    if(EEPROM.read(i) != 0){
      Serial.println("Time: " + String(EEPROM.read(i)) + "/t/t Proximity: " + String(EEPROM.read(128 + i)) + "Gradient: " + String(EEPROM.read(256 + i)));
    }
  }
  for(int i = 0; i < 512; i++){
    EEPROM.write(i, 0);
  }
}

void loop() {
  oldMillis[i] = millis();
  proximity[i] = (float)analogRead(QRD1114_PIN) * 5.0 / 1023.0;
  if (i > 0) {
    gradient[i] = (proximity[i] - proximity[i - 1]) / (oldMillis[i] - oldMillis[i - 1]);
    Serial.println("Time: " + String(oldMillis[i]) + "/t/t Proximity: " + String(proximity[i]) + "Gradient: " + String(gradient[i]));
    EEPROM.write(i, oldMillis[i]);
    EEPROM.write(128 + i, proximity[i]);
    EEPROM.write(256 + i, gradient[i]);
  }
  else
    Serial.println("Time: " + String(oldMillis[i]) + "/t/t Proximity: " + String(proximity[i]));
  delay(100);
  i++;
  if(i == 128){
    i = 0;
  }
}
