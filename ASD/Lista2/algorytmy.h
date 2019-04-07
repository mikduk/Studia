//
//  algorytmy.h
//  Lista2
//
//  Created by Mikis Dukiel on 18/03/2019.
//  Copyright © 2019 Mikis Dukiel. All rights reserved.
//

#ifndef algorytmy_h
#define algorytmy_h

#include "InsertSort.h"
#include "QuickSort.h"
#include "HeapSort.h"

statystyki selectSort(int n, int * tablica, bool asc, statystyki Statystyki, bool podsumowanie);
statystyki insertSort(int n, int * tablica, bool asc, statystyki Statystyki, bool podsumowanie);
statystyki quickSort(int n, int * tablica, bool asc, statystyki Statystyki, bool podsumowanie);
statystyki quickSortModyfikacja(int n, int * tablica, bool asc, statystyki Statystyki, bool podsumowanie);
statystyki heapSort(int n, int * tablica, bool asc, statystyki Statystyki, bool podsumowanie);

#endif /* algorytmy_h */
