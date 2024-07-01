class Element: public Printable {
  private:
    String key = "";
    int value = "";
  public:
    Element();
    Element(int);
    Element(String, int);
    Element operator = (Element&);
    Element operator + (int v);
    bool operator == (Element&);
    bool operator > (Element&);
    bool operator < (Element&);
    bool operator >= (Element&);
    bool operator <= (Element&);
    size_t printTo(Print&) const;

};

Element::Element() {
  key = "";
  value = 0;
}

Element::Element(int v) {
  key = String(v);
  value = v;
}

Element::Element(String k, int v) {
  key = k;
  value = v;
}

Element Element::operator = (Element& ele) {
  key = ele.key;
  value = ele.value;
  return *this;
}

Element Element::operator + (int v) {
  value += v;
  return *this;
}

bool Element::operator == (Element& ele) {
  return value == ele.value;
}

bool Element::operator > (Element& ele) {
  return value > ele.value;
}

bool Element::operator < (Element& ele) {
  return value < ele.value;
}

bool Element::operator >= (Element& ele) {
  return value >= ele.value;
}

bool Element::operator <= (Element& ele) {
  return value <= ele.value ;
}

size_t Element::printTo(Print& p) const {
  return p.print("Key: " + key + "\tValue: " + String(value));
}
