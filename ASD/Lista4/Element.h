//
//  Element.h
//  Lista 4
//
//  Created by Mikis Dukiel on 11/05/2019.
//  Copyright © 2019 Mikis Dukiel. All rights reserved.
//

#ifndef ELEMENT_H
#define ELEMENT_H
#include <string>

enum colour{
  black = 0,
  red = 1
};

class Element{
public:
  std::string key;
  Element * left;
  Element * right;
  Element * parent;
  colour color;
  Element(std::string this_key, Element * this_left, Element * this_right, Element * this_parent, colour this_color = black);
};

#endif // ELEMENT_H
