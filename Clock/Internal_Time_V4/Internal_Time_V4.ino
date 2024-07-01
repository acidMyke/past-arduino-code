#include <TimeLib.h>
#include <TimeAlarms.h>

AlarmId id;
/*
  #include <ESP8266WiFi.h>
  #include <ESP8266HTTPClient.h>

  const char* ssid = "Yong";
  const char* password = "yong1020";
  const char* url = "http://free.timeanddate.com/clock/i5zkgavq/n236/tlsg/th1";
*/
const int keypad[] = {14, 13, 12, 4, 5, 2, 16};

int preValue;  // use by keypad
int uploadDate[] = {30, 1, 18};

//#define TEST  // Uncomment to use Serial input
//#define no_debug // Uncomment to not use Serial output
//#define noDate // Uncomment to dont print date
#define DateInString // print date in long string
//#define DateInShortString // print date in short string
//#define format24Hour // print hour in 24 hour format

void display(String str, time_t _t = 0);
int readKeypad(int mode = 0);
time_t compileTimeDate(int mode = 0);

void setup() {
  Serial.begin(115200);
  for (int i = 0; i < 7; i++) {
    if (i < 3) {
      pinMode(keypad[i], OUTPUT);
      digitalWrite(keypad[i], HIGH);
    }
    else
      pinMode(keypad[i], INPUT_PULLUP);
  }
  while (!Serial) delay(1);
  //WiFi.begin(ssid, password);
  //while (timeStatus() != timeSet) syncInternet();
  //while (timeStatus() != timeSet) syncSerial();
  //id = Alarm.alarmOnce(19, 58, 59, alarmEvent);
  //Serial.println("Alarm Set!\nAlarm ID: " + String(id));
  setTime(21, 45, 30, 30, 1, 18); // Set a starting time
  if (timeStatus() != timeSet) setTime(0);
}

void loop() {
  switch (readKeypad()) {
    case 0: display(); break;
    case 1: setTD();  break;
    case 2: timer(); break;
    case 3: stopwatch(); break;
    case 4: alarm(); break;
    case 9: syncSerial(); break;
    case 10: adjustTime(-1); display(); delay(100); break;
    case 12: adjustTime(+1); display(); delay(100); break;
  }
  if (now() % 60 == 0) {
    display();
    delay(250);
  }
  serviceAlarms();
}

void stopwatch() {
  time_t oldTime = now();
  display("Stopwatch Started!!");
  while (true) {
    time_t diff = now() - oldTime;
    display("Stopwatch: ", diff);
    delay(500);
    if (readKeypad() == 10) break;
  }
  display("Stopwatch Stopped: ", now() - oldTime);
}

void timer() {
  display("Set Timer");
  time_t newTime = now() + compileTimeDate(1);
  display("Timer Started");
  if (newTime) {
    while (true) {
      time_t diff = newTime - now();
      display("Timer: ", diff);
      delay(500);
      if (readKeypad() == 10) break;
      if (diff = 0) break;
    }
    display("Timer Stopped: ", newTime - now());
  }
  else display("Cancelled");
}

void setTD() {
  display("Set Time");
  time_t T_T = compileTimeDate();
  if (T_T) setTime(T_T);
  else display("Cancelled");
}

