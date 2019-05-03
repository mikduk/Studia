//
//  Element.h
//  Lista 3 Zadanie 1 "Kolejka priorytetowa"
//
//  Created by Mikis Dukiel on 03/05/2019.
//  Copyright © 2019 Mikis Dukiel. All rights reserved.
//

#ifndef ELEMENT_H
#define ELEMENT_H
#include <iostream>

class Element
{
  public:
    int priority, value;
    Element(int = -1, int = -1);
    int getPriority();
    int getValue();
    void setPriority(int);
};

#endif // ELEMENT_H
