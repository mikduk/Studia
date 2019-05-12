//
//  Element.cpp
//  Lista 4
//
//  Created by Mikis Dukiel on 11/05/2019.
//  Copyright © 2019 Mikis Dukiel. All rights reserved.
//

#include "Element.h"

Element::Element(std::string this_key, Element * this_left, Element * this_right, Element * this_parent, colour this_color){
  key = this_key;
  left = this_left;
  right = this_right;
  parent = this_parent;
  color = this_color;
}
