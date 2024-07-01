#include "Printable.h"
#include "Element.h"
#include "List.h"

List<Element> list;

void setup() {
  Serial.begin(9600);
  delay(100);
  list.add(Element("3", 3));
  list.add(Element("4", 4));
  list.add(Element("5", 5));
  list.add(Element("6", 6));
  list.add(Element("9", 9));
  list.add(2);
  list.add(Element("10", 10));
  list.add(1);
  Serial.println(list);

  Serial.println(list[5]);
  Serial.println(list[3]);
}

void loop() {
  
}

