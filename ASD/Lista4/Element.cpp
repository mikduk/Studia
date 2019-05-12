//
//  Element.cpp
//  Lista 4
//
//  Created by Mikis Dukiel on 11/05/2019.
//  Copyright © 2019 Mikis Dukiel. All rights reserved.
//

#include "Element.h"

Element::Element(std::string this_key, Element * this_left, Element * this_right, Element * this_parent, colour this_color){
  this_key = key;
  this_left = left;
  this_right = right;
  this_parent = parent;
  this_color = color;
}
