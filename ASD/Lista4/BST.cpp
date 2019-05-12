//
//  BST.cpp
//  Lista 4
//
//  Created by Mikis Dukiel on 11/05/2019.
//  Copyright © 2019 Mikis Dukiel. All rights reserved.
//

#include "Trees.h"
#include <iostream>

BST::BST(){
  Trees::numberOfElements = 0;
}

void BST::insert(std::string s){ std::cout<<"[insert] s: "<<s<<"\n";
  if (numberOfElements == 0){
    Element r(s, NULL, NULL, NULL);
    root = &r;
  }
  else{
    Element * y = NULL; // NIL
    Element * x = root; // root
    std::cout<<"y = " << y << ", x = "<< x <<"\n";
    std::cout<<"key: "<< x -> key << ", left: " << x->left << "\n";
    while (x != NULL){
      y = x;
      if (s < (x -> key))
          x = (x -> left);
      else
          x = (x -> right);
    }
    Element * p = y;
    Element node(s, NULL, NULL, p);
    if (y -> key < p -> key)
      (p -> left) = &node;
    else
      (p -> right) = &node;
  }
  numberOfElements++;
  //inorderTreeWalk(root);
  std::cout << "root: " << root << " " << root -> key << "\n";
}

void BST::inorderTreeWalk(Element * x){
  if (x != NULL){
    inorderTreeWalk(x -> left);
    std::cout << x -> key << " \n";
    inorderTreeWalk(x -> right);
  }
}

Element * BST::minimum(Element * x){
  while (x -> left != NULL){
    x = x -> left;
  }
  return x;
}

Element * BST::maximum(Element * x){
  while (x -> right != NULL){
    x = x -> right;
  }
  return x;
}

void BST::del(std::string s){}
bool BST::search(std::string s){return true;}
void BST::load(std::string f){}
void BST::inorder(){}
