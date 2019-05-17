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
}

void BST::insert(std::string s){
  //s = validation(s);
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

    if (node -> key < p -> key)
      (p -> left) = node;
    else
      (p -> right) = node;
  }
  numberOfElements++;
}

void BST::inorderTreeWalk(Element * x){
  if (x != NULL){
    inorderTreeWalk(x -> left);
    std::cout << x -> key << " ";
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

bool BST::find(std::string s){
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

Element * BST::getElement(std::string s){
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

void BST::transplant(Element * u, Element * v){
  if (u -> parent == NULL)
    root = v;
  else if (u == (u -> parent) -> left)
    (u -> parent) -> left = v;
  else
    (u -> parent) -> right = v;

  if (v != NULL)
    v -> parent = u -> parent;
}

void BST::del(std::string s){
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
  numberOfElements--;
}

void BST::search(std::string s){
  std::cout << find(s) << "\n";
}

void BST::load(std::string f){

}

void BST::inorder(){
  inorderTreeWalk(root);
  std::cout<<"\n";
}
