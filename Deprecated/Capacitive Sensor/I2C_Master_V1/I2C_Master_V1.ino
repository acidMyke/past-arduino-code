#include <CapacitiveSensor.h>
#include <Servo.h>
Servo myServo;
#define servoPin 10

#define red 13
#define yellow 11
#define green 9

CapacitiveSensor CapSense[4] = {
  CapacitiveSensor(3, 4),
  CapacitiveSensor(3, 5),
  CapacitiveSensor(3, 6),
  CapacitiveSensor(3, 7)
};

char sValue[4] = {'a', 'b', 'c', 'd'};

boolean once[4] = {false, false, false, false};

char pass[4] = "acbd";
int passIndex = 0;

boolean s = false;
boolean n = false;

int th = 30;

void setup() {
  Serial.begin(115200);
  delay(3000);

  pinMode(yellow, OUTPUT);
  pinMode(red, OUTPUT);
  pinMode(green, OUTPUT);
  digitalWrite(red, HIGH);
  digitalWrite(green, LOW);
  digitalWrite(yellow, LOW);

  for (int i = 0; i < 4; i++)
    CapSense[i].reset_CS_AutoCal();

  myServo.attach(servoPin);
}

void loop() {
  long value[4];

  for (int i = 0; i < 4; i++) {
    value[i] = CapSense[i].capacitiveSensor(30);
    if (value[i] > th) {
      if (once[i] == false) {
        once[i] = true;
        trigger(i);
      }
    }
    else {
      once[i] = false;
    }
    if (s) {
      if (i < 3)
        Serial.print(String(value[i]) + "\t");
      else
        Serial.println(value[i]);
    }
  }

  if (Serial.available()) {
    if (Serial.peek() == 'r') {
      Serial.read();
      switch (Serial.read()) {
        case '0': CapSense[0].reset_CS_AutoCal(); break;
        case '1': CapSense[1].reset_CS_AutoCal(); break;
        case '2': CapSense[2].reset_CS_AutoCal(); break;
        case '3': CapSense[3].reset_CS_AutoCal(); break;
        case -1: for (int i = 0; i < 4; i++) CapSense[i].reset_CS_AutoCal(); break;
      }
      Serial.println("Reset");
    }
    else if (Serial.peek() == 't') {
      Serial.read();
      th = Serial.parseInt();
      Serial.println("Threshold: " + String(th));
    }
    else if (Serial.peek() == 'n') {
      Serial.read();
      Serial.println("New Pass");
      passIndex = 0;
      n = true;
    }
    else if (Serial.read() == 's') {
      s = !s;
      Serial.println(s ? "Serial Enable" : "Serial Disable");
    }
  }
}

void trigger(int sensor) {
  // Do when any Sensor is pressed
  if (n) {
    pass[passIndex] = sValue[sensor];
    Serial.println("Pass " + String(passIndex) + ": " + String(sValue[sensor]));
    if (++passIndex == 8){
      Serial.println("New Pass: " + String(pass));
      n = false;
    }
  }
  else {
    if (pass[passIndex] == sValue[sensor]) {
      Serial.println("Correct\t" + String(++passIndex));
      digitalWrite(yellow, HIGH);
      digitalWrite(green, HIGH);
      delay(100);
      digitalWrite(yellow, LOW);
      digitalWrite(green, LOW);
    }
    else {
      Serial.println("Wrong");
      passIndex = 0;
      digitalWrite(red, LOW);
      delay(500);
      digitalWrite(red, HIGH);
      delay(500);
      digitalWrite(red, LOW);
      delay(500);
      digitalWrite(red, HIGH);
    }

    if (passIndex == (sizeof(pass) / sizeof(char))) {
      Serial.println("Unlock");
      myServo.write(180);
      digitalWrite(red, LOW);
      digitalWrite(green, HIGH);
      digitalWrite(yellow, LOW);
      for(int i = 0; i < 10; i++){
        digitalWrite(yellow, !digitalRead(yellow));
        delay(500);
      }
      Serial.println("Lock");
      myServo.write(0);
      digitalWrite(red, HIGH);
      digitalWrite(green, LOW);
      passIndex = 0;
    }
  }
}
