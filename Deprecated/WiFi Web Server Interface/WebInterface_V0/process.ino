String process(String request) {
  String html = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\nConnection: keep-alive\r\n\r\n";
  //String req = request.substring(0, request.indexOf('\n'));
  if (request.indexOf("ajax_switch") > -1) {
    html+="<p> The number of request: " + String(++i) + "</p>\n";
  }
  else {  // HTTP request for web page
    // send web page - contains JavaScript with AJAX calls
    html+="<!DOCTYPE html>\n";
    html+="<html>\n";
    html+="<head>\n";
    html+="<title>Arduino Web Page</title>\n";
    html+="<script>\n";
    html+="function GetSwitchState() {\n";
    html+="var request = new XMLHttpRequest();\n";
    html+="request.onreadystatechange = function() {\n";
    html+="if (this.readyState == 4) {\n";
    html+="if (this.status == 200) {\n";
    html+="if (this.responseText != null) {\n";
    html+="document.getElementById(\"switch_txt\").innerHTML = this.responseText;\n";
    html+="}}}}\n";
    html+="request.open(\"POST\", \"ajax_switch\" , true);\n";
    html+="request.send(null);\n";
    html+="setTimeout('GetSwitchState()', 10);\n";
    html+="}\n";
    html+="</script>\n";
    html+="</head>\n";
    html+="<body onload=\"GetSwitchState()\">\n";
    html+="<h1>Arduino AJAX Switch Status</h1>\n";
    html+="<div id=\"switch_txt\"></div>";
    html+="</body>\n";
    html+="</html>\n";
  }
  Serial.println(html);
  return html;
}
