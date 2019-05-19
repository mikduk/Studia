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
#include <cstdlib>

Splay::Splay(){
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

void Splay::insert(std::string s){
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
    find(s);
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

void Splay::splay(Element * x){
  while (x -> parent != NULL){
    numberOfComparison++;
    Element * p = (Element*)malloc(sizeof *p);
    p = x -> parent;
    Element * g = (Element*)malloc(sizeof *g);
    g = (x -> parent) -> parent;

    numberOfComparison++;
    if (g == NULL){
      numberOfComparison++;
      if (p -> left != NULL && x == p -> left)
        rightRotate(p);
      else
        leftRotate(p);
    }
    else{
      numberOfComparison++;
      if (x == p -> left){
        numberOfComparison++;
        if (p == g -> left){
          rightRotate(g);
          rightRotate(p);
        }
        else{
          rightRotate(p);
          leftRotate(g);
        }
      }
      else{
        numberOfComparison++;
        if (p == g -> left){
          leftRotate(p);
          rightRotate(g);
        }
        else{
          leftRotate(g);
          leftRotate(p);
        }
      }
    }
  }
  root = x;
}

void Splay::leftRotate(Element * x){
  Element * y = (Element*)malloc(sizeof *y);
  y = x -> right;
  x -> right = y -> left;
  numberOfChangesOfElements++;

  numberOfComparison++;
  if (y -> left != NULL){
    (y -> left) -> parent = x;
    numberOfChangesOfElements++;
  }
  y -> parent = x -> parent;

  numberOfComparison++;
  if (x -> parent == NULL)
    root = y;
  else if (x == (x -> parent) -> left)
    (x -> parent) -> left = y;
  else
    (x -> parent) -> right = y;
  y -> left = x;
  x -> parent = y;
  numberOfChangesOfElements++;
}

void Splay::rightRotate(Element * x){
  Element * y = (Element*)malloc(sizeof *y);
  y = x -> left;
  x -> left = y -> right;
  numberOfChangesOfElements++;

  numberOfComparison++;
  if (y -> right != NULL){
    (y -> right) -> parent = x;
    numberOfChangesOfElements++;
  }
  y -> parent = x -> parent;

  numberOfComparison++;
  if (x -> parent == NULL)
    root = y;
  else if (x == (x -> parent) -> left)
    (x -> parent) -> left = y;
  else
    (x -> parent) -> right = y;
  y -> right = x;
  x -> parent = y;
  numberOfChangesOfElements++;
}

void Splay::del(std::string s){
  numberOfDel++;
  Element * z = (Element*)malloc(sizeof *z);
  if (find(s)){
    z = getElement(s);
    splay(z);
    numberOfComparison++;
    if ((z -> left != NULL) && (z -> right != NULL)){
      Element * minLess = (Element*)malloc(sizeof *minLess);
      minLess = z -> left;
      while (minLess -> right != NULL){
        minLess = minLess -> right;
        numberOfComparison++;
      }
      minLess -> right = z -> right;
      (z -> right) -> parent = minLess;
      (z -> left) -> parent = NULL;
      root = z -> left;
      numberOfChangesOfElements += 2;
    }
    else if (z -> right != NULL){
      (z -> right) -> parent = NULL;
      root = z -> right;
      numberOfChangesOfElements++;
    }
    else if (z -> left != NULL){
      (z -> left) -> parent = NULL;
      root = z -> left;
      numberOfChangesOfElements++;
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
  numberOfSearch++;
  std::cout << find(s) << "\n";
}

bool Splay::find(std::string s){

  Element * previous = (Element*)malloc(sizeof *previous);
  previous = NULL;
  Element * z = (Element*)malloc(sizeof *z);
  z = root;

  while (z != NULL){
    numberOfComparison++;
    previous = z;
    numberOfComparison++;
    if (s < (z -> key))
      z = (z -> left);
    else if (s > (z -> key))
      z = (z -> right);
    else{
      splay(z);
      return true;
    }
  }
  numberOfComparison++;
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
    numberOfComparison++;
    previous = z;
    numberOfComparison++;
    if (s < (z -> key))
      z = (z -> left);
    else if (s > (z -> key))
      z = (z -> right);
    else{
      splay(z);
      return z;
    }
  }
  numberOfComparison++;
  if (previous != NULL){
    splay(previous);
    return NULL;
  }

  return NULL;
}

void Splay::inorderTreeWalk(Element * x){
  numberOfComparison++;
  if (x != NULL){
    inorderTreeWalk(x -> left);
    std::cout << x -> key << " ";
    inorderTreeWalk(x -> right);
  }
}

void Splay::inorder(){
  numberOfInOrder++;
  if (root != NULL)
    inorderTreeWalk(root);
  std::cout<<"\n";
}
