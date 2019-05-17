#include "Trees.h"
#include <iostream>
#include <string.h>
#include <stdio.h>

std::string validation(std::string s){
  while (!( ((((char) s[0] > 64) && ((char) s[0] < 91)) || (((char) s[0] > 96) && ((char) s[0] < 123))) && ((((char) s[s.length()-1] > 64) && ((char) s[s.length()-1] < 91)) || (((char) s[s.length()-1] > 96) && ((char) s[s.length()-1] < 123))))){
    if (!((((char) s[0] > 64) && ((char) s[0] < 91)) || (((char) s[0] > 96) && ((char) s[0] < 123))))
      s = s.substr(1, s.length()-1);
    if (!((((char) s[s.length()-1] > 64) && ((char) s[s.length()-1] < 91)) || (((char) s[s.length()-1] > 96) && ((char) s[s.length()-1] < 123))))
      s = s.substr(0, s.length()-1);
  }
  return s;
}

int main(int argc, const char * argv[]){
/*
  if (argc != 3 || strcmp(argv[1], "--type")){
    std::cout << "You must write \"./list4 --type [bst/rbt/splay]\"\n";
    return 1;
  }

  Trees * tree;
  std::cout << "Hello World!\n";
  BST bst;
  RBT rbt;

  if (!strcmp(argv[2], "bst")){
    tree = &bst;
  }
  else if (!strcmp(argv[2], "rbt")){
    tree = &rbt;
  }
  else if (!strcmp(argv[2], "splay")){

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
        tree -> insert(validation(s));
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
        //tree -> load(s);
        break;
      case 'p':
        tree -> inorder();
        break;
    }
    numberOfOperations--;
  }*/
  /*test*/
  std::string a;
  //RBT rbt;

  int end = 11229; int j = 1;
  while (j < end){
  //for (int j = 0; j < end; j++){ BST rbt;//RBT rbt;
  BST rbt;
  for (int i = 0; i < j; i++){
    char ch = 'a' + i;
    a = ch;
    rbt.insert(a);
    //rbt.inorder();
  }
  //rbt.inorder();
  for (int i = 0; i < j; i++){
    char ch = 'a' + i;
    a = ch;
    rbt.del(a);
    //rbt.inorder();
    rbt.insert(a);
  }
  j++;
}
  //if (j == end - 1) rbt.inorder();
//}
  return 0;
}
