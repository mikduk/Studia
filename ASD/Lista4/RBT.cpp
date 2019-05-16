//
//  RBT.cpp
//  Lista 4
//
//  Created by Mikis Dukiel on 16/05/2019.
//  Copyright © 2019 Mikis Dukiel. All rights reserved.
//

#include "Trees.h"
#include <iostream>
#include <fstream>

RBT::RBT(){
  Trees::numberOfElements = 0;
}

void RBT::insert(std::string s){
  s = validation(s);
  if (numberOfElements == 0){
    root = (Element*)malloc(sizeof *root);
    root -> key = s;
    root -> left = NULL;
    root -> right = NULL;
    root -> parent = NULL;
  }
  else{
    Element * y = NULL; // NIL
    Element * x = root; // root

    while (x != NULL){
      y = x;
      if (s < (x -> key))
          x = (x -> left);
      else
          x = (x -> right);
    }

    Element * p = y;

    Element * node;
    node = (Element*)malloc(sizeof *node);
    node -> key = s;
    node -> left = NULL;
    node -> right = NULL;
    node -> parent = p;

    if (node -> key < p -> key)
      (p -> left) = node;
    else
      (p -> right) = node;
  }
  numberOfElements++;
}

void RBT::inorderTreeWalk(Element * x){
  if (x != NULL){
    inorderTreeWalk(x -> left);
    std::cout << x -> key << " ";
    inorderTreeWalk(x -> right);
  }
}

Element * RBT::minimum(Element * x){
  while (x -> left != NULL){
    x = x -> left;
  }
  return x;
}

Element * RBT::maximum(Element * x){
  while (x -> right != NULL){
    x = x -> right;
  }
  return x;
}

bool RBT::find(std::string s){
  if (numberOfElements == 0)
    return false;
  else if (root -> key == s)
    return true;
  else{
    Element * x = root;
    while (x != NULL){
      if (x -> key == s)
        return true;
      else if (x -> key > s)
        x = (x -> left);
      else
        x = (x -> right);
    }
  }
  return false;
}

Element * RBT::getElement(std::string s){
  if (numberOfElements == 0)
    return NULL;
  else if (root -> key == s)
    return root;
  else{
    Element * x = root;
    while (x != NULL){
      if (x -> key == s)
        return x;
      else if (x -> key > s)
        x = (x -> left);
      else
        x = (x -> right);
    }
  }
  return NULL;
}

void RBT::transplant(Element * u, Element * v){
  if (u -> parent == NULL)
    root = v;
  else if (u == (u -> parent) -> left)
    (u -> parent) -> left = v;
  else
    (u -> parent) -> right = v;

  if (v != NULL)
    v -> parent = u -> parent;
}

void RBT::del(std::string s){
  Element * z;
  if (find(s)){
    z = getElement(s);
    if (z -> left == NULL)
      transplant(z, z -> right);
    else if (z -> right == NULL)
      transplant(z, z -> left);
    else{
      Element * y = minimum(z -> right);
        if (y -> parent != z){
          transplant(y, y -> right);
          y -> right = z -> right;
          (y -> right) -> parent = y;
        }
        transplant(z, y);
        y -> left = z -> left;
        (y -> left) -> parent = y;
    }
  }

}

void RBT::search(std::string s){
  std::cout << find(s) << "\n";
}

void RBT::load(std::string f){

}

void RBT::inorder(){
  inorderTreeWalk(root);
  std::cout<<"\n";
}
