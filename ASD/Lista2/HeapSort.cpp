//
//  HeapSort.cpp
//  AlgorytmySortujace
//
//  Created by Mikis Dukiel on 07/04/2019.
//  Copyright © 2019 Mikis Dukiel. All rights reserved.
//

#include "algorytmy.h"
#include "funkcjePomocnicze.h"
#include "HeapSort.h"
#include <cstdio>
#include <ctime>
#include <iostream>

statystyki heapSort(int n, int * tablica, bool asc, statystyki Statystyki, bool podsumowanie){
    // zmienne zliczające kolejno: porównania, przestawienia, czas rozpoczęcia, czas zakończenia
    Statystyki.porownania = 0;
    Statystyki.przestawienia = 0;
    clock_t start, stop, startP, stopP;
    
    // kopiowanie tablicy w celu zrobienia algorytmu bez wypisywania
    int nCzas = n;
    int * kopia_tablicy = new int[n];
    for (int i = 0; i < n; i++)
        kopia_tablicy[i] = tablica[i];
    
    // mierzenie czasu dla kopii algorytmu (rozróżnienia na wersję asc i desc)
    if (asc){
        start = clock();
        buildMaxHeapCzas(nCzas, kopia_tablicy);
        for (int i = (nCzas-1); i > 0; i--){
            zamien(0, i, kopia_tablicy);
            maxHeapifyCzas(kopia_tablicy, 0, --nCzas);
        }
        stop = clock();
    }
    else{
        start = clock();
        buildMinHeapCzas(nCzas, kopia_tablicy);
        for (int i = (nCzas-1); i > 0; i--){
            zamien(0, i, kopia_tablicy);
            minHeapifyCzas(kopia_tablicy, 0, --nCzas);
        }
        stop = clock();
    }
    
    // właściwa część algorytmu
    if (asc){
        startP = clock();
        Statystyki.operator=(buildMaxHeap(n, tablica, Statystyki));
        for (int i = (n-1); i > 0; i--){
            Statystyki.przestawienia = przestawienie(Statystyki.przestawienia, tablica[i], "na początek tablicy");
            zamien(0, i, tablica);
            Statystyki.operator=(maxHeapify(tablica, 0, --n, Statystyki));
        }
        stopP = clock();
    }
    else{
        startP = clock();
        Statystyki.operator=(buildMinHeap(n, tablica, Statystyki));
        for (int i = (n-1); i > 0; i--){
            Statystyki.przestawienia = przestawienie(Statystyki.przestawienia, tablica[i], "na początek tablicy");
            zamien(0, i, tablica);
            Statystyki.operator=(minHeapify(tablica, 0, --n, Statystyki));
        }
        stopP = clock();
    }
    
    Statystyki.czas = stop - start;
    Statystyki.czasPraktyczny = stopP - startP;
    
    if (podsumowanie)
        std::cerr << "\nHeapSort:\nLiczba porównań: " << Statystyki.porownania << "\nLiczba przestawień: " << Statystyki.przestawienia << "\nCzas trwania: " << Statystyki.czas << " ms" << "\nCzas trwania praktyczny: " << Statystyki.czasPraktyczny << " ms\n\n";
    
    return Statystyki;
}

statystyki buildMaxHeap(int n, int * tablica, statystyki Statystyki){
    int rozmiarKopca = n;
    for (int i = (n/2)-1; i >= 0; i--)
        Statystyki.operator=(maxHeapify(tablica, i, rozmiarKopca, Statystyki));
    return Statystyki;
}

statystyki buildMinHeap(int n, int * tablica, statystyki Statystyki){
    int rozmiarKopca = n;
    for (int i = (n/2)-1; i >= 0; i--)
        Statystyki.operator=(minHeapify(tablica, i, rozmiarKopca, Statystyki));
    return Statystyki;
}

