#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

const char* ssid = "JJ Phone";
const char* password = "20001227";
const char* url = "http://free.timeanddate.com/clock/i5zkgavq/n236/tlsg/th1";

int pin[] = {2, 16, 0, 15};
int digit[] = {14, 12, 5, 4};
int button = 13;

boolean bin[][4] = {
  { 0, 0, 0, 0 },  // 0
  { 0, 0, 0, 1 },  // 1
  { 0, 0, 1, 0 },  // 2
  { 0, 0, 1, 1 },  // 3
  { 0, 1, 0, 0 },  // 4
  { 0, 1, 0, 1 },  // 5
  { 0, 1, 1, 0 },  // 6
  { 0, 1, 1, 1 },  // 7
  { 1, 0, 0, 0 },  // 8
  { 1, 0, 0, 1 },  // 9
  { 1, 0, 1, 0 },  // 10
  { 1, 0, 1, 1 },  // 11
  { 1, 1, 0, 0 }   // 12
};

char en[][10][14] = {
  {"zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"},
  {"ten", "eleven", "twelve", "thirdteen", "fourteen", "fifteen", "sixteen", "seventeen", "eighteen", "nineteen"},
  {"twenty", "twenty-one", "twenty-two", "twenty-three", "twenty-four", "twenty-five", "twenty-six", "twenty-seven", "twenty-eight", "twenty-nine"},
  {"half"}
};

int timeIs[6];
int pre;
int alarm[4];
int alarmEn;

void setup() {
  Serial.begin(115200);
  for (int i = 0; i < 4; i++) {
    pinMode(pin[i], OUTPUT);
    pinMode(digit[i], OUTPUT);
  }
  pinMode(button, INPUT);

  if (digitalRead(button) == LOW) {
    for (int i = 0; i < 4; i++) {
      digitalWrite(pin[i], LOW);
    }
    delay(5000);
    int a = 0, b = 0, c = 0, d = 0, timing = 0;
    while (alarmEn == 0) {
      while (digitalRead(button) == LOW) {
        d++;
        if (d == 10) {
          c++;
          d = 0;
        }
        if (c == 6) {
          b++;
          c = 0;
        }
        if (b == 10) {
          a++;
          b = 0;
        }
        if (a == 2 & b == 4) {
          a = 0;
          b = 0;
          c = 0;
          d = 0;
        }
        Serial.printf("%d%d:%d%d\n", a, b, c, d);
        //timeToBCD(2000);
        //BCDMultiplex();
        delay(100);
        timing = millis();
      }
      if (timing > millis() - 5000) {
        alarm[0] = a;
        alarm[1] = b;
        alarm[2] = c;
        alarm[3] = d;
        alarmEn = 1;
      }
      delay(500);
    }
  }
  for (int i = 0; i < 4; i++) {
    digitalWrite(digit[i], LOW);
  }

  while (!Serial)delay(100);
}

void loop() {

  // wait for WiFi connection

  if ((WiFi.status() == WL_CONNECTED)) {

    HTTPClient http;

    http.begin(url); //HTTP
    //Serial.printf("[%d] %s replied : ", millis(), url);

    if (http.GET() == HTTP_CODE_OK) {
      String html = http.getString();
      html.remove(0, html.indexOf("1>") + 2);
      html.remove(html.indexOf("</span></a></td></tr></table></body></html>"));
      html.trim();
      //Serial.println(html);
      stringToTime(html);
    }
    else {
      runLight();
    }
    http.end();
  }
  else {
    Serial.println(WiFi.status());
    Serial.print("Connecting to ");
    Serial.println(ssid);
    WiFi.disconnect();
    runLight();
    delay(1000);
    WiFi.begin(ssid, password);
    delay(5000);
  }
  delay(10);
  if (alarmEn == 1)runAlarm();
  if (digitalRead(button) == LOW) {
    timeToBCD(5000);

    //BCDMultiplex();
  }
}

void stringToTime(String strTime) {
  strTime.replace(":", "");
  //Serial.println(strTime);
  int time_len = strTime.length();
  if (time_len == 6) {
    for (int i = 0; i < time_len; i++) {
      timeIs[i] = strTime.charAt(i) - 48;
    }
  }
  if (time_len == 5) {
    timeIs[0] = 0;
    for (int i = 1; i <= time_len; i++) {
      timeIs[i] = strTime.charAt(i - 1) - 48;
    }
  }
  if (timeIs[5] != pre) {
    pre = timeIs[5];
    timeToSpeech();
    //Serial.printf("The time is %d%d:%d%d:%d%d\n", timeIs[0], timeIs[1], timeIs[2], timeIs[3], timeIs[4], timeIs[5]);
    //Serial.printf("[%d]The time is %d%d:%d%d:%d%d\n", millis(), timeIs[0], timeIs[1], timeIs[2], timeIs[3], timeIs[4], timeIs[5]);
  }
}

