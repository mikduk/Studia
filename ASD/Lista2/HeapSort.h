//
//  HeapSort.h
//  AlgorytmySortujace
//
//  Created by Mikis Dukiel on 07/04/2019.
//  Copyright © 2019 Mikis Dukiel. All rights reserved.
//

#ifndef HeapSort_h
#define HeapSort_h

#include "funkcjePomocnicze.h"

// pomocnicze funkcje organizacyjne
int ojciec(int i);
int lewySyn(int i);
int prawySyn(int i);

// pomocnicze funkcje potrzebne do wersji asc
statystyki maxHeapify(int * tablica, int i, int rozmiarKopca, statystyki Statystyki);
statystyki minHeapify(int * tablica, int i, int rozmiarKopca, statystyki Statystyki);

// pomocnicze funkcje potrzebne do wersji desc
statystyki buildMaxHeap(int n, int * tablica, statystyki Statystyki);
statystyki buildMinHeap(int n, int * tablica, statystyki Statystyki);

// pomocnicze funkcje potrzebne do zmierzenia czasu
void maxHeapifyCzas(int * tablica, int i, int rozmiarKopca);
void minHeapifyCzas(int * tablica, int i, int rozmiarKopca);
void buildMaxHeapCzas(int n, int * tablica);
void buildMinHeapCzas(int n, int * tablica);

// algorytm
statystyki heapSort(int n, int * tablica, bool asc, statystyki Statystyki, bool podsumowanie);

#endif /* HeapSort_h */
