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
//int oldMillis;
int uploadDate[] = {24, 1, 18};

//#define noDate
#define DateInString
//#define DateInShortString
//#define format24Hour

void setup() {
  Serial.begin(115200);
  while (!Serial) delay(1);
  //WiFi.begin(ssid, password);
  //while (timeStatus() != timeSet) syncInternet();
  while (timeStatus() != timeSet) syncSerial();
  //id = Alarm.alarmOnce(19, 58, 59, alarmEvent);
  //Serial.println("Alarm Set!\nAlarm ID: " + String(id));
  //setTime(6, 01, 30, 23, 1, 18);
  //if (timeStatus() != timeSet) return;

}

void loop() {
  display();
  Alarm.delay(250);
  if (Serial.available()) syncSerial();
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
}

void displayS(String str, time_t _t) {

}

