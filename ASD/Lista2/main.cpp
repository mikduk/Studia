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
            int k; cin >> k;
        }
        else{
            cout << "podano zły pierwszy parametr";
        }
    }
    else{
        cout << "argc != 4\n";
    }
}