time_t compileTimeDate(int mode) {
  TimeElements ntd;
  time_t newTD;
  int digitTime[12] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  delay(500);
  //for (int i = 0; i < 12; i++) digitTime[i] = 0;
  if (mode == 0) { // including date
    for (int i = 0; i < 12 && i > -1; i++) {
      //while (readKeypad(2) == readKeypad()) delay(2);
      delay(250);
      if (readKeypad(1) != 10 && readKeypad(2) != 12) digitTime[i] = readKeypad(2);
      else if (readKeypad(2) == 10) {
        digitTime[i - 1] = 0;
        i -= 2 ;
      }
      ntd.Hour = digitTime[0] * 10 + digitTime[1];
      ntd.Minute = digitTime[2] * 10 + digitTime[3];
      ntd.Second = digitTime[4] * 10 + digitTime[5];
      ntd.Day = digitTime[6] * 10 + digitTime[7];
      ntd.Month = digitTime[8] * 10 + digitTime[9];
      ntd.Year = digitTime[10] * 10 + digitTime[11] + 30;
      newTD = makeTime(ntd);
      display("Set: ", newTD);
    }
  }
  else if (mode == 1) { // excluding date
    for (int i = 0; i < 6 && i > -1; i++) {
      while (readKeypad(2) == readKeypad()) delay(2);
      if (readKeypad(1) != 10 && readKeypad(2) != 12) digitTime[i] = readKeypad(2);
      else if (readKeypad(2) == 10) {
        digitTime[i - 1] = 0;
        i -= 2 ;
      }
      ntd.Hour = digitTime[0] * 10 + digitTime[1];
      ntd.Minute = digitTime[2] * 10 + digitTime[3];
      ntd.Second = digitTime[4] * 10 + digitTime[5];
      ntd.Day = 1;
      ntd.Month = 1;
      ntd.Year = 0;
      newTD = makeTime(ntd);
      display("Set: ", newTD);
    }
  }
  while (readKeypad(2) == readKeypad()) delay(2);
  newTD = makeTime(ntd);
  display("Confirm: ", newTD);
  if (readKeypad(3)) return newTD;
  else return false;
}

int readKeypad(int mode) {
#ifndef TEST
  int _value = -1;
  if (mode == 0) { //Default Mode: read the keypad, return -1 if nothing is pressed
    for (int x = 0; x < 3; x++) {
      digitalWrite(keypad[x], LOW);
      for (int y = 6; y >= 3; y--) {
        if (digitalRead(keypad[y]) == LOW) {
          _value = x + (6 - y) * 3 + 1;
        }
      }
      digitalWrite(keypad[x], HIGH);
    }
  }
  else if (mode == 1) { //Mode 1: wait for the keypad to be pressed, return the value
    while (_value == -1) {
      for (int x = 0; x < 3; x++) {
        digitalWrite(keypad[x], LOW);
        for (int y = 6; y >= 3; y--) {
          if (digitalRead(keypad[y]) == LOW) {
            _value = x + (6 - y) * 3 + 1;
          }
        }
        digitalWrite(keypad[x], HIGH);
      }
      delay(2);
    }
  }
  else if (mode == 2) { // Mode 2: return previous value
    _value = preValue;
  }
  else if (mode == 3) { // Mode 3: return true if Sharp(#) is pressed, else return false
    if (readKeypad(1) != 12) return false;
    else return true;
  }
  delay(10);
  preValue = _value;
  if (_value == 11)return 0;
  else return _value;
#else
  int _value = -1;
  if (mode == 0) {
    if (Serial.available()) {
      char c = Serial.read();
      if (47 < c < 60) _value =  c - 48;
      else {
        Serial.println("NAN");
      }
    }
  }
  else if (mode == 1) {
    while (_value = -1) {
      if (Serial.available()) {
        char c = Serial.read();
        if (47 < c < 60) _value =  c - 48;
        else Serial.println("NAN");
      }
    }
  }
  else if (mode == 2) {
    _value = preValue;
  }
  else if (mode == 3) {
    if (readKeypad(1) != 12) return false;
    else return true;
  }
  if (_value == 11) _value = 12;
  preValue = _value;
  return _value;
#endif
}

