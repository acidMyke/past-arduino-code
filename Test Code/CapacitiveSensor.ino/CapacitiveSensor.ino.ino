#include <Wire.h>
#include <Keyboard.h>
#include <CapacitiveSensor.h>

CapacitiveSensor CapSense = CapacitiveSensor(4, 5);       // 10M resistor between pins 4 & 2, pin 2 is sensor pin, add a wire and or foil if desired

long value;
long offset = 282647;
int count = 0;
int i = 32;

boolean once = false;

void setup()
{
  Serial.begin(115200);
  //Keyboard.begin();
  Wire.begin(0x2A);
  Wire.onRequest(requestEvent);
  //CapSense.set_CS_Timeout_Millis(1000);

}

void loop()
{
  value = CapSense.capacitiveSensorRaw(30);
  Serial.println("[" + String(millis()) + "] " + String(value) + "\t-\t " + String(offset) + "\t=\t" + String(value - offset));

  if (Serial.available()) {
    if (Serial.peek() == 'r') {
      Serial.read();
      Serial.println("Reset");
      offset += (value - offset);
    }
    else
      Serial.flush();
  }

  if ((value - offset) > 0) {
    if (once == false) {
      Keyboard.write((char)i++);
      once = true;
    }
  }
  else {
    once = false;
  }

  if(i == 128) i = 32; 
}

void requestEvent() {
  Wire.write(value & 0xFF);
  Wire.write((value >> 8) & 0xFF);
  Wire.write((value >> 16) & 0xFF);
  Wire.write((value >> 24) & 0xFF);
}
