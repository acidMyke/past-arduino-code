#include <Servo.h>
#include <Wire.h>
const int ledPin = 13; // the number of the LED pin
Servo myservo; // create servo object to control a servo
int val; // variable to read the value from the analog pin

void setup() 
{
  // initialize the LED pin as an output:
  pinMode(ledPin, OUTPUT);
  Wire.begin((byte)0x2A); 
  Wire.onReceive(receiveEvent); // register event
  Serial.begin(115200); // start serial for output
  myservo.attach(9); // attaches the servo on pin 9 to the servo object
}

void loop() {
  delay(500);
}

void receiveEvent(int howMany) {

}
