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

bool dobryPorzadek(int n, int * tablica, bool asc){
    bool ok = true;
    if (asc){
        for (int i = 1; i < n; i++)
            if (tablica[i-1] > tablica[i])
                ok = false;
    }
    else {
        for (int i = 1; i < n; i++)
            if (tablica[i-1] < tablica[i])
                ok = false;
    }
    return ok;
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

int wstawIPrzestaw(bool pokaz, int wart, int pozycja, int n, int * tablica, int przestawienia){
    for (int i = n-1; i >= pozycja; i--){
        //if (pokaz)
        //przestawienia = przestawienie(przestawienia, tablica[i+1], tablica[i]);
        tablica[i+1] = tablica[i];
    }
    if (pokaz)
    przestawienia = przestawienie(pokaz, przestawienia, wart, tablica[pozycja]);
    tablica[pozycja] = wart;
    return przestawienia;
}

int porownanie(bool pokaz, int porownania, int a, int b, char znak){
    porownania++;
    if (pokaz)
    cerr << "(" << porownania << ") Porównuję: " << a << " " << znak << " " << b << endl;
    return porownania;
}

int porownanie(bool pokaz, int porownania, int a, int b, char znak, string reszta){
    porownania++;
    if (pokaz)
    cerr << "(" << porownania << ") Porównuję: " << a << " " << znak << " " << b << " (" << reszta << ")" << endl;
    return porownania;
}

int przestawienie(bool pokaz, int przestawienia, int a, int b){
    przestawienia++;
    if (pokaz)
    cerr << "(" << przestawienia << ") Przestawiam: " << a << " z " << b << "\n";
    return przestawienia;
}

int przestawienie(bool pokaz, int przestawienia, int a, string b){
    przestawienia++;
    if (pokaz)
    cerr << "(" << przestawienia << ") Przestawiam: " << a << " " << b << "\n";
    return przestawienia;
}
