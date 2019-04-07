//
//  funkcjePomocnicze.h
//  AlgorytmySortujace
//
//  Created by Mikis Dukiel on 25/03/2019.
//  Copyright © 2019 Mikis Dukiel. All rights reserved.
//

#ifndef funkcjePomocnicze_h
#define funkcjePomocnicze_h

#include <string>

typedef struct statystyki{
    int porownania;
    int przestawienia;
    unsigned long int czas;
    unsigned long int czasPraktyczny;
}Statystyki;

void pokazTablice(int n, int tablica[]);
bool dobryPorzadek(int n, int * tablica, bool asc);
void zamien (int a, int b, int * tablica);
void wstawIPrzesun(int wart, int pozycja, int n, int * tablica);
int wstawIPrzestaw(bool pokaz, int wart, int pozycja, int n, int * tablica, int przestawienia);
int porownanie(bool pokaz, int porownania, int a, int b, char znak);
int porownanie(bool pokaz, int porownania, int a, int b, char znak, std::string reszta);
int przestawienie(bool pokaz, int przestawienia, int a, int b);
int przestawienie(bool pokaz, int przestawienia, int a, std::string b);

#endif /* funkcjePomocnicze_h */
