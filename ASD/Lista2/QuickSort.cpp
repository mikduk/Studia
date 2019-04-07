//
//  QuickSort.cpp
//  AlgorytmySortujace
//
//  Created by Mikis Dukiel on 01/04/2019.
//  Copyright © 2019 Mikis Dukiel. All rights reserved.
//

#include "algorytmy.h"
#include "funkcjePomocnicze.h"
#include "QuickSort.h"
#include <iostream>
#include <cstdio>
#include <ctime>
#include <queue>
#include <stack>

using namespace std;

statystyki quickSort(int n, int * tablica, bool asc, statystyki Statystyki, bool podsumowanie){
    
    // zmienne zliczające kolejno: porównania, przestawienia, czas rozpoczęcia, czas zakończenia
    Statystyki.porownania = 0;
    Statystyki.przestawienia = 0;
    clock_t start, stop, startP, stopP;
    
    // kopiowanie tablicy w celu zrobienia algorytmu bez wypisywania
    int * kopia_tablicy = new int[n];
    for (int i = 0; i < n; i++)
        kopia_tablicy[i] = tablica[i];
    
    // mierzenie czasu dla kopii algorytmu (rozróżnienia na wersję asc i desc)
    if (asc){
        start = clock();
        quickSortCzasAsc(n, kopia_tablicy);
        stop = clock();
    }
    else{
        start = clock();
        quickSortCzasDesc(n, kopia_tablicy);
        stop = clock();
    }
    
    // właściwa część algorytmu
    startP = clock();
    Statystyki.operator=(quickSortAlgorytm(n, tablica, asc, Statystyki));
    stopP = clock();
    
    Statystyki.czas = stop - start;
    Statystyki.czasPraktyczny = stopP - startP;
    
    if (podsumowanie)
    cerr << "\nQuickSort:\nLiczba porównań: " << Statystyki.porownania << "\nLiczba przestawień: " << Statystyki.przestawienia << "\nCzas trwania: " << Statystyki.czas << " ms" << "\nCzas trwania praktyczny: " << Statystyki.czasPraktyczny << " ms\n" << endl;
    
    return Statystyki;
}

statystyki quickSortAlgorytm(int n, int * tablica, bool asc, statystyki Statystyki){
    
    // deklaracja pivota (środek nieposortowanej tablicy) oraz części do podziału (wersje asc i desc)
    int pivot = tablica[n/2];
    queue <int> mniejsze;
    queue <int> rowne;
    queue <int> wieksze;
    
    // podział na trzy tablice względem pivota
    for (int i=0; i<n; i++){
        Statystyki.porownania = porownanie(Statystyki.porownania, tablica[i], pivot, 'z');
        if (tablica[i] < pivot) {
            mniejsze.push(tablica[i]);
            Statystyki.przestawienia = przestawienie(Statystyki.przestawienia, tablica[i], "do mniejszych od pivota");
        }
        else if (tablica[i] == pivot) {
            rowne.push(tablica[i]);
            Statystyki.przestawienia = przestawienie(Statystyki.przestawienia, tablica[i], "do równych pivotowi");
        }
        else {
            wieksze.push(tablica[i]);
            Statystyki.przestawienia = przestawienie(Statystyki.przestawienia, tablica[i], "do większych od pivota");
        }
    }
    
    // sortowanie części z elementami mniejszymi od pivota
    if (mniejsze.size() > 1){
        int size = (int) mniejsze.size();
        int * tabMniejsze = new int[size];
        for (int i=0; i<size; i++){
            tabMniejsze[i] = mniejsze.front();
            mniejsze.pop();
        }
        Statystyki.operator=(quickSortAlgorytm(size, tabMniejsze, asc, Statystyki));
        for (int i=0; i<size; i++){
            mniejsze.push(tabMniejsze[i]);
        }
    }
    
    // sortowanie części z elementami większymi od pivota
    if (wieksze.size() > 1){
        int size = (int) wieksze.size();
        int * tabWieksze = new int[size];
        for (int i=0; i<size; i++){
            tabWieksze[i] = wieksze.front();
            wieksze.pop();
        }
        Statystyki.operator=(quickSortAlgorytm(size, tabWieksze, asc, Statystyki));
        for (int i=0; i<size; i++){
            wieksze.push(tabWieksze[i]);
        }
    }
    
    // łączenie tablic (przypadek asc i desc)
    int i = 0;
    if (asc){
        
        while (!mniejsze.empty()){
            tablica[i] = mniejsze.front();
            mniejsze.pop();
            i++;
        }
        
        while (!rowne.empty()){
            tablica[i] = rowne.front();
            rowne.pop();
            i++;
        }
        
        while (!wieksze.empty()){
            tablica[i] = wieksze.front();
            wieksze.pop();
            i++;
        }
    }
    else{
        
        while (!wieksze.empty()){
            tablica[i] = wieksze.front();
            wieksze.pop();
            i++;
        }
        
        while (!rowne.empty()){
            tablica[i] = rowne.front();
            rowne.pop();
            i++;
        }
        
        while (!mniejsze.empty()){
            tablica[i] = mniejsze.front();
            mniejsze.pop();
            i++;
        }
    }
    return Statystyki;
}

