//
//  PriorityQueue.cpp
//  Lista 3 "Kolejka priorytetowa"
//
//  Created by Mikis Dukiel on 03/05/2019.
//  Copyright © 2019 Mikis Dukiel. All rights reserved.
//

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
    std::cout << "true (1)\n";
  else
    std::cout << "false (0)\n";
}

void PriorityQueue::top(){
  if (numberOfElements == 0)
    std::cout<<"\n";
  else
    show(0);
}

void PriorityQueue::pop(){
  if (numberOfElements == 0)
    std::cout<<"\n";
  else{
    show(0);
    if (tab[1].getPriority() != tab[--numberOfElements].getPriority()){
      tab[0] = tab[numberOfElements];
      minHeapify(0);
    }
    else{ // case when each element has the same priority
      for (int i=0; i < numberOfElements; i++)
        tab[i] = tab[i+1];
    }
  }
}

void PriorityQueue::priority(int x, int p){
  if (p >= 0){
    for (int i = 0; i < numberOfElements; i++){
      if (tab[i].getValue() == x){
        if (tab[i].getPriority() < p){
          tab[i].setPriority(p);
          int j = i;
          while (j > 0 && tab[parent(j)].getPriority() > tab[j].getPriority()){
            swap(j, parent(j));
            j = parent(j);
          }
        }
    }}
  }
  else
    std::cout<<"Priority must be greater than 0\n";
  }

void PriorityQueue::print(){
  show();
}
