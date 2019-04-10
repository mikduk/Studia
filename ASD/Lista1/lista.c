//
//  lista.c
//  Lista1 - lista jednokierunkowa
//
//  Created by Mikis Dukiel on 01/03/2019.
//  Copyright © 2019 Mikis Dukiel. All rights reserved.
//

#include "lista.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

// Funkcja pomocniczo-organizacyjna, pokazująca zawartość listy
void pokazListe( List* list){
    printf("Elementy listy: ");
    List* tempList = list;
    while (tempList != NULL) {
        printf("%d, ", tempList -> value);
        tempList = tempList -> nextElement;
    }
    printf("\n");
}

bool isempty( List* x){
    if (x == NULL){
        return true;
    }
    else{
        return false;
    }
}

List* insert(int newValue,  List* list, bool isCommented){
    
    List* copyList = malloc(sizeof(*list));
    copyList = list;
    List* insertElement = malloc(sizeof(*insertElement));
    insertElement -> value = newValue;
    insertElement -> nextElement = NULL;
    
    if (isempty(copyList)){
        copyList = insertElement;
        copyList -> value = insertElement -> value;
        copyList -> nextElement = insertElement -> nextElement;
    }
    else{
        List* tempList = malloc(sizeof(*list));
        tempList = copyList;
        while((tempList -> nextElement)!=NULL){
            tempList = tempList -> nextElement;
        }
        tempList -> nextElement = insertElement;
    }
    if (isCommented) printf("Dodano do listy: %d.\n", newValue);
    list = copyList;
    return list;
}

List* delete(int delValue, List* list, bool isCountedComparison, bool isCommented){
    
    if (isempty(list)){
        if (isCountedComparison) licznik_porownan++;
        if (isCommented) printf("Brak elementu na liście - nie usunięto elementu %d.\n", delValue);
        return list;
    }
    else if (list -> value == delValue){
        if (isempty(list -> nextElement)){
            list = NULL;
        }
        else{
            list -> value =  list -> nextElement -> value;
            list -> nextElement = list -> nextElement -> nextElement;
        }
        if (isCountedComparison) licznik_porownan++;
        if (isCommented) printf("Usunięto z listy: %d.\n", delValue);
        return list;
    }
    else if (isempty(list -> nextElement)){
        if (isCountedComparison) licznik_porownan++;
        if (isCommented) printf("Brak elementu na liście - nie usunięto elementu %d.\n", delValue);
        return list;
    }
    else if (list -> nextElement -> value != delValue){
        if (isCountedComparison) licznik_porownan++;
        delete(delValue, list -> nextElement, isCountedComparison, isCommented);
    }
    else{
        list -> nextElement = list -> nextElement -> nextElement;
        if (isCountedComparison) licznik_porownan++;
        if (isCommented) printf("Usunięto z listy: %d.\n", delValue);
        return list;
    }
    return list;
}

bool findMTF(int x,  List* list, bool isCountedComparison, bool isCommented){
    if (isCountedComparison && isCommented) printf("licznik_porownan = %d\n", licznik_porownan);
    bool isExist = false;
    if (list == NULL){
        if (isCountedComparison) licznik_porownan++;
        if (isCommented) printf("Brak elementu na liście - nie przesunięto elementu %d.\n", x);
        return false;
    }
    else if (list -> value == x){
        list = list -> nextElement;
        if (isCountedComparison) licznik_porownan++;
        if (isCommented) printf("Element %d był już na przodzie listy.\n", x);
        return true;
    }
    else{
        List* tempList = list;
        while ((tempList -> nextElement) != NULL){
            if (tempList -> nextElement -> value != x){
                if (isCountedComparison) licznik_porownan++;
                tempList = tempList -> nextElement;
            }
            else{
                if (isCountedComparison) licznik_porownan++;
                tempList -> nextElement = tempList -> nextElement -> nextElement;
                isExist = true;
                break;
            }
        }
    }
        
    if (isExist){
        List* insertElement = malloc(sizeof(*insertElement));
        insertElement -> nextElement = list -> nextElement;
        int x1 = list -> value;
        list -> nextElement = insertElement;
        insertElement -> value = x1;
        list -> value = x;
        if (isCommented) printf("Znaleziono i przesunięto na przód element: %d.\n", x);
        
    }
    else{
        if (isCountedComparison) licznik_porownan++;
        if (isCommented) printf("Brak elementu na liście - nie przesunięto elementu %d.\n", x);
    }
    
    return isExist;
}

bool findTRANS(int x, List* list, bool isCountedComparison, bool isCommented){
    
    bool isExist = false;
    if (isempty(list)){
        if (isCountedComparison) licznik_porownan++;
        if (isCommented) printf("Brak elementu na liście - nie przesunięto elementu %d.\n", x);
        return false;
    }
    else if (list -> value == x){
        list = list -> nextElement;
        if (isCountedComparison) licznik_porownan++;
        if (isCommented) printf("Element %d był już na przodzie listy.\n", x);
        return true;
    }
    else{
        List* tempList = list;
        while ((tempList -> nextElement) != NULL){
            if (tempList -> nextElement -> value != x){
                if (isCountedComparison) licznik_porownan++;
                tempList = tempList -> nextElement;
            }
            else{
                if (isCountedComparison) licznik_porownan++;
                int x1 = tempList -> value;
                tempList -> value = x;
                tempList -> nextElement -> value = x1;
                isExist = true;
            }
        }
    }
    
    if (isExist){
        if (isCommented) printf("Znaleziono i przesunięto element: %d.\n", x);
        return true;
    }
    else{
        if (isCommented) printf("Brak elementu na liście - nie przesunięto elementu %d.\n", x);
        return false;
    }
    return false;
}