void timeToSpeech() {
  if (timeIs[0] == 0 || ( timeIs[0] == 1  && timeIs[1] < 2)) {   // 00 to 12 : morning
    if (timeIs[2] == 0 && timeIs[3] == 0) {
      Serial.printf("It is %s o'clock in the morning\n", en[timeIs[0]][timeIs[1]]);
    }
    else if (timeIs[2] < 3 || (timeIs[2] == 3 && timeIs[3] == 0)) {
      Serial.printf("It is %s minuets pass %s o'clock in the morning\n", en[timeIs[2]][timeIs[3]], en[timeIs[0]][timeIs[1]]);
    }
    else {
      Serial.printf("It is %s minuets to %s o'clock in the morning\n", en[5 - timeIs[2]][10 - timeIs[3]], en[timeIs[0]][timeIs[1] + 1]);
    }
  }
  else if (timeIs[0] == 1 && timeIs[1] < 7) { // 12 to 17 : afternoon
    if (timeIs[2] == 0 && timeIs[3] == 0) {
      Serial.printf("It is %s o'clock in the afternoon\n", en[timeIs[0] - 1][timeIs[1] - 2]);
    }
    else if (timeIs[2] < 3 || (timeIs[2] == 3 && timeIs[3] == 0)) {
      Serial.printf("It is %s minuets pass %s o'clock in the afternoon\n", en[timeIs[2]][timeIs[3]], en[timeIs[0] - 1][timeIs[1] - 2]);
    }
    else {
      Serial.printf("It is %s minuets to %s o'clock in the afternoon\n", en[5 - timeIs[2]][10 - timeIs[3]], en[timeIs[0] - 1][timeIs[1] + 1 - 2]);
    }
  }
  else if (timeIs[0] == 1  || ( timeIs[0] == 2  && timeIs[1] == 0)) { // 17 to 21 : evening
    if (timeIs[2] == 0 && timeIs[3] == 0) {
      Serial.printf("It is %s o'clock in the evening\n", en[timeIs[0] - 1][timeIs[1] - 2]);
    }
    else if (timeIs[2] < 3 || (timeIs[2] == 3 && timeIs[3] == 0)) {
      Serial.printf("It is %s minuets pass %s o'clock in the evening\n", en[timeIs[2]][timeIs[3]], en[timeIs[0] - 1][timeIs[1] - 2]);
    }
    else {
      Serial.printf("It is %s minuets to %s o'clock in the evening\n", en[5 - timeIs[2]][10 - timeIs[3]], en[timeIs[0] - 1][timeIs[1] + 1 - 2]);
    }
  }
  else  { // 21 to 00 : night
    if (timeIs[2] == 0 && timeIs[3] == 0) {
      Serial.printf("It is %s o'clock at night\n", en[timeIs[0] - 1][timeIs[1] - 2]);
    }
    else if (timeIs[2] < 3 || (timeIs[2] == 3 && timeIs[3] == 0)) {
      Serial.printf("It is %s minuets pass %s o'clock at night\n", en[timeIs[2]][timeIs[3]], en[timeIs[0] - 1][timeIs[1] - 2]);
    }
    else {
      Serial.printf("It is %s minuets to %s o'clock at night\n", en[5 - timeIs[2]][10 - timeIs[3]], en[timeIs[0] - 1][timeIs[1] + 1 - 2]);
    }
  }
}

void timeToBCD(int delayer) {
  if ((timeIs[0] == 1 && timeIs[1] > 2) || timeIs[0] == 2) {
    timeIs[0] = timeIs[0] - 1;
    timeIs[1] = timeIs[1] - 2;
  }
  if (timeIs[0] != 0) {
    timeIs[1] = (timeIs[0] * 10) + timeIs[1];
    timeIs[0] = 0;
  }
  //if (digitalRead(button) == LOW) {
  for (int x = 1; x < 4; x++) {
    for (int i = 0; i < 4; i++) {
      digitalWrite(pin[i], bin[timeIs[x]][i]);
    }
    delay(delayer);
    for (int i = 0; i < 4; i++) {
      digitalWrite(pin[i], 1);
    }
    delay(delayer / 50);
  }
  //}
  //else {
  for (int i = 0; i < 4; i++) {
    digitalWrite(pin[i], 0);
  }
  //}
}

void BCDMultiplex() {
  if ((timeIs[0] == 1 && timeIs[1] > 2) || timeIs[0] == 2) {
    timeIs[0] = timeIs[0] - 1;
    timeIs[1] = timeIs[1] - 2;
  }
  if (timeIs[0] != 0) {
    timeIs[1] = (timeIs[0] * 10) + timeIs[1];
    timeIs[0] = 0;
  }
  //if (digitalRead(button) == LOW) {
  for (int x = 1; x < 4; x++) {
    for (int i = 0; i < 4; i++) {
      digitalWrite(pin[i], bin[timeIs[x]][i]);
    }
    for (int i = 0; i < 4; i++) {
      digitalWrite(digit[i], HIGH);
    }
    digitalWrite(digit[x], HIGH);
    delayMicroseconds(5000);
    //delay(1000);
    digitalWrite(digit[x], LOW);
  }
  for (int i = 0; i < 4; i++) {
    digitalWrite(pin[i], 0);
  }
  //}
}

void runLight() {
  for (int i = 0; i < 4; i++) {
    digitalWrite(pin[i], 1);
    delay(50);
    digitalWrite(pin[i], 0);
    delay(50);
  }
  for (int i = 3; i >= 0; i--) {
    digitalWrite(pin[i], 1);
    delay(50);
    digitalWrite(pin[i], 0);
    delay(50);
  }
}

void runAlarm() {
  int ring = 0;
  for (int i = 0; i < 4; i++) {
    if (timeIs[i] == alarm[i])ring++;
  }
  if (ring == 4) {
    while ( digitalRead(button) == HIGH ) {
      for (int x = 0; x < 4; x++) {
        digitalWrite(digit[x], HIGH);
        for (int i = 3; i >= 0; i--) {
          digitalWrite(pin[i], 1);
          delay(500);
        }
        for (int i = 3; i >= 0; i--) {
          digitalWrite(pin[i], 0);
          delay(500);
        }
        digitalWrite(digit[x], LOW);
      }
    }
  }
}

