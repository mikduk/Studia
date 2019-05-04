//
//  PriorityQueue.h
//  Lista 3 "Kolejka priorytetowa"
//
//  Created by Mikis Dukiel on 03/05/2019.
//  Copyright © 2019 Mikis Dukiel. All rights reserved.
//

#ifndef PRIORITYQUEUE_H
#define PRIORITYQUEUE_H
#include "Heap.h"
#include "Element.h"
#include <iostream>

class PriorityQueue :protected Heap{

  public:
    PriorityQueue();
    void insert(int, int);
    bool empty();
    void top();
    int pop();
    void priority(int x, int p);
    void print();

};

#endif // PRIORITYQUEUE_H
