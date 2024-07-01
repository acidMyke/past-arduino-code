typedef enum {NO_WAIT, WAIT, PREVIOUS} MODE;
class ButtonMatrix {
  public:
    void addInputArray(int* , int);
    void addOutputArray(int* , int);
    void addInput(int);
    void addOutput(int);
    void inverseInput();
    void inverseOutput();
    void inverse();
    int read (MODE = NO_WAIT);

  private:
    int* input;
    int* output;
    int inputCount = 0;
    int outputCount = 0;
    int preValue;

};
void ButtonMatrix::addInputArray(int* pins, int count) {
  for (int i = 0; i < count; i++)
    pinMode(pins[i], INPUT_PULLUP);
  input = pins;
  inputCount = count;
}
void ButtonMatrix::addOutputArray(int* pins, int count) {
  for (int i = 0; i < count; i++) {
    pinMode(pins[i], OUTPUT);
    digitalWrite(pins[i], HIGH);
  }
  output = pins;
  outputCount = count;
}
void ButtonMatrix::addInput(int pin) {
  int newInput[inputCount + 1];

  for (int i = 0; i < inputCount; i++) {
    newInput[i] = input[i];
  }

  newInput[inputCount] = pin;

  input = newInput;
  inputCount++;
}
void ButtonMatrix::addOutput(int pin) {
  int newOutput[outputCount + 1];

  for (int i = 0; i < outputCount; i++) {
    newOutput[i] = output[i];
  }

  newOutput[outputCount] = pin;

  output = newOutput;
  outputCount++;
}
void ButtonMatrix::inverseInput() {
  int newInput[inputCount];

  for (int i = 0; i < inputCount; i++) {
    newInput[inputCount - 1 - i] = input[i];
  }

  input = newInput;
}
void ButtonMatrix::inverseOutput() {
  int newOutput[inputCount];

  for (int i = 0; i < outputCount; i++) {
    newOutput[outputCount - 1 - i] = output[i];
  }

  output = newOutput;
}
void ButtonMatrix::inverse() {
  inverseInput();
  inverseOutput();
}
int ButtonMatrix::read(MODE mode) {6
  int value = -1;
  if (mode == NO_WAIT) {
    for (int x = 0; x < outputCount; x++) {
      digitalWrite(output[x], LOW);
      for (int y = 0; y < inputCount; y++) {
        if (digitalRead(inputCount) == LOW) {
          value = (x * inputCount) + y;
          Serial.println("Lib: " + String(value));
        }
      }
      digitalWrite(output[x], HIGH);
    }
  }
  else if (mode == WAIT) {
    while (value == -1) {
      for (int x = 0; x < outputCount; x++) {
        digitalWrite(output[x], LOW);
        for (int y = 0; y < inputCount; y++) {
          if (digitalRead(inputCount) == LOW) {
            value = (x * inputCount) + y;
          }
        }
        digitalWrite(output[x], HIGH);
      }
    }
  }
  else if (mode == PREVIOUS) {
    value = preValue;
  }

  return value;
}

int input[4] = {2, 3, 4, 5};
int output[4] = {6, 7, 8, 9};

ButtonMatrix keypad;

void setup() {
  Serial.begin(115200);
  delay(100);
  keypad.addInputArray(input, 4);
  keypad.addOutputArray(output, 4);
}

void loop() {
  Serial.println(keypad.read());
  delay(100);
}
