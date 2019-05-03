#include "PriorityQueue.h"
#include "Heap.h"
#include "Element.h"
#include <iostream>

PriorityQueue::PriorityQueue():Heap(){}

void PriorityQueue::insert(int x, int p){
  if (p < 0)
    std::cout<<"Priority must be greater than 0\n";
  else
    add(x, p);
}

void PriorityQueue::empty(){
  if (numberOfElements == 0)
    std::cout << "true (1)" << endl;
  else
    std::cout << "false (0)" << endl;
}

void PriorityQueue::top(){
  if (numberOfElements == 0)
    std::cout<<"\n";
  else
    show(0);
}

void PriorityQueue::pop(){
  if (empty())
    std::cout<<"\n";
  else{
    show(0);
    deleteFirst();
  }
}

void PriorityQueue::priority(int x, int p){
  if (p >= 0){
    for (int i = 0; i < numberOfElements; i++){
      if (tab[i].getValue() == x)
        if (tab[i].getPriority() < p)
          tab[i].setPriority(p);
    }
    buildMinHeap(numberOfElements);
  }
  else
    std::cout<<"Priority must be greater than 0\n";
  }

void PriorityQueue::print(){
  show();
}
};
