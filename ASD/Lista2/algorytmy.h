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

statystyki selectSort(int n, int * tablica, bool asc, statystyki Statystyki, bool podsumowanie, bool pokaz);
statystyki insertSort(int n, int * tablica, bool asc, statystyki Statystyki, bool podsumowanie, bool pokaz);
statystyki quickSort(int n, int * tablica, bool asc, statystyki Statystyki, bool podsumowanie, bool pokaz);
statystyki quickSortModyfikacja(int n, int * tablica, bool asc, statystyki Statystyki, bool podsumowanie, bool pokaz);
statystyki heapSort(int n, int * tablica, bool asc, statystyki Statystyki, bool podsumowanie, bool pokaz);

#endif /* algorytmy_h */
