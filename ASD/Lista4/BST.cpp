//
//  BST.cpp
//  Lista 4
//
//  Created by Mikis Dukiel on 11/05/2019.
//  Copyright © 2019 Mikis Dukiel. All rights reserved.
//

#include "Trees.h"
#include <iostream>
#include <fstream>

BST::BST(){
  Trees::numberOfElements = 0;
  Trees::maxNumberOfElements = 0;
  Trees::numberOfInsert = 0;
  Trees::numberOfDel = 0;
  Trees::numberOfSearch = 0;
  Trees::numberOfLoad = 0;
  Trees::numberOfInOrder = 0;
  Trees::numberOfComparison = 0;
  Trees::numberOfChangesOfElements = 0;
  root = NULL;
}

std::string Trees::validation(std::string s){
  while (s.length() > 0 && !( ((((char) s[0] > 64) && ((char) s[0] < 91)) || (((char) s[0] > 96) && ((char) s[0] < 123))) && ((((char) s[s.length()-1] > 64) && ((char) s[s.length()-1] < 91)) || (((char) s[s.length()-1] > 96) && ((char) s[s.length()-1] < 123))))){
    if (!((((char) s[0] > 64) && ((char) s[0] < 91)) || (((char) s[0] > 96) && ((char) s[0] < 123))))
      s = s.substr(1, s.length()-1);
    if (!((((char) s[s.length()-1] > 64) && ((char) s[s.length()-1] < 91)) || (((char) s[s.length()-1] > 96) && ((char) s[s.length()-1] < 123))))
      s = s.substr(0, s.length()-1);
  }

  if (s.length() > 0)
    return s;
  else
    return "";
}

void BST::insert(std::string s){
  if (s.length() == 0){
    std::cout << "[s is incorrect]\n";
    return;
  }
  numberOfInsert++;
  if (numberOfElements == 0){
    root = (Element*)malloc(sizeof *root);
    root -> key = s;
    root -> left = NULL;
    root -> right = NULL;
    root -> parent = NULL;
  }
  else{
    Element * y = (Element*)malloc(sizeof *y);
    y = NULL;
    Element * x = (Element*)malloc(sizeof *x);
    x = root;

    while (x != NULL){
      y = x;
      numberOfComparison++;
      if (s < (x -> key))
          x = (x -> left);
      else
          x = (x -> right);
    }

    Element * p = (Element*)malloc(sizeof *p);
    p = y;

    Element * node = (Element*)malloc(sizeof *node);
    node -> key = s;
    node -> left = NULL;
    node -> right = NULL;
    node -> parent = p;

    numberOfComparison++;
    if (y == NULL)
      root = node;
    else if (node -> key < p -> key)
      (p -> left) = node;
    else
      (p -> right) = node;
  }
  numberOfElements++;
  if (numberOfElements > maxNumberOfElements)
    maxNumberOfElements = numberOfElements;
}

void BST::inorderTreeWalk(Element * x){
  numberOfComparison++;
  if (x != NULL){
    inorderTreeWalk(x -> left);
    std::cout << x -> key << " ";
    inorderTreeWalk(x -> right);
  }
}

Element * BST::minimum(Element * x){
  while (x -> left != NULL){
    x = x -> left;
    numberOfComparison++;
  }
  numberOfComparison++;
  return x;
}

Element * BST::maximum(Element * x){
  while (x -> right != NULL){
    x = x -> right;
    numberOfComparison++;
  }
  numberOfComparison++;
  return x;
}

bool BST::find(std::string s){
  if (numberOfElements == 0)
    return false;
  else if (root -> key == s){
    numberOfComparison++;
    return true;
  }
  else{
    Element * x = root;
    while (x != NULL){
      numberOfComparison++;
      if (x -> key == s)
        return true;
      else if (x -> key > s)
        x = (x -> left);
      else
        x = (x -> right);
    }
    numberOfComparison++;
  }
  return false;
}

Element * BST::getElement(std::string s){
  if (numberOfElements == 0)
    return NULL;
  else if (root -> key == s){
    numberOfComparison++;
    return root;
  }
  else{
    Element * x = root;
    while (x != NULL){
      numberOfComparison++;
      if (x -> key == s)
        return x;
      else if (x -> key > s)
        x = (x -> left);
      else
        x = (x -> right);
    }
    numberOfComparison++;
  }
  return NULL;
}

void BST::transplant(Element * u, Element * v){
  numberOfComparison++;
  numberOfChangesOfElements++;
  if (u -> parent == NULL)
    root = v;
  else if (u == (u -> parent) -> left)
    (u -> parent) -> left = v;
  else
    (u -> parent) -> right = v;

  numberOfComparison++;
  if (v != NULL){
    v -> parent = u -> parent;
    numberOfChangesOfElements++;
  }
}

void BST::del(std::string s){
  numberOfDel++;
  Element * z= (Element*)malloc(sizeof *z);
  if (find(s)){
    z = getElement(s);
    numberOfComparison++;
    if (z -> left == NULL)
      transplant(z, z -> right);
    else if (z -> right == NULL)
      transplant(z, z -> left);
    else{
      Element * y = minimum(z -> right);
      numberOfComparison++;
      if (y -> parent != z){
        transplant(y, y -> right);
        numberOfChangesOfElements++;
        y -> right = z -> right;
        (y -> right) -> parent = y;
      }
      transplant(z, y);
      numberOfChangesOfElements++;
      y -> left = z -> left;
      (y -> left) -> parent = y;
    }
  numberOfElements--;
  }
}

void BST::search(std::string s){
  numberOfSearch++;
  std::cout << find(s) << "\n";
}

void Trees::load(std::string f){
  numberOfLoad++;
   std::ifstream fin;
   fin.open(f);
   if (!fin.is_open()){
      std::cout << "There is no such file as " << f << "\n";
      fin.close();
      return;
   }
   std::string word;
   while (fin >> word){
     word = validation(word);
     if (word.length() > 0){
      this->insert(word);
    }
   }
   fin.close();
}

void BST::inorder(){
  numberOfInOrder++;
  if (root != NULL)
    inorderTreeWalk(root);
  std::cout<<"\n";
}

void Trees::statistic(){
  std::cerr << " number of function Insert() calls: \t" << numberOfInsert << "\n";
  std::cerr << " number of function Delete() calls: \t" << numberOfDel << "\n";
  std::cerr << " number of function Search() calls: \t" << numberOfSearch << "\n";
  std::cerr << " number of function Load() calls:   \t" << numberOfLoad << "\n";
  std::cerr << " number of function InOrder() calls:\t" << numberOfInOrder << "\n";
  std::cerr << " number of elements at the end:     \t" << numberOfElements << "\n";
  std::cerr << " the largest number of elements:    \t" << maxNumberOfElements << "\n";
  std::cerr << " total number of comparisons:       \t" << numberOfComparison << "\n";
  std::cerr << " total number of element changes:   \t" << numberOfChangesOfElements << "\n";
}
