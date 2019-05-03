//
//  Heap.h
//  Lista 3 Zadanie 1 "Kolejka priorytetowa"
//
//  Created by Mikis Dukiel on 03/05/2019.
//  Copyright © 2019 Mikis Dukiel. All rights reserved.
//

#ifndef HEAP_H
#define HEAP_H
#include "Element.h"
#include <iostream>
#define MAX_HEAP_SIZE 100

class Heap{

  protected:
    int numberOfElements;
    Element tab[MAX_HEAP_SIZE];

  public:
    Heap();
    int size();
    void add(Element);
    void add(int, int);
    void show(int);
    void show();

  protected:
    int parent(int);
    int left(int);
    int right(int);
    void swap(int, int);
    void minHeapify(int);
    void buildMinHeap(int);
};

#endif // HEAP_H
