//
//  InsertSort.cpp
//  Lista2
//
//  Created by Mikis Dukiel on 25/03/2019.
//  Copyright © 2019 Mikis Dukiel. All rights reserved.
//

#include "algorytmy.h"
#include "funkcjePomocnicze.h"
#include "InsertSort.h"
#include <iostream>
#include <cstdio>
#include <ctime>

using namespace std;

statystyki insertSort(int n, int * tablica, bool asc, statystyki Statystyki, bool podsumowanie, bool pokaz){
    
    // kopiowanie tablicy
    int * kopia_tablicy = new int[n];

    for (int i = 0; i < n; i++){
        kopia_tablicy[i] = tablica[i];
    }
    
    // zmienne zliczające kolejno: porównania, przestawienia, czas rozpoczęcia, czas zakończenia
    int porownania = Statystyki.porownania, przestawienia = Statystyki.przestawienia;
    clock_t start, stop, startP, stopP;
    
    // mierzenie czasu dla kopii algorytmu (rozróżnienia na wersję asc i desc) 
    if (asc){ 
        start = clock();
        insertSortCzasAsc(n, tablica, kopia_tablicy);
        stop = clock();
    }
    else{
        start = clock();
        insertSortCzasDesc(n, tablica, kopia_tablicy);
        stop = clock();
    }

    for (int i = 0; i < n; i++){
        kopia_tablicy[i] = tablica[i];
    }
    
    // właściwa część algorytmu SelectSort
    startP = clock();
    if (asc){
        for (int i = 1; i < n; i++){
            bool maximum = true;
            for (int j = 0; j < i; j++){
                porownania = porownanie(pokaz, porownania, tablica[i], kopia_tablicy[j], '<');
                if (tablica[i] < kopia_tablicy[j]){
                    przestawienia = wstawIPrzestaw(pokaz, tablica[i], j, n, kopia_tablicy, przestawienia);
                    maximum = false;
                    break;
                }
            }
            if (maximum)
                przestawienia = wstawIPrzestaw(pokaz, tablica[i], i, n, kopia_tablicy, przestawienia);
        }
    }
    else{
        for (int i = 1; i < n; i++){
            bool maximum = true;
            for (int j = 0; j < i; j++){
                porownania = porownanie(pokaz, porownania, tablica[i], kopia_tablicy[j], '>');
                if (tablica[i] > kopia_tablicy[j]){
                    przestawienia = wstawIPrzestaw(pokaz, tablica[i], j, n, kopia_tablicy, przestawienia);
                    maximum = false;
                    break;
                }
            }
            if (maximum)
                przestawienia = wstawIPrzestaw(pokaz, tablica[i], i, n, kopia_tablicy, przestawienia);
        }
    }
    
    for (int i = 0; i < n; i++)
       tablica[i] = kopia_tablicy[i];
    
    stopP = clock();
    if (podsumowanie)
    cerr << "\nInsertSort:\nLiczba porównań: " << porownania << "\nLiczba przestawień: " << przestawienia << "\nCzas trwania: " << stop - start << " ms" << "\nCzas trwania praktyczny: " << stopP - startP << " ms\n" << endl;
    
    Statystyki.porownania = porownania;
    Statystyki.przestawienia = przestawienia;
    Statystyki.czas = stop - start;
    Statystyki.czasPraktyczny = stopP - startP;
    
    return Statystyki;
}

void insertSortCzasAsc(int n, int * tablica, int * kopia_tablicy_czas){

        for (int i = 1; i < n; i++){
            bool maximum = true;
            for (int j = 0; j < i; j++)
                if (tablica[i] < kopia_tablicy_czas[j]){
                    wstawIPrzesun(tablica[i], j, n, kopia_tablicy_czas);
                    maximum = false;
                    break;
                }
            if (maximum)
                wstawIPrzesun(tablica[i], i, n, kopia_tablicy_czas);
        }
}

void insertSortCzasDesc(int n, int * tablica, int * kopia_tablicy_czas){
    
    for (int i = 1; i < n; i++){
        bool maximum = true;
        for (int j = 0; j < i; j++)
            if (tablica[i] > kopia_tablicy_czas[j]){
                wstawIPrzesun(tablica[i], j, n, kopia_tablicy_czas);
                maximum = false;
                break;
            }
        if (maximum)
            wstawIPrzesun(tablica[i], i, n, kopia_tablicy_czas);
    }
}
