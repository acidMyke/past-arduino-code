#include "Printable.h"

class Element: public Printable {
  private:
    String key = "";
    int value = "";
  public:
    Element();
    Element(String, int);
    size_t printTo(Print&) const;

};

Element::Element(){
  key = "";
  value = 0;
}

Element::Element(String k, int v){
  key = k;
  value = v;
}

size_t Element::printTo(Print& p) const{
  return p.print("Key: " + key + "\tValue: " + String(value));
}

template <class T>
class List: public Printable {
  private:
    int index = 0;
    T list[10];
  public:
    int add(T);
    T get(int);
    T remove(int);
    size_t printTo(Print&) const;
};

template <class T>
int List<T>::add(T element) {
  list[index] = element;
  return index++;
}

template <class T>
T List<T>::get(int rIndex) {
  if (rIndex > index) return;
  return list[rIndex];
}

template <class T>
T List<T>::remove(int rIndex) {
  if (rIndex > index) return;
  T buffer = list[rIndex];
  for (int i = 0; i < (index - rIndex); i++)
    list[rIndex + i] = list[rIndex + i + 1];
  index--;
  return buffer;
}

template <class T>
size_t List<T>::printTo(Print& p) const {
  size_t n = 0;
  for (int i = 0; i < index; i++) {
    n += p.print("[" + String(i) + "] ");
    n += p.println(list[i]);
  }
  return n;
}

List<Element> intList;

void setup() {
  Serial.begin(9600);
  delay(100);
  intList.add(Element("4", 4));
  intList.add(Element("2", 2));
  intList.add(Element("7", 7));
  intList.add(Element("5", 5));
  intList.add(Element("467", 467));
  intList.add(Element("546", 546));
  Serial.println(intList);
  intList.remove(2);
  Serial.println(intList);
  intList.remove(3);
  Serial.println(intList);
  Serial.println(intList.get(4));
}

void loop() {
  // put your main code here, to run repeatedly:

}
