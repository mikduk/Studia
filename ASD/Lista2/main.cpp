//
//  main.cpp
//  AlgorytmySortujace
//
//  Created by Mikis Dukiel on 25/03/2019.
//  Copyright © 2019 Mikis Dukiel. All rights reserved.
//

#include "algorytmy.h"
#include <iostream>
#include <string.h>
#include <fstream>

using namespace std;

int main(int argc, const char * argv[]) {
  
    if (argc == 4){
        if (!strcmp(argv[1], "--type")){
            
            int n; cin >> n;
            int * tablica = new int[n];
            for (int i = 0; i < n; i++)
                cin >> tablica[i];
            
            statystyki Statystyki;
            Statystyki.porownania = 0;
            Statystyki.przestawienia = 0;
            Statystyki.czas = 0;
            Statystyki.czasPraktyczny = 0;
            
            if (!strcmp(argv[3], "--asc")){
                if (!strcmp(argv[2], "select")){
                    Statystyki.operator=(selectSort(n, tablica, true, Statystyki, true, true));
                    if (dobryPorzadek(n, tablica, true))
                        {cout << n << endl; pokazTablice(n, tablica);}
                }
                else if(!strcmp(argv[2], "insert")){
                    Statystyki.operator=(insertSort(n, tablica, true, Statystyki, true, true));
                    if (dobryPorzadek(n, tablica, true))
                        {cout << n << endl; pokazTablice(n, tablica);}
                }
                else if(!strcmp(argv[2], "heap")){
                    Statystyki.operator=(heapSort(n, tablica, true, Statystyki, true, true));
                    if (dobryPorzadek(n, tablica, true))
                        {cout << n << endl; pokazTablice(n, tablica);}
                }
                else if(!strcmp(argv[2], "quick")){
                    Statystyki.operator=(quickSort(n, tablica, true, Statystyki, true, true));
                    if (dobryPorzadek(n, tablica, true))
                        {cout << n << endl; pokazTablice(n, tablica);}
                }
                else if(!strcmp(argv[2], "mquick")){
                    Statystyki.operator=(quickSortModyfikacja(n, tablica, true, Statystyki, true, true));
                    if (dobryPorzadek(n, tablica, true))
                        {cout << n << endl; pokazTablice(n, tablica);}
                }
                else{
                    cout << "podano zły drugi parametr\n";
                }
            }
            else if(!strcmp(argv[3], "--desc")){
                if (!strcmp(argv[2], "select")){
                    Statystyki.operator=(selectSort(n, tablica, false, Statystyki, true, true));
                    if (dobryPorzadek(n, tablica, false))
                        {cout << n << endl; pokazTablice(n, tablica);}
                }
                else if(!strcmp(argv[2], "insert")){
                    Statystyki.operator=(insertSort(n, tablica, false, Statystyki, true, true));
                    if (dobryPorzadek(n, tablica, false))
                        {cout << n << endl; pokazTablice(n, tablica);}
                }
                else if(!strcmp(argv[2], "heap")){
                    Statystyki.operator=(heapSort(n, tablica, false, Statystyki, true, true));
                    if (dobryPorzadek(n, tablica, false))
                        {cout << n << endl; pokazTablice(n, tablica);}
                }
                else if(!strcmp(argv[2], "quick")){
                    Statystyki.operator=(quickSort(n, tablica, false, Statystyki, true, true));
                    if (dobryPorzadek(n, tablica, false))
                        {cout << n << endl; pokazTablice(n, tablica);}
                }
                else if(!strcmp(argv[2], "mquick")){
                    Statystyki.operator=(quickSortModyfikacja(n, tablica, false, Statystyki, true, true));
                    if (dobryPorzadek(n, tablica, false))
                        {cout << n << endl; pokazTablice(n, tablica);}
                }
                else{
                    cout << "podano zły drugi parametr\n";
                }
            }
            else{
                cout << "podano zły trzeci parametr\n";
            }
        }
        else if(!strcmp(argv[1], "--stat")){
            	int k = atoi(argv[3]);
		fstream fout;
		string nazwaAlgorytmu;
		fout.open(argv[2], ios::out);
		
		int tablica[10000];
		int kopia_tablicy[10000];

		for (int i = 100; i <= 1000; i += 100){
			statystyki Insert, Select, Heap, Quick, ModifiedQuick, Zero;
			Zero.porownania = 0;
			Zero.przestawienia = 0;
			Zero.czas = 0;
			Zero.czasPraktyczny = 0;
			Insert.operator=(Zero);
			Select.operator=(Zero);
			Heap.operator=(Zero);
			Quick.operator=(Zero);
			ModifiedQuick.operator=(Zero);
			
			for (int j = 0; j < k; j++){

				// generowanie tablicy
				for (int y = 0; y < i; y++)
					tablica[y] = ((rand()*20000) % 20000) - 10000;

				// InsertSort
	            		for (int u = 0; u < i; u++)
                			kopia_tablicy[u] = tablica[u];
				Insert.operator=(insertSort(i, kopia_tablicy, true, Insert, false, false));

				// SelectSort
				for (int u = 0; u < i; u++)
                			kopia_tablicy[u] = tablica[u];
				Select.operator=(selectSort(i, kopia_tablicy, true, Select, false, false));

				// HeapSort
				for (int u = 0; u < i; u++)
                			kopia_tablicy[u] = tablica[u];
				Heap.operator=(heapSort(i, kopia_tablicy, true, Heap, false, false));

				// QuickSort
				for (int u = 0; u < i; u++)
                			kopia_tablicy[u] = tablica[u];
				Quick.operator=(quickSort(i, kopia_tablicy, true, Quick, false, false));
			
				
				// QuickSortModyfikacja
				for (int u = 0; u < i; u++)
                			kopia_tablicy[u] = tablica[u];
				ModifiedQuick.operator=(quickSortModyfikacja(i, kopia_tablicy, true, ModifiedQuick, false, false));
						
			}
			fout << "i = " << i << endl;
			fout << "InsertSort: porownania = " << Insert.porownania/k << " | przestawienia = " << Insert.przestawienia/k << " | czas teoretyczny = " << Insert.czas/k << " ms | czas praktyczny = " << Insert.czasPraktyczny/k << " ms" << endl;
			fout << "SelectSort: porownania = " << Select.porownania/k << " | przestawienia = " << Select.przestawienia/k << " | czas teoretyczny = " << Select.czas/k << " ms | czas praktyczny = " << Select.czasPraktyczny/k << " ms" << endl;
			fout << "HeapSort: porownania = " << Heap.porownania/k << " | przestawienia = " << Heap.przestawienia/k << " | czas teoretyczny = " << Heap.czas/k << " ms | czas praktyczny = " << Heap.czasPraktyczny/k << " ms" << endl;
			fout << "QuickSort: porownania = " << Quick.porownania/k << " | przestawienia = " << Quick.przestawienia/k << " | czas teoretyczny = " << Quick.czas/k << " ms | czas praktyczny = " << Quick.czasPraktyczny/k << " ms" << endl;
			fout << "QuickSortModyfikacja: porownania = " << ModifiedQuick.porownania/k << " | przestawienia = " << ModifiedQuick.przestawienia/k << " | czas teoretyczny = " << ModifiedQuick.czas/k << " ms | czas praktyczny = " << ModifiedQuick.czasPraktyczny/k << " ms" << endl;
		}
		fout.close();	
        }
        else{
            cout << "podano zły pierwszy parametr";
        }
    }
    else{
        cout << "argc != 4\n";
    }
	return 0;
}
