#include "Lambda.h"

Lambda<String(void)> lambda;

void setup() {
  lambda = []()-> String{};
}

void loop() {

}
