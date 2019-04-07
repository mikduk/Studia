//
//  QuickSort.h
//  AlgorytmySortujace
//
//  Created by Mikis Dukiel on 01/04/2019.
//  Copyright © 2019 Mikis Dukiel. All rights reserved.
//

#ifndef QuickSort_h
#define QuickSort_h

#include "funkcjePomocnicze.h"

// funkcje z pliku QuickSort.cpp
statystyki quickSort(int n, int * tablica, bool asc, statystyki Statystyki, bool podsumowanie);
statystyki quickSortAlgorytm(int n, int * tablica, bool asc, statystyki Statystyki);
void quickSortCzasAsc(int n, int * tablica);
void quickSortCzasDesc(int n, int * tablica);

// funkcje z pliku QuickSortModyfikacja.cpp
statystyki quickSortModyfikacja(int n, int * tablica, bool asc, statystyki Statystyki, bool podsumowanie);
statystyki quickSortModyfikacjaAlgorytm(int n, int * tablica, bool asc, statystyki Statystyki);
void quickSortModyfikacjaCzasAsc(int n, int * tablica);
void quickSortModyfikacjaCzasDesc(int n, int * tablica);

#endif /* QuickSort_h */
