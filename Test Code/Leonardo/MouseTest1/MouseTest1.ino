#include <IRremote.h>
#include <Mouse.h>

int RECV_PIN = 11;
IRrecv irrecv(RECV_PIN);
decode_results results;

uint32_t prevValue = 0;
uint8_t mouseState = false;
uint8_t count = 0;
int8_t moveBy = 5;
uint8_t specialMode = false;

void setup() {
  Serial.begin(9600);
  pinMode(2, INPUT_PULLUP);
  irrecv.enableIRIn(); // Start the receiver
}

void loop() {
  if (digitalRead(2) && mouseState) {
    Mouse.end();
    mouseState = false;
  }
  if (!digitalRead(2) && !mouseState) {
    Mouse.begin();
    mouseState = true;
  }
  if (!mouseState) return;

  if (irrecv.decode(&results)) {
    Serial.println(results.value, HEX);
    switch (results.value) {
      case 0xE9F1A5C3: Mouse.click(); break; //Centre
      case 0x48245F9F:
        if (!specialMode) Mouse.move(0, -moveBy, 0);
        else Mouse.move(0, 0, 1);
        break; //Up
      case 0x2121E3A0:
        if (!specialMode) Mouse.move(0, moveBy, 0);
        else Mouse.move(0, 0, -1);
        break; //Down
      case 0x20C4E583: Mouse.move(-moveBy, 0, 0); break; //Left
      case 0xF9C26984: Mouse.move(moveBy, 0, 0); break; //Right
      case 0x8421BC8F: specialMode = true; break;
      case 0x833A50DC: specialMode = false; break;
    }
    if (prevValue == results.value) {
      if (count++ > 10)
        moveBy = 10;
    }
    else {
      prevValue = results.value;
      moveBy = 5;
      count = 0;
    }
    irrecv.resume(); // Receive the next value
  }
}