statystyki maxHeapify(int * tablica, int i, int rozmiarKopca, statystyki Statystyki){
    int l = lewySyn(i);
    int p = prawySyn(i);
    int najwiekszy = i;
    
    Statystyki.porownania = porownanie(Statystyki.porownania, l, rozmiarKopca, '>', "rozmiar kopca");
    if (l < rozmiarKopca){
        Statystyki.porownania = porownanie(Statystyki.porownania, tablica[l], tablica[i], '>');
        if (tablica[l] > tablica[i])
            najwiekszy = l;
    }
    
    Statystyki.porownania = porownanie(Statystyki.porownania, p, rozmiarKopca, '>', "rozmiar kopca");
    if (p < rozmiarKopca){
        Statystyki.porownania = porownanie(Statystyki.porownania, tablica[p], tablica[najwiekszy], '>');
        if (tablica[p] > tablica[najwiekszy])
            najwiekszy = p;
    }
    
    Statystyki.porownania = porownanie(Statystyki.porownania, najwiekszy, i, '=', "czy ojciec był największy");
    if (najwiekszy != i){
        Statystyki.przestawienia = przestawienie(Statystyki.przestawienia, tablica[i], tablica[najwiekszy]);
        zamien(i, najwiekszy, tablica);
        Statystyki.operator=(maxHeapify(tablica, najwiekszy, rozmiarKopca, Statystyki));
    }
    
    return Statystyki;
}

statystyki minHeapify(int * tablica, int i, int rozmiarKopca, statystyki Statystyki){
    int l = lewySyn(i);
    int p = prawySyn(i);
    int najmniejszy = i;
    
    Statystyki.porownania = porownanie(Statystyki.porownania, l, rozmiarKopca, '>', "rozmiar kopca");
    if (l < rozmiarKopca){
        Statystyki.porownania = porownanie(Statystyki.porownania, tablica[l], tablica[i], '<');
        if (tablica[l] < tablica[i])
            najmniejszy = l;
    }
    
    Statystyki.porownania = porownanie(Statystyki.porownania, p, rozmiarKopca, '>', "rozmiar kopca");
    if (p < rozmiarKopca){
        Statystyki.porownania = porownanie(Statystyki.porownania, tablica[p], tablica[najmniejszy], '<');
        if (tablica[p] < tablica[najmniejszy])
            najmniejszy = p;
    }
    
    Statystyki.porownania = porownanie(Statystyki.porownania, najmniejszy, i, '=', "czy ojciec był najmniejszy");
    if (najmniejszy != i){
        Statystyki.przestawienia = przestawienie(Statystyki.przestawienia, tablica[i], tablica[najmniejszy]);
        zamien(i, najmniejszy, tablica);
        Statystyki.operator=(minHeapify(tablica, najmniejszy, rozmiarKopca, Statystyki));
    }
    
    return Statystyki;
}

void buildMaxHeapCzas(int n, int * tablica){
    int rozmiarKopca = n;
    for (int i = (n/2)-1; i >= 0; i--)
        maxHeapifyCzas(tablica, i, rozmiarKopca);
}

void buildMinHeapCzas(int n, int * tablica){
    int rozmiarKopca = n;
    for (int i = (n/2)-1; i >= 0; i--)
        minHeapifyCzas(tablica, i, rozmiarKopca);
}

void maxHeapifyCzas(int * tablica, int i, int rozmiarKopca){
    int l = lewySyn(i);
    int p = prawySyn(i);
    int najwiekszy = i;
    
    if (l < rozmiarKopca){
        if (tablica[l] > tablica[i])
            najwiekszy = l;
    }
    
    if (p < rozmiarKopca){
        if (tablica[p] > tablica[najwiekszy])
            najwiekszy = p;
    }
    
    if (najwiekszy != i){
        zamien(i, najwiekszy, tablica);
        maxHeapifyCzas(tablica, najwiekszy, rozmiarKopca);
    }
}

void minHeapifyCzas(int * tablica, int i, int rozmiarKopca){
    int l = lewySyn(i);
    int p = prawySyn(i);
    int najmniejszy = i;
    
    if (l < rozmiarKopca){
        if (tablica[l] < tablica[i])
            najmniejszy = l;
    }
    
    if (p < rozmiarKopca){
        if (tablica[p] < tablica[najmniejszy])
            najmniejszy = p;
    }
    
    if (najmniejszy != i){
        zamien(i, najmniejszy, tablica);
        minHeapifyCzas(tablica, najmniejszy, rozmiarKopca);
    }
}

int ojciec(int i){
    return i/2;
}

int lewySyn(int i){
    return 2*(i+1)-1;
}

int prawySyn(int i){
    return 2*(i+1);
}
