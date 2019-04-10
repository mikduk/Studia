//
//  lista.h
//  Lista1
//
//  Created by Mikis Dukiel on 01/03/2019.
//  Copyright © 2019 Mikis Dukiel. All rights reserved.
//

#ifndef lista_h
#define lista_h

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

extern int licznik_porownan;

typedef struct List{
    int value;
    struct List *nextElement;
}List;

void pokazListe(List* list);
bool isempty(List* x);
List* insert(int newValue, List* list, bool isCommented);
List* delete(int delValue, List* list, bool isCountedComparison, bool isCommented);
bool findMTF(int x, List* list, bool isCountedComparison, bool isCommented);
bool findTRANS(int x, List* list, bool isCountedComparison, bool isCommented);

#endif /* lista_h */

