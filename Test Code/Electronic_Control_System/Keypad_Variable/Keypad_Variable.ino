#define NUMOFCOLUMN 4
#define NUMOFROW 4

const int columnPin[NUMOFCOLUMN] = {2, 3, 4, 5};
const int rowPin[NUMOFROW] = {6, 7, 8, 9};

const bool buttonLogic = HIGH;

String c[NUMOFROW*NUMOFCOLUMN] = {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12", "13", "14", "15"};

void setup() {
  Serial.begin(115200);
  while(!Serial) delay(1);
  for(int x = 0; x < NUMOFCOLUMN; x++){
    pinMode(columnPin[x], OUTPUT);
    digitalWrite(columnPin[x], !buttonLogic);
  }
  for(int y = 0; y < NUMOFROW; y++){
    pinMode(rowPin[y], INPUT);
  }
}

void loop() {
  readKeypad();
}

void readKeypad(){
  int value = -1;
  for(int x = 0; x < NUMOFCOLUMN; x++) {
    digitalWrite(columnPin[x], buttonLogic);
    for(int y = 0; y < NUMOFROW; y++) if (digitalRead(rowPin[y]) == buttonLogic && value == 0) value = x + y * 3;
    digitalWrite(columnPin[x], !buttonLogic);
  }
  if (value != 0){
    Serial.println("Value: " + String(value) + "\t It represent: " + c[value]);
  }
  value = 0;
  delay(100);
}

