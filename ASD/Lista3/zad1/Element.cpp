//
//  Element.cpp
//  Lista 3 Zadanie 1 "Kolejka priorytetowa"
//
//  Created by Mikis Dukiel on 03/05/2019.
//  Copyright © 2019 Mikis Dukiel. All rights reserved.
//

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
