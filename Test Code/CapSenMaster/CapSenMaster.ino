#include <Wire.h>
#include <CapacitiveSensor.h>

#define threshold2 10000
#define threshold 4000

CapacitiveSensor CapSense = CapacitiveSensor(7, 9);

long value;

void setup() {
  Serial.begin(115200);
  Wire.begin();
  CapSense.set_CS_Timeout_Millis(1000);
  CapSense.set_CS_AutocaL_Millis(0xFFFFFFFF);     // turn off autocalibrate on channel 1 - just as an example
}

void loop() {
  value = CapSense.capacitiveSensor(100);
  Wire.beginTransmission(0x2A);
  if (value > threshold2){
    Serial.println("Touch: " + String(value));
  }
  else if (threshold2 > value && value > threshold) {
    Serial.println("Hover: " + String(value));
    Wire.write('1');
  }
  else {
    Serial.println("Not Trigger: " + String(value));
    Wire.write('0');
  }
  Wire.endTransmission();
}
