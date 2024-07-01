enum {FRONT_PING = 2, REAR_PING = 8, LEFT_PING, RIGHT_PING};
enum {FORWARD, BACK, LEFT, RIGHT};

const int pingServor = 3; // PWM
const int motorEn[] = {4, 7};
const int motorSpeed[] = {5, 6}; // PWM

int distance(int _pin, int angle = 0);

void setup() {
  Serial.begin(115200);
  while (!Serial) delay(1);
}

void loop() {

}

int distance(int _pin, int angle) {
  long duration;
  if (_pin == FRONT_PING) {
    angle = map(angle, 0, 180, 1000, 2000);
    digitalWrite(pingServor, HIGH);
    delayMicroseconds(angle);
    digitalWrite(pingServor, LOW);
    delayMicroseconds(2000 - angle);
  }
  pinMode(_pin, OUTPUT);
  digitalWrite(_pin, LOW);
  delayMicroseconds(2);
  digitalWrite(_pin, HIGH);
  delayMicroseconds(5);
  digitalWrite(_pin, LOW);

  pinMode(_pin, INPUT);
  duration = pulseIn(_pin, HIGH, 20000);
  if (duration >= 20000) return 0;
  return duration / 58;
}

