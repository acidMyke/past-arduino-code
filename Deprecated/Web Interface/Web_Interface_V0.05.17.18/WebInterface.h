#include <Printable.h>
#include "HTML.h"

class WebInterface {
  public:
    int state = 0;
    void begin(Client&);
    void editTitle(String);
    int run();
    void addButton();
    size_t printTo(Print& p) const;

  private:
    Client* client;
    String title = "Arduino Web Interface";
    String style;
    String script;
    String request;
    String respone;
    String data;
    void processRequest();

} Interface;

void WebInterface::begin(Client& c) {
  client = &c;
}

void WebInterface::editTitle(String t) {
  title = t;
}

int WebInterface::run() {
  if (!client) {
    PRINT("No Client is available\n");
    return -1;
  }
  PRINT("New Client\n");
  int newMillis = millis() + 2000;
  while (!client->available() && newMillis > millis()) delay(1);
  if (client->available()) {
    request = client->readString();
    PRINT("Request:\n\n" + request + "\n\nEnd of Request\n");
    processRequest();
    PRINT("Respone:\n\n" + respone + "\n\nEnd of Respone\n");
    client->println(respone);
    client->stop();
  }
  else if (millis() > newMillis) {
    PRINT("Client Timeout\n");
    client->stop();
    return -1;
  }
  else {
    PRINT("Unknown Error");
    return -1;
  }
}

void WebInterface::processRequest() {
  HTML html = HTML(request);
  respone.remove(0);

  if (html.getMethod() == "GET") {
    if (html.getURL() == "/Control") {
      respone += F("HTTP/1.1 200 OK\r\nContent-Type: text/html\r\nConnection: keep-alive\r\n\r\n");
      respone += F("<!DOCTYPE html>\r\n<html>\r\n<head>\r\n<style>");
      respone += style;
      respone += F("</style><title>");
      respone += title;
      respone += F("</title>\r\n<script>\r\n");
      respone += script;
      respone += F("\r\nfunction GetData(){\r\nvar request = new XMLHttpRequest();\r\n");
      respone += F("request.onreadystatechange = function() {\r\n");
      respone += F("if (this.readyState == 4 && this.status == 200) {\r\n");
      respone += F("if (this.responseText != null) {\r\n");
      respone += F("document.getElementById(\"switch\").innerHTML = this.responseText;\r\n}}}\r\n");
      respone += F("request.open(\"POST\", \"variable\" , true);\r\nrequest.send();\r\n");
      respone += F("setTimeout('GetData()', 1750);\r\n}\r\n</script>\r\n</head>\r\n");
      respone += F("<body style=\"background-color:black;\" onload=\"GetData();\">\r\n<h1 style=\"color:White;\">");
      respone += title;
      respone += F("</h1>\r\n<div id=\"switch\"></div></body>\r\n</html>\r\n");
    }
    else {
      respone += F("HTTP/1.1 404 Not Found\r\nConnection: Closed");
    }
  }
  else if (html.getMethod() == "POST") {
    Serial.println(html.getInfo("Referer"));
    if (html.getInfo("Referer").indexOf("Control")) {
      respone += data;
    }
  }
}

void WebInterface::addButton(){
  script += "var state = 0;\r\nfunction B0(){\r\n state = !state;\r\n console.log(\"State: \" + state.toString()\r\n}\r\n";
  data += String("<button>") + (state? "TRUE" : "FALSE") + "</button>";
}

