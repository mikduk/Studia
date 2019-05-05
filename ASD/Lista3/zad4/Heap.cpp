//
//  Heap.cpp
//  Lista 3 Zadanie 1 "Kolejka priorytetowa"
//
//  Created by Mikis Dukiel on 03/05/2019.
//  Copyright © 2019 Mikis Dukiel. All rights reserved.
//

#include "Heap.h"
#include "Element.h"
#include <iostream>

Heap::Heap(){
  numberOfElements = 0;
}

int Heap::size(){
  return numberOfElements;
}

void Heap::add(Element a){
  tab[numberOfElements] = a;
  int j = numberOfElements;
  while (j > 0 && tab[parent(j)].getPriority() > tab[j].getPriority()){
    swap(j, parent(j));
    j = parent(j);
  }
  numberOfElements++;
}

void Heap::add(int a, int b){
  Element temp(a,b);
  add(temp);
}

void Heap::show(int i){
  if (i < numberOfElements)
    std::cout << "value: " << tab[i].getValue() << ", priority: " << tab[i].getPriority() << std::endl;
  else
    std::cout << " i > heap.size " << std::endl;
}

void Heap::show(){
  std::cout << "(" << tab[0].getValue() << ", " << tab[0].getPriority() << ")";
  for (int i = 1; i < numberOfElements; i++)
    std::cout << ", (" << tab[i].getValue() << ", " << tab[i].getPriority() << ")";
  std::cout << std::endl;
}

int Heap::parent(int i){
  if (i==0)
    return 0;
  else
    return ((i+1)/2)-1;
}

int Heap::left(int i){
  return 2*(i+1)-1;
}

int Heap::right(int i){
  return 2*(i+1);
}

void Heap::swap(int a, int b){
  Element temp;
  temp = tab[a];
  tab[a] = tab[b];
  tab[b] = temp;
}

void Heap::minHeapify(int i){
  int l = left(i);
  int r = right(i);
  int min = i;

  if (l < numberOfElements){
    if (tab[l].getPriority() < tab[min].getPriority())
        min = l;
  }

  if (r < numberOfElements){
    if (tab[r].getPriority() < tab[min].getPriority())
      min = r;
  }

  if (min != i){
    swap(i, min);
    minHeapify(min);
  }
}

void Heap::buildMinHeap(int n){
  for (int i = (n/2)-1; i >= 0; i--)
    minHeapify(i);
}
