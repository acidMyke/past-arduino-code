String process(String request) {
  String html = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\nConnection: keep-alive\r\n\r\n<!DOCTYPE html>\n<html>\n";
  //String req = request.substring(0, request.indexOf('\n'));

  if (request.indexOf("GET") > -1) { 
    // HTTP request for web page
    // send web page - contains JavaScript with AJAX calls
    html += "<head>\n";
    html += "<title>Arduino Web Interface</title>\n";
    html += "<script>\n";
    html += generateScript();
    html += "function GetData() {\n";
    html += "var request = new XMLHttpRequest();\n";
    html += "request.onreadystatechange = function() {\n";
    html += "if (this.readyState == 4 && this.status == 200) {\n";
    html += "if (this.responseText != null) {\n";
    html += "document.getElementById(\"switch\").innerHTML = this.responseText;\n";
    html += "}}}\n";
    html += "request.open(\"POST\", \"variable\" , true);\n";
    html += "request.send(generate());\n";
    html += "setTimeout('GetData()', 500);\n";
    html += "}\n";
    html += "</script>\n";
    html += "</head>\n";
    html += "<body onload=\"GetData()\">\n";
    html += "<h1>Arduino AJAX Web Interface</h1>\n";
    html += "<div id=\"switch\"></div>";
    html += "</body>\n";
    html += "</html>\n";
  }
  else if (request.indexOf("POST") > -1) {
    if (request.indexOf("getData")) {
      html += generateHTML();
    }
  }
  Serial.println("\nRespone:\n\n" + html + "End of Respone\n");
  return html;
}

void data(String str){
  int index[32];
  for(int i = 0; i < 32; i++){
    if(i == 0) index[i] = str.indexOf(",");
    else index[i] = str.indexOf(",", index[i - 1]);
  }
}

