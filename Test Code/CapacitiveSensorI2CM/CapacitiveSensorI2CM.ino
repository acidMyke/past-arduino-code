// Wire Master Reader
// by Nicholas Zambetti <http://www.zambetti.com>

// Demonstrates use of the Wire library
// Reads data from an I2C/TWI slave device
// Refer to the "Wire Slave Sender" example for use with this

// Created 29 March 2006

// This example code is in the public domain.


#include <Wire.h>
#include <Servo.h>

Servo servo;
long max = 2000L;
long min = 20000L;

void setup() {
  Wire.begin();        // join i2c bus (address optional for master)
  Serial.begin(115200);  // start serial for output
  pinMode(3, OUTPUT);
  servo.attach(9);
}

void loop() {
  Wire.requestFrom(0x2A, 4);    // request 6 bytes from slave device #8

  long value = 0L;

  if (Wire.available() >= 4) {
    long four = Wire.read();
    long three = Wire.read();
    long two = Wire.read();
    long one = Wire.read();
    
    value = ((four << 0) & 0xFF) + ((three << 8) & 0xFFFF) + ((two << 16) & 0xFFFFFF) + ((one << 24) & 0xFFFFFFFF);
    Serial.println(value);
  }
  else Serial.println("Available: " + String(Wire.available()));
  delay(100);

  servoRun(value);
  if(value > 2000) digitalWrite(3, HIGH);
  else digitalWrite(3, LOW);
}

void servoRun(long value){
  if(value > max) max = value;
  if(value < min) min = value;
  servo.write(map(value, min, max, 0, 180));
  Serial.println("Servo: " + String(map(value, 0, max, 0, 180)));
}

