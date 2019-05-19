#include "Trees.h"
#include "Tests.h"
#include <iostream>
#include <string.h>
#include <stdio.h>
#include <ctime>

int main(int argc, const char * argv[]){

  if (argc != 3 || strcmp(argv[1], "--type")){
    std::cout << "You must write \"./list4 --type [bst/rbt/splay]\"\n";
    return 1;
  }

  Trees * tree;
  BST bst;
  RBT rbt;
  Splay splay;
  AllOfThem allOfThem;

  if (!strcmp(argv[2], "bst")){
    tree = &bst;
  }
  else if (!strcmp(argv[2], "rbt")){
    tree = &rbt;
  }
  else if (!strcmp(argv[2], "splay")){
    tree = &splay;
  }
  else if (!strcmp(argv[2], "all")){
    tree = &allOfThem;
  }
  else{
    std::cout << "Third parametr mustn't be unequal to \"bst\",\"rbt\" or \"splay\"\n";
    return 2;
  }

  int numberOfOperations;
  clock_t start, stop;
  std::cout << "n = "; std::cin >> numberOfOperations;
  start = clock();
  while (numberOfOperations > 0){
    printf("\t\tn: %4.d | i - insert | d - delete | s - search | l - load | p - print(inorder) |\n", numberOfOperations);
    char command; std::cout << "command: "; std::cin >> command;
    std::string s;
    switch (command) {
      case 'i':
        std::cout << "s: "; std::cin >> s;
        tree -> insert(tree -> validation(s));
        break;
      case 'd':
        std::cout << "s: "; std::cin >> s;
        tree -> del(s);
        break;
      case 's':
        std::cout << "s: "; std::cin >> s;
        tree -> search(s);
        break;
      case 'l':
        std::cout << "f: "; std::cin >> s;
        tree -> load(s);
        break;
      case 'p':
        tree -> inorder();
        break;
      case 't':
        test(tree);
        return 0;
    }
    numberOfOperations--;
  }
  stop = clock();
  std::cerr << "\n duration of the entire program:\t" << stop - start << " ms\n";

  if (!strcmp(argv[2], "all")){
    allOfThem.statistic();
  }
  else
    tree -> statistic();

  return 0;
}
