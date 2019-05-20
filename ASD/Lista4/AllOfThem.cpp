//
//  AllOfThem.cpp
//  Lista 4
//
//  Created by Mikis Dukiel on 19/05/2019.
//  Copyright © 2019 Mikis Dukiel. All rights reserved.
//

#include "Trees.h"
#include <iostream>

AllOfThem::AllOfThem(){
  BST tree1; bst_tree = tree1; bst = &bst_tree;
  RBT tree2; rbt_tree = tree2; rbt = &rbt_tree;
  Splay tree3; splay_tree = tree3; splay = &splay_tree;
}

void AllOfThem::insert(std::string s){ 
    bst -> insert(s);
    rbt -> insert(s);
  splay -> insert(s);
}

void AllOfThem::del(std::string s){
    bst -> del(s);
    rbt -> del(s);
  splay -> del(s);
}

void AllOfThem::search(std::string s){
  std::cout<<"   BST: ";   bst -> search(s);
  std::cout<<"   RBT: ";   rbt -> search(s);
  std::cout<<" SPLAY: "; splay -> search(s);
}

void AllOfThem::inorder(){
  std::cout<<"   BST: ";   bst -> inorder();
  std::cout<<"   RBT: ";   rbt -> inorder();
  std::cout<<" SPLAY: "; splay -> inorder();
}

void AllOfThem::load(std::string f){
  std::cout<<"   BST: ";   bst -> load(f);
  std::cout<<"   RBT: ";   rbt -> load(f);
  std::cout<<" SPLAY: "; splay -> load(f);
}

void AllOfThem::statistic(){
  std::cerr << "\n";
  std::cerr << " :::::::::::::::DATA::::::::::::::::\t" << ":::BST:::\t" << ":::RBT:::\t" << "::SPLAY::\n";
  std::cerr << "\n";
  std::cerr << " number of function Insert() calls: \t" << bst -> numberOfInsert << "\t\t" << rbt -> numberOfInsert << "\t\t" << splay -> numberOfInsert << "\n";
  std::cerr << " number of function Delete() calls: \t" << bst -> numberOfDel << "\t\t" << rbt -> numberOfDel << "\t\t" << splay -> numberOfDel << "\n";
  std::cerr << " number of function Search() calls: \t" << bst -> numberOfSearch << "\t\t" << rbt -> numberOfSearch << "\t\t" << splay -> numberOfSearch << "\n";
  std::cerr << " number of function Load() calls:   \t" << bst -> numberOfLoad << "\t\t" << rbt -> numberOfLoad << "\t\t" << splay -> numberOfLoad << "\n";
  std::cerr << " number of function InOrder() calls:\t" << bst -> numberOfInOrder << "\t\t" << rbt -> numberOfInOrder << "\t\t" << splay -> numberOfInOrder << "\n";
  std::cerr << " number of elements at the end:     \t" << bst -> numberOfElements << "\t\t" << rbt -> numberOfElements << "\t\t" << splay -> numberOfElements << "\n";
  std::cerr << " the largest number of elements:    \t" << bst -> maxNumberOfElements << "\t\t" << rbt -> maxNumberOfElements << "\t\t" << splay -> maxNumberOfElements << "\n";
  std::cerr << " total number of comparisons:       \t" << bst -> numberOfComparison << "\t\t" << rbt -> numberOfComparison << "\t\t" << splay -> numberOfComparison << "\n";
  std::cerr << " total number of element changes:   \t" << bst -> numberOfChangesOfElements << "\t\t" << rbt -> numberOfChangesOfElements << "\t\t" << splay -> numberOfChangesOfElements << "\n";
}

bool AllOfThem::find(std::string s){return true;}
Element * AllOfThem::getElement(std::string s){return NULL;}
