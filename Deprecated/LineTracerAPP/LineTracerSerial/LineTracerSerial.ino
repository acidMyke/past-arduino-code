const byte comp[4] = {0x1C, 0x01, 0x07, 0x10};

void setup() {
  Serial.begin(9600);
  while (!Serial);
  for (int data = 0; data < 32; data++) {
    Serial.print(data, BIN);
    Serial.print(" : ");
    printMovement(data);
    delay(10);
  }
}

void loop() {
  // put your main code here, to run repeatedly:

}

void printMovement(int data) {
  int left, right;
  String movement = "Stop";

  if ((data & 0x1C) > 0 == (data & 0x01) > 0) left = 0;
  else if (data & 0x1C) left = 1;
  else if (data & 0x01) left = -1;
  else return;

  if ((data & 0x07) > 0 == (data & 0x10) > 0) right = 0;
  else if (data & 0x07) right = 1;
  else if (data & 0x10) right = -1;
  else return;

  if (left == right)
    if (left == 1) movement = "Forward";
    else if (left == 0) movement = "Stop";
    else if (left == -1) movement = "Reverse";
    else return;
  else {
    if (left + right) movement = "Turn ";
    else movement = "Rotate ";
    if (left > right) movement += "Right";
    else movement += "Left";
  }
  Serial.println(movement);
}

