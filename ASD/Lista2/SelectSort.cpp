//
//  SelectSort.cpp
//  Lista2
//
//  Created by Mikis Dukiel on 12/03/2019.
//  Copyright © 2019 Mikis Dukiel. All rights reserved.
//

#include "algorytmy.h"
#include "funkcjePomocnicze.h"
#include <iostream>
#include <cstdio>
#include <ctime>

using namespace std;

statystyki selectSort(int n, int * tablica, bool asc, statystyki Statystyki, bool podsumowanie){
    
    // zmienne zliczające kolejno: porównania, przestawienia, czas rozpoczęcia, czas zakończenia
    int porownania = Statystyki.porownania, przestawienia = Statystyki.przestawienia;
    clock_t start, stop, startP, stopP;
    
    // kopiowanie tablicy w celu zrobienia algorytmu bez wypisywania
    int * kopia_tablicy = new int[n];
    for (int i = 0; i < n; i++)
        kopia_tablicy[i] = tablica[i];
   
    // mierzenie czasu dla kopii algorytmu (rozróżnienia na wersję asc i desc)
    if (asc){
        start = clock();
        for (int i=0, k=n-1; i<k; i++, k--){
            
            int temp = kopia_tablicy[i],
                temp2 = kopia_tablicy[k],
                min = kopia_tablicy[i],
                min_index = i,
                max = kopia_tablicy[i],
                max_index = i;
        
            for (int j=i+1; j<=k; j++){
                
                if (min > kopia_tablicy[j]){
                    min = kopia_tablicy[j];
                    min_index = j;
                }
                
                if (max < kopia_tablicy[j]){
                    max = kopia_tablicy[j];
                    max_index = j;
                }
            }
        
            kopia_tablicy[i] = min;
            kopia_tablicy[min_index] = temp;
        
            kopia_tablicy[k] = max;
            kopia_tablicy[max_index] = temp2;
        }
        stop = clock();
    }
    else{
        start = clock();
        for (int i=0, k=n-1; i<k; i++, k--){
            
            int temp = kopia_tablicy[i],
                temp2 = kopia_tablicy[k],
                min = kopia_tablicy[i],
                min_index = i,
                max = kopia_tablicy[i],
                max_index = i;
            
            for (int j=i+1; j<=k; j++){
                if (min > kopia_tablicy[j]){
                    min = kopia_tablicy[j];
                    min_index = j;
                }
                
                if (max < kopia_tablicy[j]){
                    max = kopia_tablicy[j];
                    max_index = j;
                }
            }
            
            kopia_tablicy[i] = max;
            kopia_tablicy[min_index] = temp2;
            
            kopia_tablicy[k] = min;
            kopia_tablicy[max_index] = temp;
        }
        stop = clock();
    }
    
    // właściwa część algorytmu SelectSort
    startP = clock();
    for (int i=0, k=n-1; i<k; i++, k--){
        
        int temp = tablica[i],
            temp2 = tablica[k],
            min = tablica[i],
            min_index = i,
            max = tablica[i],
            max_index = i;
        
        for (int j=i+1; j<=k; j++){
            
            cerr << "(" << ++porownania << ") Porównuję: min(" << min << ") > " << tablica[j] << endl;
            if (min > tablica[j]){
                min = tablica[j];
                min_index = j;
            }
            
            cerr << "(" << ++porownania << ") Porównuję: max(" << max << ") < " << tablica[j] << endl;
            if (max < tablica[j]){
                max = tablica[j];
                max_index = j;
            }
        }
        
        if (asc){
            cerr << "(" << ++przestawienia << ") Przestawiam: " << tablica[i] << " z min(" << min << ")\n";
            tablica[i] = min;
            tablica[min_index] = temp;
            
            cerr << "(" << ++przestawienia << ") Przestawiam: " << tablica[k] << " z max(" << max << ")\n";
            tablica[k] = max;
            tablica[max_index] = temp2;
        }
        else{
            cerr << "(" << ++przestawienia << ") Przestawiam: " << tablica[i] << " z max(" << max << ")\n";
            tablica[i] = max;
            tablica[min_index] = temp2;
            cerr << "(" << ++przestawienia << ") Przestawiam: " << tablica[k] << " z min(" << min << ")\n";
            tablica[k] = min;
            tablica[max_index] = temp;
        }
            
    }
    stopP = clock();
    if (podsumowanie)
    cerr << "\nSelectSort:\nLiczba porównań: " << porownania << "\nLiczba przestawień: " << przestawienia << "\nCzas trwania: " << stop - start << " ms" << "\nCzas trwania praktyczny: " << stopP - startP << " ms\n" << endl;
    
    Statystyki.porownania = porownania;
    Statystyki.przestawienia = przestawienia;
    Statystyki.czas = stop - start;
    Statystyki.czasPraktyczny = stopP - startP;
    
    return Statystyki;
}
