#include "Trees.h"
#include "Tests.h"
#include <iostream>
#include <string>
#include <stdio.h>
#include <ctime>
#include <fstream>

void loadInsert(Trees * tree, std::string f, clock_t &time){
  clock_t start;
   std::ifstream fin;
   fin.open(f);
   if (!fin.is_open()){
      std::cout << "There is no such file as " << f << "\n";
      fin.close();
      return;
   }
   std::string word;
   while (fin >> word){
     word = tree -> validation(word);
     if (word.length() > 0){
      start = clock();
      tree -> insert(word);
      time += (clock() - start);
    }
   }
   fin.close();
}

void loadDelete(Trees * tree, std::string f, clock_t &time){
  clock_t start;
   std::ifstream fin;
   fin.open(f);
   if (!fin.is_open()){
      std::cout << "There is no such file as " << f << "\n";
      fin.close();
      return;
   }
   std::string word;
   while (fin >> word){
     word = tree -> validation(word);
     if (word.length() > 0){
      start = clock();
      tree -> del(word);
      time += (clock() - start);
    }
   }
   fin.close();
}

void loadSearch(Trees * tree, std::string f, clock_t &time){
  clock_t start;
   std::ifstream fin;
   fin.open(f);
   if (!fin.is_open()){
      std::cout << "There is no such file as " << f << "\n";
      fin.close();
      return;
   }
   std::string word;
   while (fin >> word){
     word = tree -> validation(word);
     if (word.length() > 0){
      start = clock();
      tree -> search(word);
      time += (clock() - start);
    }
   }
   fin.close();
}

int test(Trees * tree){

  int testID;
  bool go = true;
  clock_t start, stop, insT, delT, seaT, inoT;
  int n = 10000;
  std::string f = "filePath";
  std::cout << " 1: n elements\n 2: n same elements\n 3: elements from file\n 0: end of testing\n";
  start = clock();
  while (go){
    std::cout << "testID: "; std::cin >> testID;
    if (testID == 1 || testID == 2){
      std::cout << "n: "; std::cin >> n;
    }
    else if (testID == 3){
      std::cout << "f: "; std::cin >> f;
    }
    else if (testID == 0){
      return 0;
    }
    std::string s;
    if (testID == 1){
      // insert
      start = clock();
      for (int i = 0; i < n; i++){
        s = "a" + std::to_string(i) + "a";
        tree -> insert(s);
      }
      stop = clock();
      insT = stop - start;
      // inorder
      start = clock();
      tree -> inorder();
      stop = clock();
      inoT = stop - start;
      // search
      start = clock();
      for (int i = 0; i < n; i++){
        s = "a" + std::to_string(i) + "a";
        tree -> search(s);
      }
      stop = clock();
      seaT = stop - start;
      // delete
      start = clock();
      for (int i = 0; i < n; i++){
        s = "a" + std::to_string(i) + "a";
        tree -> del(s);
      }
      stop = clock();
      delT = stop - start;

      std::cout << " ::INSERT::\n avg time: " << insT / n << " ms\n";
      std::cout << " entire duration: " << insT << " ms\n\n";
      std::cout << " ::DELETE\n avg time: " << delT / n << " ms\n";
      std::cout << " entire duration: " << delT << " ms\n\n";
      std::cout << " ::SEARCH::\n avg time: " << seaT / n << " ms\n";
      std::cout << " entire duration: " << seaT << " ms\n\n";
      std::cout << " ::INORDER::\n avg time: " << inoT / n << " ms\n";
      std::cout << " entire duration: " << inoT << " ms\n\n";
      tree -> statistic();
      // clear
      tree -> numberOfElements = 0;
      tree -> maxNumberOfElements = 0;
      tree -> numberOfInsert = 0;
      tree -> numberOfDel = 0;
      tree -> numberOfSearch = 0;
      tree -> numberOfLoad = 0;
      tree -> numberOfInOrder = 0;
      tree -> numberOfComparison = 0;
      tree -> numberOfChangesOfElements = 0;
      tree -> root = NULL;
    }
    else if (testID == 2){
      // insert
      start = clock();
      for (int i = 0; i < n; i++){
        s = "a";
        tree -> insert(s);
      }
      stop = clock();
      insT = stop - start;
      // inorder
      start = clock();
      tree -> inorder();
      stop = clock();
      inoT = stop - start;
      // search
      start = clock();
      for (int i = 0; i < n; i++){
        s = "a";
        tree -> search(s);
      }
      stop = clock();
      seaT = stop - start;
      // delete
      start = clock();
      for (int i = 0; i < n; i++){
        s = "a";
        tree -> del(s);
      }
      stop = clock();
      delT = stop - start;

      std::cout << " ::INSERT::\n avg time: " << insT / n << " ms\n";
      std::cout << " entire duration: " << insT << " ms\n\n";
      std::cout << " ::DELETE\n avg time: " << delT / n << " ms\n";
      std::cout << " entire duration: " << delT << " ms\n\n";
      std::cout << " ::SEARCH::\n avg time: " << seaT / n << " ms\n";
      std::cout << " entire duration: " << seaT << " ms\n\n";
      std::cout << " ::INORDER::\n avg time: " << inoT / n << " ms\n";
      std::cout << " entire duration: " << inoT << " ms\n\n";
      tree -> statistic();
      // clear
      tree -> numberOfElements = 0;
      tree -> maxNumberOfElements = 0;
      tree -> numberOfInsert = 0;
      tree -> numberOfDel = 0;
      tree -> numberOfSearch = 0;
      tree -> numberOfLoad = 0;
      tree -> numberOfInOrder = 0;
      tree -> numberOfComparison = 0;
      tree -> numberOfChangesOfElements = 0;
      tree -> root = NULL;
    }
    else if (testID == 3){
      int insC, insM, delC, delM, seaC, seaM;
      // insert
      insT = 0;
      loadInsert(tree, f, insT);
      n = tree -> numberOfInsert;
      insC = tree -> numberOfComparison;
      insM = tree -> numberOfChangesOfElements;
      // inorder
      start = clock();
      tree -> inorder();
      stop = clock();
      inoT = stop - start;
      // search
      seaT = 0;
      loadSearch(tree, f, seaT);
      seaC = (tree -> numberOfComparison) - insC;
      seaM = (tree -> numberOfChangesOfElements) - insM;
      // delete
      delT = 0;
      loadDelete(tree, f, delT);
      delC = (tree -> numberOfComparison) - seaC;
      delM = (tree -> numberOfChangesOfElements) - seaM;

      std::cout << " ::INSERT::\n avg time: " << insT / n << " ms\n";
      std::cout << " entire duration: " << insT << " ms\n";
      std::cout << " entire comparisons: " << insC << "\n";
      std::cout << " entire element changes: " << insM << "\n\n";
      std::cout << " ::DELETE\n avg time: " << delT / n << " ms\n";
      std::cout << " entire duration: " << delT << " ms\n";
      std::cout << " entire comparisons: " << delC << "\n";
      std::cout << " entire element changes: " << delM << "\n\n";
      std::cout << " ::SEARCH::\n avg time: " << seaT / n << " ms\n";
      std::cout << " entire duration: " << seaT << " ms\n";
      std::cout << " entire comparisons: " << seaC << "\n";
      std::cout << " entire element changes: " << seaM << "\n\n";
      std::cout << " ::INORDER::\n avg time: " << inoT / n << " ms\n";
      std::cout << " entire duration: " << inoT << " ms\n\n";
      tree -> statistic();
    }

      }
    return 0;
}
