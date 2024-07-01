String htmlAddOn(String body, String style){
  
}

String HTML(String str) {
  String head, body, style, active, refreshRate = "<meta http-equiv=\"refresh\" content=\"30\">";
  Serial.println("" + str);
  if (str.equalsIgnoreCase("Home")) {
    active = "<li><a class=\"active\" href=\"/Home\">Home</a></li>   <li><a href=\"/Control\">Control</a></li>   <li><a href=\"/WiFi\">WiFi</a></li>";
  }
  else if (str.equalsIgnoreCase("Control")) {
    active = "<li><a href=\"/Home\">Home</a></li>   <li><a class=\"active\" href=\"/Control\">Control</a></li>   <li><a href=\"/WiFi\">WiFi</a></li>";
    refreshRate = "<meta http-equiv=\"refresh\" content=\"1\">";
  }
  else if (str.equalsIgnoreCase("WiFi")) {
    style = " input[type=text], input[type=password] {     width: 100%;     padding: 12px 20px;     margin: 8px 0;     display: inline-block;     border: 1px solid #ccc;     box-sizing: border-box; }  button {     background-color: #4CAF50;     color: white;     padding: 14px 20px;     margin: 8px 0;     border: none;     cursor: pointer;     width: 100%; }  button:hover {     opacity: 0.8; }  label {   color: white; }  span.psw {     float: right;     padding-top: 16px; }  @media screen and (max-width: 300px) {     span.psw {        display: block;        float: none;     } }";
    body = "<form method=\"POST\">   <div class=\"WiFi\">     <label ><b>SSID</b></label>       <input type=\"text\" placeholder=\"Enter SSID\" name=\"SSID\" required>       <label ><b>Password</b></label>       <input type=\"password\" placeholder=\"Enter password\" name=\"PASS\">       <button type=\"submit\">Submit</button>       <input type=\"checkbox\" name=\"RMEM\" value=\"1\">         <label ><b>Remember</b></label>     </div>  </form>";
    active = "<li><a href=\"/Home\">Home</a></li>   <li><a href=\"/Control\">Control</a></li>   <li><a class=\"active\" href=\"/WiFi\">WiFi</a></li>";
    refreshRate = "";
  }

  String html = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n<!DOCTYPE HTML>\r\n<html>\r\n<head>\r\n" + refreshRate + "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\"><style> body {margin: 0;}  ul.topnav {     list-style-type: none;     margin: 0;     padding: 0;     overflow: hidden;     background-color: #333; }  ul.topnav li {float: left;}  ul.topnav li a {     display: block;     color: white;     text-align: center;     padding: 14px 16px;     text-decoration: none;     background-colour: black; }  ul.topnav li a:hover:not(.active) {background-color: #666666;}  ul.topnav li a.active {background-color: #111111;}  ul.topnav li.right {float: right;}  @media screen and (max-width: 600px){     ul.topnav li.right,      ul.topnav li {float: none;} }";
  html += style + "</style>" + head + "</head><body style=\"background-color:black;\">  <ul class=\"topnav\">   " + active +  "</ul>";
  html += body + "</body></html>";
  return html;
}

String POST(String str, String input) {
  String head, body, style, active, refreshRate = "<meta http-equiv=\"refresh\" content=\"30\">";
  Serial.println(input);
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

    style = "  label {   color: white;   align: centre; }";
    body = "<label ><b>Your WiFi Setting may have change</b></label> <label ><b>Please check and change your network </b></label>";
    active = "<li><a class=\"active\" href=\"/Home\">Home</a></li>   <li><a href=\"/Control\">Control</a></li>   <li><a href=\"/WiFi\">WiFi</a></li>";
  }
  String html = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n<!DOCTYPE HTML>\r\n<html>\r\n<head>\r\n" + refreshRate + "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\"><style> body {margin: 0;}  ul.topnav {     list-style-type: none;     margin: 0;     padding: 0;     overflow: hidden;     background-color: #333; }  ul.topnav li {float: left;}  ul.topnav li a {     display: block;     color: white;     text-align: center;     padding: 14px 16px;     text-decoration: none;     background-colour: black; }  ul.topnav li a:hover:not(.active) {background-color: #666666;}  ul.topnav li a.active {background-color: #111111;}  ul.topnav li.right {float: right;}  @media screen and (max-width: 600px){     ul.topnav li.right,      ul.topnav li {float: none;} }";
  html += style + "</style>" + head + "</head><body style=\"background-color:black;\">  <ul class=\"topnav\">   " + active +  "</ul>";
  html += body + "</body></html>";
  return html;
}

/* Basic Page //
  <!DOCTYPE html>
  <html>
  <head>
  <meta http-equiv="refresh" content="5">
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
    background-colour: black;
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
  <style>
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
