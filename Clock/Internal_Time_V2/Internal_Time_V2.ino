/*/ For Internet Clock //
  #include <ESP8266WiFi.h>
  #include <ESP8266HTTPClient.h>

  const char* ssid = "Yong";
  const char* password = "yong1020";
  const char* url = "http://free.timeanddate.com/clock/i5zkgavq/n236/tlsg/th1";
  // End /*/
//#include <EEPROM.h>

#define hour12

const int keypad[] = {14, 13, 12, 4, 5, 2, 16};
const int tempPin = A0;

const String weekdayString[7] = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"};

int display(String str, long _t = -1);
void timing();
int readButton(int mode = 0);
int compileTime();
void setTime();
void timer();
void stopWatch();
void setAlarm();
void alarmEn();
void EEPROMalarm(int _addr = -1);
int ring();
void sync(String mode);
void event0();
void event1();
void event2();
void event3();
/* void event4();
   void event5();
   void event6();
   void event7();
   void event8();
   void event9();
*/
void (*event[4])() = {event0, event1, event2, event3/*, event4 event5, event6, event7, event8, event9*/}; 

unsigned long oldMillis;

unsigned int t = 0; // t in seconds
unsigned int alarm[5][2];  // alarm[alarmNo][Alarm, Repeat] = {{Alarm 1, Repeat 1}, {Alarm 2, Repeat 2},...}
unsigned int eventTime[4];  // event[eventNo] = {Event 1, Event 2,...} // eventNo = eventNo in void (*event[eventNo])()


int preValue;
int weekday;
//int displayCount = 0;

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
  Serial.println();
  display("Weekday ??");
  if (readButton(1) < 8) weekday = readButton(2);
  display("Today is " + weekdayString[weekday - 1]);
  while (readButton(2) == readButton()) delay(2);
  EEPROMalarm(-1);
}

void loop() {
  timing();
  switch (readButton()) {
    case 0: display("Time: ", t); break;
    case 1: setTime(); break;
    case 2: timer(); break;
    case 3: stopwatch(); break;
    case 4: setAlarm(); break;
    //case 5: sync("Internet"); break;
    case 6: sync("Serial"); break;
    //case 8: displayCount = 0; break;
    case 10: t--; display("Time: ", t); delay(100); break;
    case 12: t++; display("Time: ", t); delay(100); break;
  }
  alarmEn();
}

int display(String str, long _t) {
  if (_t > -1) {
    //displayCount++;
    String hour, minute, second, isPM;
    if (_t < 60) {
      hour = "00";
      minute = "00";
      second = String(_t);
    } else if (_t < 3600) {
      hour = "00";
      minute =  String(_t / 60);
      second = String(_t % 60);
    } else if (_t < 86400) {
      hour = String((_t / 3600));
      minute = String((_t % 3600) / 60);
      second = String(_t % 60);
    } else {
      Serial.println("Invalid Time !!!!");
      return -1;
    }
#ifdef hour12
    if (str == "Time: " || str == "Internet Time: ") {
      if (hour.toInt() == 12) isPM = " PM";
      else if (hour.toInt() > 12) {
        hour = String(hour.toInt() - 12);
        isPM = " PM";
      }
      else isPM = " AM";
    }
#endif
    if (hour.length() == 1) {
      hour = "0" + hour;
    }
    if (minute.length() == 1) {
      minute = "0" + minute;
    }
    if (second.length() == 1) {
      second = "0" + second;
    }
    Serial.println("[" + String(millis()) + "] " + str + hour + ":" + minute + ":" + second + isPM);
    if (str == "Time: ") {
      delay(2500);
      Serial.println("[" + String(millis()) + "] " + String((float)((analogRead(tempPin) - 500) / 10)) + "°C");
    }
  }
  else {
    if (str.indexOf("\n") == -1)
      Serial.println("[" + String(millis()) + "] " + str);
    else {
      Serial.println("[" + String(millis()) + "] " + str.substring(0, str.indexOf("\n")) + str.substring(str.indexOf("\n") + 1));
    }
  }
}

