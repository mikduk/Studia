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
    void deleteFirst();
    void show(int);
    void show();

  private:
    int father(int);
    int left(int);
    int right(int);
    void swap(int, int);
    void minHeapify(int);

  protected:
    void buildMinHeap(int);
};

#endif // HEAP_H
