void begin() {
  for (int VP = 0; VP < 32; VP++) {
    minV[VP] = 0;
    maxV[VP] = 0;
    type[VP] = NA;
  }
}

int createSwitch(int VP, int miniV, int maxiV, Type mode) {
  if (0 > VP > 32) return -1;
  minV[VP] = miniV;
  maxV[VP] = maxiV;
  type[VP] = mode;
}

String generateScript() {
  String str;
  String var = "0";
  for(int i = 1; i < 32; i++) var += ",0";
  str += "var vari = ["+ var +"];\n";
  var = String(maxV[0]);
  for(int i = 1; i < 32; i++) var += "," + String(maxV[i]);
  str += "var maxV = ["+ var +"];\n";
  var = String(minV[0]);
  for(int i = 1; i < 32; i++) var += "," + String(minV[i]);
  str += "var minV = ["+ var +"];\n";
  str += "function Switch(num){\n";
  str += "if (vari[num] == minV[num]) vari[num] = maxV[num];\n";
  str += "else if(vari[num] == maxV[num]) vari[num] = minV[num];\n";
  str += "console.log(\"num = \" + vari[num].toString())";
  str += "}\n";
  str += "function generate(){\n";
  str += "var data = \"\";\n";
  str += "for(var x in vari)\n";
  str += "data +=  \",\" + vari[x].toString();\n";
  str += "console.log(\"Data: \" + data );\n";
  str += "return data + \"\\n\";\n";
  str += "}\n";
  return str;
}

String generateHTML() {
  String str;
  str += "<p>[" + String(millis()) + "] Number: " + String(count++) + "</p>\n";
  str += "<button onclick=\"Switch(0)\" >OFF</button>\n";
  return str;
}

