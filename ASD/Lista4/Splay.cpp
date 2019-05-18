//
//  Splay.cpp
//  Lista 4
//
//  Created by Mikis Dukiel on 18/05/2019.
//  Copyright © 2019 Mikis Dukiel. All rights reserved.
//

#include "Trees.h"
#include <iostream>
#include <fstream>

Splay::Splay(){
  Trees::numberOfElements = 0;
  root = NULL;
}

void Splay::insert(std::string s){
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

    if (y == NULL)
      root = node;
    else if (node -> key < p -> key)
      (p -> left) = node;
    else
      (p -> right) = node;
    splay(node);
  }
  numberOfElements++;
}

void Splay::splay(Element * x){
  while (x -> parent != NULL){
    Element * p = (Element*)malloc(sizeof *p);
    p = x -> parent;
    Element * g = (Element*)malloc(sizeof *g);
    g = (x -> parent) -> parent;

    if (g == NULL){
      if (x == p -> left)
        makeLeftChildParent(x, p);
      else
        makeRightChildParent(x, p);
    }
    else{
      if (x == p -> left){
        if (p == g -> left){
          makeLeftChildParent(p, g);
          makeLeftChildParent(x, p);
        }
        else{
          makeLeftChildParent(x, p);
          makeRightChildParent(x, p);
        }
      }
      else{
        if (p == g -> left){
          makeRightChildParent(x, p);
          makeLeftChildParent(x, p);
        }
        else{
          makeRightChildParent(p, g);
          makeRightChildParent(x, p);
        }
      }
    }
  }
  root = x;
}

void Splay::makeLeftChildParent(Element * x, Element * p){
  if ((x == NULL) || (p == NULL) || (p -> left != x) || (x -> parent != p))
    std::cout << "[makeLeftChildParent] WRONG\n";

  if (p -> parent != NULL){
    if (p == (p -> parent) -> left)
        (p -> parent) -> left = x;
    else
        (p -> parent) -> right = x;
  }

  if (x -> right != NULL)
    (x -> right) -> parent = p;

  x -> parent = p -> parent;
  p -> parent = x;
  p -> left = x -> right;
  x -> right = p;
}

void Splay::makeRightChildParent(Element * x, Element * p){
  if ((x == NULL) || (p == NULL) || (p -> right != x) || (x -> parent != p))
    std::cout << "[makeRightChildParent] WRONG\n";

  if (p -> parent != NULL){
    if (p == (p -> parent) -> left)
        (p -> parent) -> left = x;
    else
        (p -> parent) -> right = x;
  }

  if (x -> left != NULL)
    (x -> left) -> parent = p;

  x -> parent = p -> parent;
  p -> parent = x;
  p -> right = x -> left;
  x -> left = p;
}

void Splay::del(std::string s){
  Element * z = (Element*)malloc(sizeof *z);
  if (find(s)){
    z = getElement(s);
    splay(z);
    if ((z -> left != NULL) && (z -> right != NULL)){
      Element * minLess = (Element*)malloc(sizeof *minLess);
      minLess = z -> left;
      while (minLess -> right != NULL)
        minLess = minLess -> right;
      minLess -> right = z -> right;
      (z -> right) -> parent = minLess;
      (z -> left) -> parent = NULL;
      root = z -> left;
    }
    else if (z -> right != NULL){
      (z -> right) -> parent = NULL;
      root = z -> right;
    }
    else if (z -> left != NULL){
      (z -> left) -> parent = NULL;
      root = z -> left;
    }
    else
      root = NULL;

    z -> parent = NULL;
    z -> left = NULL;
    z -> right = NULL;
    z = NULL;
    numberOfElements--;
  }
}

void Splay::search(std::string s){
  std::cout << find(s) << "\n";
}

bool Splay::find(std::string s){

  Element * previous = (Element*)malloc(sizeof *previous);
  previous = NULL;
  Element * z = (Element*)malloc(sizeof *z);
  z = root;

  while (z != NULL){
    previous = z;
    if (s < (z -> key))
      z = (z -> left);
    else if (s > (z -> key))
      z = (z -> right);
    else{
      splay(z);
      return true;
    }
  }

  if (previous != NULL){
    splay(previous);
    return false;
  }

  return false;
}

Element * Splay::getElement(std::string s){

  Element * previous = (Element*)malloc(sizeof *previous);
  previous = NULL;
  Element * z = (Element*)malloc(sizeof *z);
  z = root;

  while (z != NULL){
    previous = z;
    if (s < (z -> key))
      z = (z -> left);
    else if (s > (z -> key))
      z = (z -> right);
    else{
      splay(z);
      return z;
    }
  }

  if (previous != NULL){
    splay(previous);
    return NULL;
  }

  return NULL;
}

void Splay::inorderTreeWalk(Element * x){
  if (x != NULL){
    inorderTreeWalk(x -> left);
    std::cout << x -> key << " ";
    inorderTreeWalk(x -> right);
  }
}

void Splay::inorder(){
  if (root != NULL)
    inorderTreeWalk(root);
  std::cout<<"\n";
}

void Splay::load(std::string f){

}
