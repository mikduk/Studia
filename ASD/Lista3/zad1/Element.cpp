#include "Element.h"
#include <iostream>

Element::Element(int v, int p){
  priority = p;
  value = v;
}

int Element::getPriority(){
  return priority;
}

int Element::getValue(){
  return value;
}

void Element::setPriority(int p){
  priority = p;
}
