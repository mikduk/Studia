//
//  QuickSortModyfikacja.cpp
//  AlgorytmySortujace
//
//  Created by Mikis Dukiel on 06/04/2019.
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

statystyki quickSortModyfikacja(int n, int * tablica, bool asc, statystyki Statystyki, bool podsumowanie, bool pokaz){ 

    // zmienne zliczające kolejno: czas rozpoczęcia, czas zakończenia
    clock_t start, stop, startP, stopP;
    
    // kopiowanie tablicy w celu zrobienia algorytmu bez wypisywania
    int * kopia_tablicy = new int[n];
    for (int i = 0; i < n; i++)
        kopia_tablicy[i] = tablica[i];
    
    // mierzenie czasu dla kopii algorytmu (rozróżnienia na wersję asc i desc)
    /*if (asc){
        start = clock(); 
        quickSortModyfikacjaCzasAsc(n, kopia_tablicy); 
        stop = clock();
    }
    else{
        start = clock();
        quickSortModyfikacjaCzasDesc(n, kopia_tablicy);
        stop = clock();
    }*/

    // właściwa część algorytmu
    startP = clock();
    Statystyki.operator=(quickSortModyfikacjaAlgorytm(n, tablica, asc, Statystyki, pokaz));
    stopP = clock();
    
    //Statystyki.czas = stop - start;
    Statystyki.czasPraktyczny = stopP - startP;
    
    if (podsumowanie)
    cerr << "\nquickSortModyfikacja:\nLiczba porównań: " << Statystyki.porownania << "\nLiczba przestawień: " << Statystyki.przestawienia << "\nCzas trwania: " << Statystyki.czas << " ms" << "\nCzas trwania praktyczny: " << Statystyki.czasPraktyczny << " ms\n" << endl;
    
    return Statystyki;
}

