//
//  InsertSort.h
//  AlgorytmySortujace
//
//  Created by Mikis Dukiel on 07/04/2019.
//  Copyright © 2019 Mikis Dukiel. All rights reserved.
//

#ifndef InsertSort_h
#define InsertSort_h

#include "funkcjePomocnicze.h"

statystyki insertSort(int n, int * tablica, bool asc, statystyki Statystyki, bool podsumowanie);
void insertSortCzasAsc(int n, int * tablica, int * kopia_tablicy_czas);
void insertSortCzasDesc(int n, int * tablica, int * kopia_tablicy_czas);

#endif /* InsertSort_h */