void timing() {
  if (oldMillis < millis() - 1000) {
    int diff = millis() - oldMillis;
    oldMillis = millis() - diff % 1000;
    diff = diff / 1000;
    t = t + diff;
    if (t % 60 == 0 && t != 0)display("Time: ", t);
    //Serial.print("\nMillis: " + String(millis()) + " t: " + String(t) + " Hours: " + String(time(0)) + " Minute: " + String(time(1)) + " Second: " + String(time(2)));
    //Serial.print("\n[" + String(millis()) + "] Time "  + String(time(0)) + ":" + String(time(1)) + ":" + String(time(2)));
    //Serial.print("\t ")
  }
  if (t == -1) {
    t = 86399;
    weekday--;
  }
  if (t == 86400) {
    t = 0;
    weekday++;
  }
  if (weekday == 8) {
    weekday = 1;
  }
}

int readButton(int mode) { // Mode : 0 = read button if available ; 1 = read button until available ; 2 = read the previous value
  int _value = -1;
  if (mode == 2) {
    _value = preValue;
  }
  else if (mode == 1) {
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
  else if (mode == 0) {
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
  delay(10);
  preValue = _value;
  if (_value == 11)return 0;
  else return _value;
}

int compileTime() {
  int tempT,  digitTime[6] = {0, 0, 0, 0, 0, 0};
  delay(500);
  for (int i = 0; i < 6 && i > -1; i++) {
    delay(250);
    if (readButton(1) != 10 && readButton(2) != 12) digitTime[i] = readButton(2);
    else if (readButton(2) == 10) {
      digitTime[i - 1] = 0;
      i -= 2 ;
    }
    tempT = ((digitTime[0] * 10 + digitTime[1]) * 3600) + ((digitTime[2] * 10 + digitTime[3]) * 60) + (digitTime[4] * 10 + digitTime[5]);
    if (display("Set: ", tempT) == -1) return -1;
  }
  tempT = ((digitTime[0] * 10 + digitTime[1]) * 3600) + ((digitTime[2] * 10 + digitTime[3]) * 60) + (digitTime[4] * 10 + digitTime[5]);
  display("Confirm: ", tempT);
  delay(250);
  if (readButton(1) == 12) return tempT;
  else if (readButton(2) == 10) {
    return -1;
    display("Cancelled", -1);
  }
}

void setTime() {
  display("Set Time");
  int tempt = compileTime();
  if (tempt != -1) {
    //delay(250);
    t = tempt;
    oldMillis = millis();
  }
  while (readButton(2) == readButton()) delay(2);
}

void timer() {
  display("Set Timer");
  int timerT = compileTime();
  timing();
  if (timerT != -1) {
    if (readButton(1) == 12) {
      display("Timer Started");
      timerT += t;
      while (true) {
        timing();
        long diff = timerT - t;
        if (readButton() == 10) break;
        else if (readButton(2) == 0) display("Time: ", t);
        else display("Timer: ", diff);
        if (diff < 1) if (ring()) return;
        //delay(100);
      }
    }
  }
}

void stopwatch() {
  unsigned long oldT = t;
  display("Stopwatch Started!!");
  while (true) {
    timing();
    long diff = t - oldT;
    if (readButton() == 10) break;
    else if (readButton(2) == 0) display("Time: ", t);
    else display("Stopwatch: ", diff);
    //delay(100);
  }
  while (readButton(2) == readButton()) delay(2);
}

void setAlarm() {
  while (readButton(2) == readButton()) delay(2);
  display("Set Alarm No");
  int alarmNo = readButton(1) - 1;
  display("Set Alarm " + String(alarmNo + 1));
  int alarmT = compileTime();
  if (alarmT == -1) return;
  alarm[alarmNo][0] = alarmT;
  display("Repeat??");
  byte rep = B00000000;
  while (true) {
    while (readButton(2) == readButton()) delay(2);
    if (readButton(1) == 10 || readButton(2) == 0) rep = 0;
    else if (readButton(2) < 8) bitWrite(rep, 8 - readButton(2), !bitRead(rep, 8 - readButton(2)));
    else if (readButton(2) == 12) break;
    else display("Invalid");
    display("Repeat: " + String(rep, BIN));
  }
  alarm[alarmNo][1] = rep;
  EEPROMalarm(alarmNo);
  display("Alarm Set");
  while (readButton(2) == readButton()) delay(2);
}

void alarmEn() {
  for (int i = 0; i < 5; i++) {
    if (alarm[i][0] != 0 && alarm[i][0] == t && bitRead(alarm[i][1], 8 - weekday)) ring();
  }
}

void EEPROMalarm(int _addr) {
  /*
    if (_addr == -1) {
      for (int _addr = 0; _addr < 5; _addr++) {
        alarm[_addr][0] = ((EEPROM.read(_addr*3) & 0xFF) + ((EEPROM.read(_addr*3 + 1) << 8) & 0xFFFF));
        alarm[_addr][1] = EEPROM.read(_addr*3 + 2);
        display("Alarm " + String(_addr + 1) + ": ", alarm[_addr][0]);
      }
    }
    else {
      _addr *= 3;
      EEPROM.write(_addr, (alarm[_addr / 3][0] & 0xFF));
      EEPROM.write(_addr + 1, (alarm[_addr / 3][0] & 0xFF));
      EEPROM.write(_addr + 2, alarm[_addr / 3][1]);
    }
  */
}

int ring() {
  while (readButton(2) != 12) {
    display("Ringing\n !!!!!");
    readButton();
  }
  while (readButton(2) == readButton()) delay(2);
  return 1;
}

void sync(String mode) {
  /*/Internet Time//
    if (mode == "Internet") {
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
          oldMillis = millis();
          timing();
          //display(t, "PREV: ");
          int buffer = ((digitTime[0] * 10 + digitTime[1]) * 3600) + ((digitTime[2] * 10 + digitTime[3]) * 60) + (digitTime[4] * 10 + digitTime[5]);
          display("Internet Time: ", buffer);
          t = buffer;
          return;
        }
        else {
          Serial.println("Failed");
        }
        http.end();
      }
      else {
        Serial.println(WiFi.status());
        Serial.print("Connecting to ");
        Serial.println(ssid);
        WiFi.disconnect();
        delay(1000);
        WiFi.begin(ssid, password);
        delay(5000);
      }
    }
    //End of Internet Time/*/
  //Serial Time//
  if (mode == "Serial") {
    String serial, stringTime;
    int oldmillis = millis();
    while (oldmillis > millis() - 10000) { // It will timeout in 10 seconds
      if (Serial.available() > 0) {
        serial = Serial.readString();
      }
      else {
        display("Waiting", -1);
        Serial.println("Waiting");
        delay(500);
      }
      if (serial == "Ready") {
        Serial.println("Ready");
        while (true) {
          if (Serial.available() > 0) {
            stringTime = Serial.readString();
            if (stringTime.length() != 6) {
              //Serial.println(stringTime);
              stringTime.replace(":", "");
              int digitTime[6] = {0, 0, 0, 0, 0, 0};
              for (int i = 0; i < 6; i++) {
                digitTime[i] = stringTime.substring(i, i + 1).toInt();
              }
              oldMillis = millis();
              timing();
              //display(t, "PREV: ");
              int buffer = ((digitTime[0] * 10 + digitTime[1]) * 3600) + ((digitTime[2] * 10 + digitTime[3]) * 60) + (digitTime[4] * 10 + digitTime[5]);
              display("Serial Time: ", buffer);
              t = buffer;
              return;
            }
          }
        }
      }
    }
    display("Timeout !!");
  }
  //End of SerialTime
  Serial.println(mode + " sync Failled !!");
}
