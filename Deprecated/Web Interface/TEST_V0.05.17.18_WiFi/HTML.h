struct HTML {
  HTML(String s) {
    request.reserve(s.length());
    request = s;
  }
  
  String getMethod() {
    return request.substring(0, request.indexOf(" /"));
  }

  String getURL() {
    return request.substring(request.indexOf(" /") + 1, request.indexOf(" HTTP/1.1"));
  }

  int getNumSubUrl(){
    String s = getURL();
    int num = 0;
    for(int i = 0; i < s.length(); i++)
      if(s.charAt(i) == '/') {
        SubURL[num++] = i;
      }
    return num;
  }

  String getSubUrl(int index){
    if(index < getNumSubUrl()) return "INVALID";
    return request.substring(SubURL[index], SubURL[index + 1]);
  }

  String getInfo(String s) {
    if(request.indexOf(s) < 0) return "INVALID";
    if(s.endsWith(": ")) s + ": ";
    return request.substring(request.indexOf(s), request.indexOf("\n", request.indexOf(s)));
  }
  
  String request;
  int SubURL[100];
  
};
