//
//  funkcjePomocnicze.cpp
//  AlgorytmySortujace
//
//  Created by Mikis Dukiel on 25/03/2019.
//  Copyright © 2019 Mikis Dukiel. All rights reserved.
//

#include "funkcjePomocnicze.h"
#include <iostream>
#include <cstdio>

using namespace std;

void pokazTablice(int n, int tablica[]){
    for (int i=0; i<n; i++)
        cout << tablica[i] << " ";
    cout << endl;
}

void zamien (int a, int b, int * tablica){
    int temp = tablica[a];
    tablica[a] = tablica[b];
    tablica[b] = temp;
}

void wstawIPrzesun(int wart, int pozycja, int n, int * tablica){
    for (int i = n-1; i >= pozycja; i--)
        tablica[i+1] = tablica[i];
    tablica[pozycja] = wart;
}

int wstawIPrzestaw(int wart, int pozycja, int n, int * tablica, int przestawienia){
    for (int i = n-1; i >= pozycja; i--){
        //przestawienia = przestawienie(przestawienia, tablica[i+1], tablica[i]);
        tablica[i+1] = tablica[i];
    }
    przestawienia = przestawienie(przestawienia, wart, tablica[pozycja]);
    tablica[pozycja] = wart;
    return przestawienia;
}

int porownanie(int porownania, int a, int b, char znak){
    cerr << "(" << ++porownania << ") Porównuję: " << a << " " << znak << " " << b << endl;
    return porownania;
}

int porownanie(int porownania, int a, int b, char znak, string reszta){
    cerr << "(" << ++porownania << ") Porównuję: " << a << " " << znak << " " << b << " (" << reszta << ")" << endl;
    return porownania;
}

int przestawienie(int przestawienia, int a, int b){
    cerr << "(" << ++przestawienia << ") Przestawiam: " << a << " z " << b << "\n";
    return przestawienia;
}

int przestawienie(int przestawienia, int a, string b){
    cerr << "(" << ++przestawienia << ") Przestawiam: " << a << " " << b << "\n";
    return przestawienia;
}

