String HTML(String str) {
  String html = "";
  Serial.println("" + str);
  if (str.equalsIgnoreCase("Home")) {
    html += "<!DOCTYPE html>\n <html>\n <head>\n <meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">\n <style>\n body {margin: 0;}\n ul.topnav {\n ";
    html += "\tlist-style-type: none;\n \tmargin: 0;\n \tpadding: 0;\n \toverflow: hidden;\n \tbackground-color: #333333;\n }\n ul.topnav li {float: left;}\n ul.topnav li a {\n ";
    html += "\tdisplay: block;\n \tcolor: white;\n \ttext-align: center;\n \tpadding: 14px 16px;\n \ttext-decoration: none;\n }\n label{\n \tcolor: white;\n }\n ul.topnav li a:hover:not(.active) {background-color: #777777;}\n ";
    html += "ul.topnav li a.active {background-color: #050505;}\n ul.topnav li.right {float: right;}\n @media screen and (max-width: 400px){\n \tul.topnav li.right, ul.topnav li {float: none;}\n ";
    html += "}\n </style>\n </head>\n <body style=\"background-color:black;\">\n <ul class=\"topnav\">\n \t<li><a class=\"active\" href=\"/Home\">Home</a></li>\n \t<li><a href=\"/Control\">Control</a></li>\n ";
    html += "\t<li><a href=\"/WiFi\">WiFi</a></li>\n </ul>\n </body>\n </html>\n";
  }
  else if (str.equalsIgnoreCase("Control")) {
    html += "<!DOCTYPE html>\r\n <html>\r\n <head>\r\n <script>\r\n function getState(){\r\n \tvar xhttp = new XMLHttpRequest();\r\n \txhttp.onreadystatechange = function(){\r\n ";
    html += "\t\tif (this.readyState == 4){\r\n \t\t\tif(this.status == 200){\r\n \t\t\t\tif(this.responeText != null){\r\n \t\t\tdocument.getElementById(\"state\").innerHTML = this.responeText;\r\n ";
    html += "\t\t\tconsole.log(this.responeText);\r\n \t\t\t\t}\r\n \t\t\t}\r\n \t\t}\r\n \t}\r\n xhttp.open(\"GET\", \"/ControlParam\", true);\r\n xhttp.send(null);\r\n ";
    html += "setTimeout('getState()', 1000);\r\n }\r\n </script>\r\n <meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">\r\n <style>\r\n body {margin: 0;}\r\n ";
    html += "ul.topnav {\r\n \tlist-style-type: none;\r\n \tmargin: 0;\r\n \tpadding: 0;\r\n \toverflow: hidden;\r\n \tbackground-color: #333333;\r\n }\r\n ul.topnav li {float: left;}\r\n ";
    html += "ul.topnav li a {\r\n \tdisplay: block;\r\n \tcolor: white;\r\n \ttext-align: center;\r\n \tpadding: 14px 16px;\r\n \ttext-decoration: none;\r\n }\r\n label{\r\n ";
    html += "\tcolor: white;\r\n }\r\n ul.topnav li a:hover:not(.active) {background-color: #777777;}\r\n ul.topnav li a.active {background-color: #050505;}\r\n ul.topnav li.right {float: right;}\r\n ";
    html += "@media screen and (max-width: 500px){\r\n \tul.topnav li.right, ul.topnav li {float: none;}\r\n }\r\n </style>\r\n </head>\r\n <body onload=\"getState()\" style=\"background-color:black;\">\r\n ";
    html += "<ul class=\"topnav\">\r\n \t<li><a href=\"/Home\">Home</a></li>\r\n \t<li><a class=\"active\" href=\"/Control\">Control</a></li>\r\n \t<li><a href=\"/WiFi\">WiFi</a></li>\r\n ";
    html += "</ul>\r\n \t<div id=\"state\">\r\n \r\n \t</div>\r\n </body>\r\n </html>\r\n ";
  }
  else if (str.equalsIgnoreCase("WiFi")) {
    html += "<!DOCTYPE html>\n <html>\n <head>\n <meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">\n <style>\n body {margin: 0;}\n ul.topnav {\n ";
    html += "\tlist-style-type: none;\n \tmargin: 0;\n \tpadding: 0;\n \toverflow: hidden;\n \tbackground-color: #333333;\n }\n ul.topnav li {float: left;}\n ul.topnav li a {\n ";
    html += "\tdisplay: block;\n \tcolor: white;\n \ttext-align: center;\n \tpadding: 14px 16px;\n \ttext-decoration: none;\n }\n label{\n \tcolor: white;\n }\n ul.topnav li a:hover:not(.active) {background-color: #777777;}\n ";
    html += "ul.topnav li a.active {background-color: #050505;}\n ul.topnav li.right {float: right;}\n @media screen and (max-width: 400px){\n \tul.topnav li.right, ul.topnav li {float: none;}\n ";
    html += "\tspan.psw {\n \t\tdisplay: block;\n \t\tfloat: none;\n \t}\n }\n input[type=text], input[type=password] {\n \twidth: 100%;\n \tpadding: 12px 20px;\n \tmargin: 8px 0;\n ";
    html += "\tdisplay: inline-block;\n \tborder: 1px solid #ccc;\n \tbox-sizing: border-box;\n }\n button {\n \tbackground-color: #4CAF50;\n \tcolor: white;\n \tpadding: 14px 20px;\n ";
    html += "\tmargin: 8px 0;\n \tborder: none;\n \tcursor: pointer;\n \twidth: 100%;\n }\n button:hover {\n \topacity: 0.8;\n }\n label {\n \tcolor: white;\n \t}\n span.psw {\n ";
    html += "\tfloat: right;\n \tpadding-top: 16px;\n }\n </style>\n </head>\n <body style=\"background-color:black;\">\n <ul class=\"topnav\">\n \t<li><a href=\"/Home\">Home</a></li>\n ";
    html += "\t<li><a href=\"/Control\">Control</a></li>\n \t<li><a class=\"active\" href=\"/WiFi\">WiFi</a></li>\n </ul>\n <form method=\"POST\">\n \t<div class=\"WiFi\">\n ";
    html += "\t\t<label ><b>SSID</b></label>\n \t\t<input type=\"text\" placeholder=\"Enter SSID\" name=\"SSID\" required>\n \t\t<label ><b>Password</b></label>\n \t\t<input type=\"password\" placeholder=\"Enter password\" name=\"PASS\">\n ";
    html += "\t\t<button type=\"submit\">Submit</button>\n \t\t<input type=\"checkbox\" name=\"RMEM\" value=\"true\">\n \t\t<label ><b>Remember</b></label>\n \t</div>\n </form>\n </body>\n </html>\n";
  }
  html = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\nConnection: keep-alive\r\n\r\n" + html;
  return html;
}

String POST(String str, String input) {
  String html = "";
  Serial.println(input);
  input.replace("+", " ");
  if (str.equalsIgnoreCase("WiFi")) {
    ssid = input.substring(input.indexOf("SSID=") + 5);
    //Serial.println("SSID: " + ssid);
    if (ssid.indexOf("PASS") != -1) {
      pass = ssid.substring(ssid.indexOf("PASS=") + 5);
      //Serial.println("PASS: " + pass);
      ssid = ssid.substring(0, ssid.indexOf("&PASS="));
      //Serial.println("SSID: " + ssid);
      if (pass.indexOf("RMEM") != -1) {
        rmem = pass.substring(pass.indexOf("RMEM=") + 5).toInt();
        //Serial.println("RMEM: " + rmem);
        pass = pass.substring(0, pass.indexOf("&RMEM="));
        //Serial.println("PASS: " + pass);
      }
    } else if (ssid.indexOf("RMEM") != -1) {
      rmem = ssid.substring(ssid.indexOf("RMEM=") + 5).toInt();
      //Serial.println("RMEM: " + rmem);
      ssid = ssid.substring(0, ssid.indexOf("&RMEM="));
      //Serial.println("SSID: " + ssid);
    }

    Serial.println("SSID: " + ssid + "\tLength: " + String(ssid.length()));
    Serial.println("PASS: " + pass + "\tLength: " + String(pass.length()));
    Serial.println("RMEM: " + String(rmem));

    html += "<!DOCTYPE html>\n <html>\n <head>\n <meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">\n <style>\n body {margin: 0;}\n ul.topnav {\n ";
    html += "\tlist-style-type: none;\n \tmargin: 0;\n \tpadding: 0;\n \toverflow: hidden;\n \tbackground-color: #333333;\n }\n ul.topnav li {float: left;}\n ul.topnav li a {\n ";
    html += "\tdisplay: block;\n \tcolor: white;\n \ttext-align: center;\n \tpadding: 14px 16px;\n \ttext-decoration: none;\n }\n label{\n \tcolor: white;\n }\n ul.topnav li a:hover:not(.active) {background-color: #777777;}\n ";
    html += "ul.topnav li a.active {background-color: #050505;}\n ul.topnav li.right {float: right;}\n @media screen and (max-width: 400px){\n \tul.topnav li.right, ul.topnav li {float: none;}\n ";
    html += "}\n </style>\n </head>\n <body style=\"background-color:black;\">\n <ul class=\"topnav\">\n \t<li><a class=\"active\" href=\"/Home\">Home</a></li>\n \t<li><a href=\"/Control\">Control</a></li>\n ";
    html += "\t<li><a href=\"/WiFi\">WiFi</a></li>\n </ul>\n <label ><b>Your WiFi Setting may have change</b></label>\n <label ><b>Please check and change your network </b></label>\n </body>\n </html>\n";
  }
  html = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n<!DOCTYPE HTML>\r\n<html>\r\n" + html;
  return html;
}

/* Basic Page //
  <!DOCTYPE html>
  <html>
  <head>
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <style>
  body {margin: 0;}

  ul.topnav {
    list-style-type: none;
    margin: 0;
    padding: 0;
    overflow: hidden;
    background-color: #333;
  }

  ul.topnav li {float: left;}

  ul.topnav li a {
    display: block;
    color: white;
    text-align: center;
    padding: 14px 16px;
    text-decoration: none;
    background-color: black;
  }

  ul.topnav li a:hover:not(.active) {background-color: #666666;}

  ul.topnav li a.active {background-color: #111111;}

  ul.topnav li.right {float: right;}

  @media screen and (max-width: 600px){
    ul.topnav li.right,
    ul.topnav li {float: none;}
  }
  </style>
  </head>
  <body style="background-color:black;">

  <ul class="topnav">
  <li><a class="active" href="/Home">Home</a></li>
  <li><a href="/Control">Control</a></li>
  <li><a href="/WiFi">WiFi</a></li>
  </ul>
  </body>
  </html>
*/

/* WiFi AddOn //
  <style>
  input[type=text], input[type=password] {
  width: 100%;
  padding: 12px 20px;
    margin: 8px 0;
    display: inline-block;
    border: 1px solid #ccc;
    box-sizing: border-box;
  }

  button {
  background-color: #4CAF50;
    color: white;
    padding: 14px 20px;
    margin: 8px 0;
    border: none;
    cursor: pointer;
    width: 100%;
  }

  button:hover {
  opacity: 0.8;
  }

  label {
  color: white;
  }

  span.psw {
  float: right;
    padding-top: 16px;
  }

  @media screen and (max-width: 300px) {
  span.psw {
    display: block;
    float: none;
  }
  </style>
  <body>
  <form method="POST">
  <div class="WiFi">
    <label ><b>SSID</b></label>
      <input type="text" placeholder="Enter SSID" name="SSID" required>
      <label ><b>Password</b></label>
      <input type="password" placeholder="Enter password" name="Pass">
      <button type="submit">Submit</button>
      <input type="checkbox" name="mem" value="true">
        <label ><b>Remember</b></label>
    </div>
  </form>
  </body>
*/