void syncSerial() {
  while (!Serial.available()) {
    Serial.println("Waiting for Serial!!");
    delay(2000);
  }
  if (Serial.available()) {
    String str = Serial.readString();
    if (str.startsWith("T")) {
      str.remove(0, 1);
      str.replace(":", "");
      int digitTime[6] = {0, 0, 0, 0, 0, 0};
      for (int i = 0; i < 6; i++) {
        digitTime[i] = str.substring(i, i + 1).toInt();
      }
      setTime(digitTime[0] * 10 + digitTime[1], digitTime[2] * 10 + digitTime[3], digitTime[4] * 10 + digitTime[5], uploadDate[0], uploadDate[1], uploadDate[2]);
      Serial.println("Time Set");
    }
    else if (str.startsWith("A")) {
      str.remove(0, 1);
      str.replace(":", "");
      int digitTime[6] = {0, 0, 0, 0, 0, 0};
      for (int i = 0; i < 6; i++) {
        digitTime[i] = str.substring(i, i + 1).toInt();
      }
      Alarm.alarmOnce(digitTime[0] * 10 + digitTime[1], digitTime[2] * 10 + digitTime[3], digitTime[4] * 10 + digitTime[5], alarmEvent);
      Serial.println("Alarm Set");
    }
  }
}
/*
  void syncInternet() {
  delay(5000);
  if ((WiFi.status() == WL_CONNECTED)) {
    HTTPClient http;
    http.begin(url); //HTTP
    //Serial.printf("[%d] %s replied : ", millis(), url);

    if (http.GET() == HTTP_CODE_OK) {
      String html = http.getString();
      html.remove(0, html.indexOf("1>") + 2);
      html.remove(html.indexOf("</span></a></td></tr></table></body></html>"));
      html.trim();
      html.replace(":", "");
      int digitTime[6] = {0, 0, 0, 0, 0, 0};
      for (int i = 0; i < 6; i++) {
        digitTime[i] = html.substring(i, i + 1).toInt();
      }
      setTime(digitTime[0] * 10 + digitTime[1], digitTime[2] * 10 + digitTime[3], digitTime[4] * 10 + digitTime[5], uploadDate[0], uploadDate[1], uploadDate[2]);
    }
    else {
      Serial.println("Failed");
    }
    http.end();
  }
  else {
    //Serial.println(WiFi.status());
    Serial.print("Connecting to ");
    Serial.println(ssid);
    WiFi.reconnect();
    delay(1000);
  }
  }
*/
void display() {
#ifndef no_debug
  Serial.print("Time: ");
#ifndef format24Hour
  Serial.print(hourFormat12() != 0 ? hourFormat12() > 9 ? String(hourFormat12()) : "0" + String(hourFormat12()) : "00");
#else
  Serial.print(hour() != 0 ? hour() > 9 ? String(hour()) : "0" + String(hour()) : "00");
#endif
  Serial.print(":");
  Serial.print(minute() != 0 ? minute() > 9 ? String(minute()) : "0" + String(minute()) : "00");
  Serial.print(":");
  Serial.print(second() != 0 ? second() > 9 ? String(second()) : "0" + String(second()) : "00");
#ifndef format24Hour
  Serial.print(isPM() ? " PM" : " AM");
#endif
#ifndef NoDate
  Serial.print("\tDate: ");
#ifdef DateInString
  Serial.print(dayStr(weekday()));
  Serial.print(", ");
  Serial.print(monthStr(month()));
  Serial.print(" ");
  Serial.print(day());
  Serial.print(" ");
  Serial.println(year());
#else
#ifdef DateInShortString
  Serial.print(day() > 9 ? String(day()) : "0" + String(day()));
  Serial.print(" ");
  Serial.print(monthShortStr(month()));
  Serial.print(" ");
  Serial.print(String(year()).substring(2));
  Serial.print(", ");
  Serial.println(dayShortStr(weekday()));
#else
  Serial.print(day() > 9 ? String(day()) : "0" + String(day()));
  Serial.print("/");
  Serial.print(month() > 9 ? String(month()) : "0" + String(month()));
  Serial.print("/");
  Serial.println(year());
#endif
#endif
#endif
#endif
//Display code starts here//
}

void display(String str, time_t _t) {
#ifndef no_debug
  if (str.endsWith(": ")) {
    Serial.print(str);
    Serial.print(hour(_t) != 0 ? hour(_t) > 9 ? String(hour(_t)) : "0" + String(hour(_t)) : "00");
    Serial.print(":");
    Serial.print(minute(_t) != 0 ? minute(_t) > 9 ? String(minute(_t)) : "0" + String(minute(_t)) : "00");
    Serial.print(":");
    Serial.print(second(_t) != 0 ? second(_t) > 9 ? String(second(_t)) : "0" + String(second(_t)) : "00");
    if (day(_t) != 1 || month(_t) != 1 || year(_t) != 1970) {
      Serial.print("\t");
      Serial.print(day(_t) > 9 ? String(day(_t)) : "0" + String(day(_t)));
      Serial.print("/");
      Serial.print(month(_t) > 9 ? String(month(_t)) : "0" + String(month(_t)));
      Serial.print("/");
      Serial.println(year(_t));
    }
    else Serial.println();
  }
  else Serial.println(str);
#endif
//Display code starts here//
}

