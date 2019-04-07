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
                    Statystyki.operator=(selectSort(n, tablica, true, Statystyki, true));
                    if (dobryPorzadek(n, tablica, true))
                        cout << n << endl; pokazTablice(n, tablica);
                }
                else if(!strcmp(argv[2], "insert")){
                    Statystyki.operator=(insertSort(n, tablica, true, Statystyki, true));
                    if (dobryPorzadek(n, tablica, true))
                        cout << n << endl; pokazTablice(n, tablica);
                }
                else if(!strcmp(argv[2], "heap")){
                    Statystyki.operator=(heapSort(n, tablica, true, Statystyki, true));
                    if (dobryPorzadek(n, tablica, true))
                        cout << n << endl; pokazTablice(n, tablica);
                }
                else if(!strcmp(argv[2], "quick")){
                    Statystyki.operator=(quickSort(n, tablica, true, Statystyki, true));
                    if (dobryPorzadek(n, tablica, true))
                        cout << n << endl; pokazTablice(n, tablica);
                }
                else if(!strcmp(argv[2], "mquick")){
                    Statystyki.operator=(quickSortModyfikacja(n, tablica, true, Statystyki, true));
                    if (dobryPorzadek(n, tablica, true))
                        cout << n << endl; pokazTablice(n, tablica);
                }
                else{
                    cout << "podano zły drugi parametr\n";
                }
            }
            else if(!strcmp(argv[3], "--desc")){
                if (!strcmp(argv[2], "select")){
                    Statystyki.operator=(selectSort(n, tablica, false, Statystyki, true));
                    if (dobryPorzadek(n, tablica, false))
                        cout << n << endl; pokazTablice(n, tablica);
                }
                else if(!strcmp(argv[2], "insert")){
                    Statystyki.operator=(insertSort(n, tablica, false, Statystyki, true));
                    if (dobryPorzadek(n, tablica, false))
                        cout << n << endl; pokazTablice(n, tablica);
                }
                else if(!strcmp(argv[2], "heap")){
                    Statystyki.operator=(heapSort(n, tablica, false, Statystyki, true));
                    if (dobryPorzadek(n, tablica, false))
                        cout << n << endl; pokazTablice(n, tablica);
                }
                else if(!strcmp(argv[2], "quick")){
                    Statystyki.operator=(quickSort(n, tablica, false, Statystyki, true));
                    if (dobryPorzadek(n, tablica, false))
                        cout << n << endl; pokazTablice(n, tablica);
                }
                else if(!strcmp(argv[2], "mquick")){
                    Statystyki.operator=(quickSortModyfikacja(n, tablica, false, Statystyki, true));
                    if (dobryPorzadek(n, tablica, false))
                        cout << n << endl; pokazTablice(n, tablica);
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
		nazwaAlgorytmu = "insertSort";
		fout << nazwaAlgorytmu << endl;
		int tablica[10000];
		for (int i = 0; i < 10000; i++){
			tablica[i] = ((rand()*20000) % 20000) - 10000;
		}
		
		for (int i = 100; i <= 1000; i += 100){
			int porownania = 0;
			int przestawienia = 0;
			unsigned long int czas = 0;
			unsigned long int czasPraktyczny = 0;

			int * kopia_tablicy = new int[i];
	            	for (int u = 0; u < i; u++)
                		kopia_tablicy[u] = tablica[u];
			for (int j = 0; j < k; j++){
				statystyki x;
				x.operator=(insertSort(i, kopia_tablicy, true, x, false));
				porownania += x.porownania;
				przestawienia += x.przestawienia;
				czas += x.czas;
				czasPraktyczny += x.czasPraktyczny;				
			}
			fout << "i = " << i << " | porownania = " << porownania/k << " | przestawienia = " << przestawienia/k << " | czas teoretyczny = " << czas/k << " ms | czas praktyczny = " << czasPraktyczny/k << " ms" << endl; 
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
}