statystyki quickSortModyfikacjaAlgorytm(int n, int * tablica, bool asc, statystyki Statystyki, bool pokaz){
    
    if (n > 16){
        
        // deklaracja pivota (mediana z pierwszego, środkowego i ostatniego elementu tablicy)
        int pivot;
        int potencjalnePivoty[3] = {tablica[0], tablica[n/2], tablica[n-1]};
        Statystyki.operator=(insertSort(3, potencjalnePivoty, true, Statystyki, false, pokaz));
        pivot = potencjalnePivoty[1];
        
        // deklaracja części do dzielenia tablicy
        queue <int> mniejsze;
        queue <int> rowne;
        queue <int> wieksze;
    
        // podział na trzy tablice względem pivota
        for (int i=0; i<n; i++){
            Statystyki.porownania = porownanie(pokaz, Statystyki.porownania, tablica[i], pivot, 'z');
            if (tablica[i] < pivot) {
                mniejsze.push(tablica[i]);
                Statystyki.przestawienia = przestawienie(pokaz, Statystyki.przestawienia, tablica[i], "do mniejszych od pivota");
            }
            else if (tablica[i] == pivot) {
                rowne.push(tablica[i]);
                Statystyki.przestawienia = przestawienie(pokaz, Statystyki.przestawienia, tablica[i], "do równych pivotowi");
            }
            else {
                wieksze.push(tablica[i]);
                Statystyki.przestawienia = przestawienie(pokaz, Statystyki.przestawienia, tablica[i], "do większych od pivota");
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
            Statystyki.operator=(quickSortModyfikacjaAlgorytm(size, tabMniejsze, asc, Statystyki, pokaz));
            for (int i=0; i<size; i++){
                mniejsze.push(tabMniejsze[i]);
            }
            free(tabMniejsze);		
        }
    
        // sortowanie części z elementami większymi od pivota
        if (wieksze.size() > 1){
            int size = (int) wieksze.size();
            int * tabWieksze = new int[size];
            for (int i=0; i<size; i++){
                tabWieksze[i] = wieksze.front();
                wieksze.pop();
            }
            Statystyki.operator=(quickSortModyfikacjaAlgorytm(size, tabWieksze, asc, Statystyki, pokaz));
            for (int i=0; i<size; i++){
                wieksze.push(tabWieksze[i]);
            }
            free(tabWieksze);
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
    }
    
    else{ 

	int * kopia_tablicy = new int[n];

	for (int i = 0; i < n; i++)
	        kopia_tablicy[i] = tablica[i];

	if (asc){
	        for (int i = 1; i < n; i++){
	            bool maximum = true;
	            for (int j = 0; j < i; j++){
	                Statystyki.porownania = porownanie(pokaz, Statystyki.porownania, tablica[i], kopia_tablicy[j], '<');
	                if (tablica[i] < kopia_tablicy[j]){
	                    Statystyki.przestawienia = wstawIPrzestaw(pokaz, tablica[i], j, n, kopia_tablicy, Statystyki.przestawienia);
	                    maximum = false;
	                    break;
	                }
	            }
	            if (maximum)
	                Statystyki.przestawienia = wstawIPrzestaw(pokaz, tablica[i], i, n, kopia_tablicy, Statystyki.przestawienia);
	        }
	    }
	    else{
	        for (int i = 1; i < n; i++){
	            bool maximum = true;
	            for (int j = 0; j < i; j++){
	                Statystyki.porownania = porownanie(pokaz, Statystyki.porownania, tablica[i], kopia_tablicy[j], '>');
	                if (tablica[i] > kopia_tablicy[j]){
	                    Statystyki.przestawienia = wstawIPrzestaw(pokaz, tablica[i], j, n, kopia_tablicy, Statystyki.przestawienia);
	                    maximum = false;
	                    break;
	                }
	            }
	            if (maximum)
	                Statystyki.przestawienia = wstawIPrzestaw(pokaz, tablica[i], i, n, kopia_tablicy, Statystyki.przestawienia);
	        }
	    }
    
	    for (int i = 0; i < n; i++)
	       tablica[i] = kopia_tablicy[i];
	    }
    
	    return Statystyki;
}

void quickSortModyfikacjaCzasAsc(int n, int * tablica){
    
    if (n > 16){
    
        int pivot;
        int potencjalnePivoty[3] = {tablica[0], tablica[n/2], tablica[n-1]};
        int kopia_tablicy_czas[3] = {tablica[0], tablica[n/2], tablica[n-1]};
        insertSortCzasAsc(3, potencjalnePivoty, kopia_tablicy_czas);
        pivot = potencjalnePivoty[1];
        
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
        
            quickSortModyfikacjaCzasAsc(size, tabMniejsze);
        
            for (int i=0; i<size; i++)
                mniejsze.push(tabMniejsze[i]);
		
	free(tabMniejsze);
        }
    
        if (wieksze.size() > 1){
        
            int size = (int) wieksze.size();
            int * tabWieksze = new int[size];
        
            for (int i=0; i<size; i++){
                tabWieksze[i] = wieksze.front();
                wieksze.pop();
            }
        
            quickSortModyfikacjaCzasAsc(size, tabWieksze);
        
            for (int i=0; i<size; i++)
                wieksze.push(tabWieksze[i]);

	free(tabWieksze);
        
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
    
    else{ 

	int * kopia_tablicy = new int[n];

	for (int i = 0; i < n; i++)
	        kopia_tablicy[i] = tablica[i];
	
	        for (int i = 1; i < n; i++){
	            bool maximum = true;
	            for (int j = 0; j < i; j++){
	                
	                if (tablica[i] < kopia_tablicy[j]){
	                    wstawIPrzesun(tablica[i], j, n, kopia_tablicy);
	                    maximum = false;
	                    break;
	                }
	            }
	            if (maximum)
	                wstawIPrzesun(tablica[i], i, n, kopia_tablicy);
	        }
	    
    
	    for (int i = 0; i < n; i++)
	       tablica[i] = kopia_tablicy[i];
	free(kopia_tablicy);	
	    }	
}

void quickSortModyfikacjaCzasDesc(int n, int * tablica){
    
    if (n > 16){
    
        int pivot;
        int potencjalnePivoty[3] = {tablica[0], tablica[n/2], tablica[n-1]};
        int kopia_tablicy_czas[3] = {tablica[0], tablica[n/2], tablica[n-1]};
        insertSortCzasDesc(3, potencjalnePivoty, kopia_tablicy_czas);
        pivot = potencjalnePivoty[1];
    
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
            quickSortModyfikacjaCzasDesc(size, tabMniejsze);
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
            quickSortModyfikacjaCzasDesc(size, tabWieksze);
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
    else{ 

	int * kopia_tablicy = new int[n];

	for (int i = 0; i < n; i++)
	        kopia_tablicy[i] = tablica[i];
  
	        for (int i = 1; i < n; i++){
	            bool maximum = true;
	            for (int j = 0; j < i; j++){
	             
	                if (tablica[i] > kopia_tablicy[j]){
	                    wstawIPrzesun(tablica[i], j, n, kopia_tablicy);
	                    maximum = false;
	                    break;
	                }
	            }
	            if (maximum)
	                wstawIPrzesun(tablica[i], i, n, kopia_tablicy);
	        }
    
	    for (int i = 0; i < n; i++)
	       tablica[i] = kopia_tablicy[i];
	    }
}
