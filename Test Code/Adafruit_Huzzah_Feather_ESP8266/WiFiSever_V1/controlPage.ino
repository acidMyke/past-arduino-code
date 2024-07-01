//"<!DOCTYPE html> <html> <head>   <script>    function getState(){          var request = new XMLHttpRequest();             request.onreadystatechange = function(){              if (this.readyState == 4 && this.status == 200 && this.responeText != null){                   document.getElementById(\"state\").innerHTML = this.responeText;                 }             }             request.open(\"POST\", \"\", true);             request.send(\"getState\");             setTimeout('getState()', 1000);     }   </script> </head> <body onload=\"getState()\">  <div id=\"state\">          </div>  </body> </html> 
String controlStyle(){
  String style = "";
  return style;
}

void controlHTML(WiFiClient client, String request){
  Serial.println(request);
  String reply = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\nConnection: keep-alive\r\n\r\n";
  reply += "<button type=\"button\">What</button>";
  reply += "\n<label>I'm DONE</label>";
  Serial.println(reply);
  client.print(reply);
}

