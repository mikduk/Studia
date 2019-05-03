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
