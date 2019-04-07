//
//  main.cpp
//  AlgorytmySortujace
//
//  Created by Mikis Dukiel on 25/03/2019.
//  Copyright © 2019 Mikis Dukiel. All rights reserved.
//

#include "algorytmy.h"
#include <iostream>

int main(int argc, const char * argv[]) {
    if (argc >= 3){
        if (!strcmp(argv[0], "--type")){
            
            int n = atoi(argv[3]);
            int * tablica = new int[n];
            for (int i = 4; i < n+3; i++)
                tablica[i-4] = atoi(argv[i]);
            
            statystyki Statystyki;
            Statystyki.porownania = 0;
            Statystyki.przestawienia = 0;
            Statystyki.czas = 0;
            Statystyki.czasPraktyczny = 0;
            
            if (!strcmp(argv[2], "--asc")){
                if (!strcmp(argv[1], "select")){
                    Statystyki.operator=(selectSort(n, tablica, true, Statystyki, true));
                }
                else if(!strcmp(argv[1], "insert")){
                    Statystyki.operator=(insertSort(n, tablica, true, Statystyki, true));
                }
                else if(!strcmp(argv[1], "heap")){
                    Statystyki.operator=(heapSort(n, tablica, true, Statystyki, true));
                }
                else if(!strcmp(argv[1], "quick")){
                    Statystyki.operator=(quickSort(n, tablica, true, Statystyki, true));
                }
                else if(!strcmp(argv[1], "mquick")){
                    Statystyki.operator=(quickSortModyfikacja(n, tablica, true, Statystyki, true));
                }
                else{
                   std::cout << "podano zły drugi parametr\n";
                }
            }
            else if(!strcmp(argv[2], "--desc")){
                if (!strcmp(argv[1], "select")){
                    Statystyki.operator=(selectSort(n, tablica, false, Statystyki, true));
                }
                else if(!strcmp(argv[1], "insert")){
                    Statystyki.operator=(insertSort(n, tablica, false, Statystyki, true));
                }
                else if(!strcmp(argv[1], "heap")){
                    Statystyki.operator=(heapSort(n, tablica, false, Statystyki, true));
                }
                else if(!strcmp(argv[1], "quick")){
                    Statystyki.operator=(quickSort(n, tablica, false, Statystyki, true));
                }
                else if(!strcmp(argv[1], "mquick")){
                    Statystyki.operator=(quickSortModyfikacja(n, tablica, false, Statystyki, true));
                }
                else{
                    std::cout << "podano zły drugi parametr\n";
                }
            }
            else{
                std::cout << "podano zły trzeci parametr\n";
            }
        }
        else if(!strcmp(argv[0], "--stat")){
            int k = atoi(argv[2]);
        }
        else{
            std::cout << "podano zły pierwszy parametr";
        }
    }
    else{
        std::cout << "argc != 3\n";
    }
}
