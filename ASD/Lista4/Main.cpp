#include "Trees.h"
#include <iostream>
#include <string.h>
#include <stdio.h>

int main(int argc, const char * argv[]){

  if (argc != 3 || strcmp(argv[1], "--type")){
    std::cout << "You must write \"./list4 --type [bst/rbt/splay]\"\n";
    return 1;
  }

  Trees * tree;
  std::cout << "Hello World!\n";
  BST bst;
  RBT rbt;
  Splay splay;

  if (!strcmp(argv[2], "bst")){
    tree = &bst;
  }
  else if (!strcmp(argv[2], "rbt")){
    tree = &rbt;
  }
  else if (!strcmp(argv[2], "splay")){
    tree = &splay;
  }
  else{
    std::cout << "Third parametr mustn't be unequal to \"bst\",\"rbt\" or \"splay\"\n";
    return 2;
  }

  int numberOfOperations;
  std::cout << "n = "; std::cin >> numberOfOperations;

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
    }
    numberOfOperations--;
  }

  tree -> statistic();

  return 0;
}
