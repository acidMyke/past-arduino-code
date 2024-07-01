const int cdsPin = A0, micPin = A1;

//int cdsReading, micReading;
int delayTime = 500;
int mode = 0;

void setup() {
  Serial.begin(115200);
  while (!Serial) delay(1);
  pinMode(cdsPin, INPUT);
  pinMode(micPin, INPUT);
}

void loop() {
  if (Serial.available()) {
    String serial = Serial.readString();
    if (serial.indexOf("only") != -1)
      if (serial.indexOf("cds") != -1) mode = 1;
      else if (serial.indexOf("mic") != -1) mode = 2;
      else mode = 0;
    else if (serial.indexOf("delay") != -1)
      if (serial.substring(5).toInt() != -1) delayTime = serial.substring(5).toInt();
      else Serial.println("delay is " + String(delayTime));
    else Serial.println("Unsupported");
  }
  switch (mode) {
    case 0: Serial.println("CDS: " + String(analogRead(cdsPin)) + "\tMIC: " + String(analogRead(micPin))); break;
    case 1: Serial.println(analogRead(cdsPin)); break;
    case 2: Serial.println(analogRead(micPin)); break;
  }
  delay(delayTime);
}
