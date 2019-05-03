#ifndef PRIORITYQUEUE_H
#define PRIORITYQUEUE_H
#include "Heap.h"
#include "Element.h"
#include <iostream>

class PriorityQueue :protected Heap{

  public:
    PriorityQueue():Heap(){}
    void insert(int, int);
    void empty();
    void top();
    void pop();
    void priority(int x, int p);
    void print();

};

#endif // PRIORITYQUEUE_H