void quickSortCzasAsc(int n, int * tablica){
    
    int pivot = tablica[n/2];
    queue <int> mniejsze;
    queue <int> rowne;
    queue <int> wieksze;
    
    for (int i=0; i<n; i++){
        if (tablica[i] < pivot) mniejsze.push(tablica[i]);
        else if (tablica[i] == pivot) rowne.push(tablica[i]);
        else wieksze.push(tablica[i]);
    }
    
    if (mniejsze.size() > 1){
        
        int size = (int) mniejsze.size();
        int * tabMniejsze = new int[size];
        
        for (int i=0; i<size; i++){
            tabMniejsze[i] = mniejsze.front();
            mniejsze.pop();
        }
        
        quickSortCzasAsc(size, tabMniejsze);
        
        for (int i=0; i<size; i++)
            mniejsze.push(tabMniejsze[i]);
    }
    
    if (wieksze.size() > 1){
        
        int size = (int) wieksze.size();
        int * tabWieksze = new int[size];
        
        for (int i=0; i<size; i++){
            tabWieksze[i] = wieksze.front();
            wieksze.pop();
        }
        
        quickSortCzasAsc(size, tabWieksze);
        
        for (int i=0; i<size; i++)
            wieksze.push(tabWieksze[i]);
        
    }
    
    // łączenie tablic
    int i = 0;
    
    while (!mniejsze.empty()){
        tablica[i] = mniejsze.front();
        mniejsze.pop();
        i++;
    }
    
    while (!rowne.empty()){
        tablica[i] = rowne.front();
        rowne.pop();
        i++;
    }
    
    while (!wieksze.empty()){
        tablica[i] = wieksze.front();
        wieksze.pop();
        i++;
    }
}

void quickSortCzasDesc(int n, int * tablica){
    
    int pivot = tablica[n/2];
    queue <int> mniejsze;
    queue <int> rowne;
    queue <int> wieksze;
    
    // podział na trzy tablice względem pivota
    for (int i=0; i<n; i++){
        if (tablica[i] < pivot) mniejsze.push(tablica[i]);
        else if (tablica[i] == pivot) rowne.push(tablica[i]);
        else wieksze.push(tablica[i]);
    }
    
    if (mniejsze.size() > 1){
        int size = (int) mniejsze.size();
        int * tabMniejsze = new int[size];
        
        for (int i=0; i<size; i++){
            tabMniejsze[i] = mniejsze.front();
            mniejsze.pop();
        }
        quickSortCzasDesc(size, tabMniejsze);
        for (int i=0; i<size; i++)
            mniejsze.push(tabMniejsze[i]);
    }
    
    if (wieksze.size() > 1){
        int size = (int) wieksze.size();
        int * tabWieksze = new int[size];
        
        for (int i=0; i<size; i++){
            tabWieksze[i] = wieksze.front();
            wieksze.pop();
        }
        quickSortCzasDesc(size, tabWieksze);
        for (int i=0; i<size; i++)
            wieksze.push(tabWieksze[i]);
    }
    
    // łączenie tablic
    int i = 0;
    
    while (!wieksze.empty()){
        tablica[i] = wieksze.front();
        wieksze.pop();
        i++;
    }
    
    while (!rowne.empty()){
        tablica[i] = rowne.front();
        rowne.pop();
        i++;
    }
    
    while (!mniejsze.empty()){
        tablica[i] = mniejsze.front();
        mniejsze.pop();
        i++;
    }
}

