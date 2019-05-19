//
//  RBT.cpp
//  Lista 4
//
//  Created by Mikis Dukiel on 16/05/2019.
//  Copyright © 2019 Mikis Dukiel. All rights reserved.
//

#include "Trees.h"
#include <iostream>

RBT::RBT(){
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

void RBT::leftRotate(Element * x){
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

void RBT::rightRotate(Element * x){
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

void RBT::insert(std::string s){
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
    root -> color = black;
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

    Element * node;
    node = (Element*)malloc(sizeof *node);
    node -> key = s;
    node -> parent = p;

    numberOfComparison++;
    if (y == NULL)
      root = node;
    else if (node -> key < p -> key)
      (p -> left) = node;
    else
      (p -> right) = node;

    node -> left = NULL;
    node -> right = NULL;
    node -> color = red;
    insertFixup(node);
  }
  numberOfElements++;
  if (numberOfElements > maxNumberOfElements)
    maxNumberOfElements = numberOfElements;
}

void RBT::insertFixup(Element * node){
  Element * y = (Element*)malloc(sizeof *y);
  while(node -> parent != NULL && (node -> parent) -> color == red){
    numberOfComparison++;
    if ((node -> parent) -> parent != NULL && node -> parent == ((node -> parent) -> parent) -> left){
      y = ((node -> parent) -> parent) -> right;
      // case 1
      if (y != NULL && y -> color == red){
        (node -> parent) -> color = black;
        y -> color = black;
        ((node -> parent) -> parent) -> color = red;
        node = (node -> parent) -> parent;
      }
      else{
        numberOfComparison++;
          // case 2
        if (node == (node -> parent) -> right){
          node = node -> parent;
          leftRotate(node);
        }
        // case 3
        (node -> parent) -> color = black;
        ((node -> parent) -> parent) -> color = red;
        rightRotate((node -> parent) -> parent);
      }
    }
    else{
      if ((node -> parent) -> parent != NULL)
        y = ((node -> parent) -> parent) -> left;
      // case 4
      if (y != NULL && y -> color == red){
        (node -> parent) -> color = black;
        y -> color = black;
        ((node -> parent) -> parent) -> color = red;
        node = (node -> parent) -> parent;
      }
      else{
        numberOfComparison++;
          // case 5
        if (node == (node -> parent) -> left){
          node = node -> parent;
          rightRotate(node);
        }
        // case 6
        (node -> parent) -> color = black;
        numberOfComparison++;
        if ((node -> parent) -> parent != NULL){
          ((node -> parent) -> parent) -> color = red;
          leftRotate((node -> parent) -> parent);
        }
      }
    }
  }
  root -> color = black;
}

void RBT::inorderTreeWalk(Element * x){
  numberOfComparison++;
  if (x != NULL){
    inorderTreeWalk(x -> left);
    std::cout << x -> key << " ";
    inorderTreeWalk(x -> right);
  }
}

Element * RBT::minimum(Element * x){
  while (x -> left != NULL){
    x = x -> left;
    numberOfComparison++;
  }
  numberOfComparison++;
  return x;
}

Element * RBT::maximum(Element * x){
  while (x -> right != NULL){
    x = x -> right;
    numberOfComparison++;
  }
  numberOfComparison++;
  return x;
}

bool RBT::find(std::string s){
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

Element * RBT::getElement(std::string s){
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

void RBT::transplant(Element * u, Element * v){
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

void RBT::del(std::string s){
  numberOfDel++;
  Element *x, *y, *z;
  colour yOriginalColor;
  if (find(s)){
    z = getElement(s);
    y = z;
    yOriginalColor = y -> color;
    numberOfComparison++;
    if (z -> left == NULL){
      x = z -> right;
      transplant(z, z -> right);
    }
    else if (z -> right == NULL){
      x = z -> left;
      transplant(z, z -> left);
    }
    else{
      y = minimum(z -> right);
      yOriginalColor = y -> color;
      x = y -> right;
      numberOfComparison++;
      if (y -> parent == z){
        if (x != NULL)
        x -> parent = y;}
      else{
          transplant(y, y -> right);
          y -> right = z -> right;
          (y -> right) -> parent = y;
        }
      transplant(z, y);
      y -> left = z -> left;
      (y -> left) -> parent = y;
      y -> color = z -> color;
    }
  if (yOriginalColor == black)
    deleteFixup(x);
  numberOfElements--;
  }
}

void RBT::deleteFixup(Element * x){
  Element * w;
  while (x != NULL && x -> color == black && x != root){
    numberOfComparison++;
    if (x == (x -> parent) -> left){
      w = (x -> parent) -> right;
      // case 1
      if (w != NULL && w -> color == red){
        w -> color = black;
        (x -> parent) -> color = red;
        leftRotate(x -> parent);
        w = (x -> parent) -> right;
      }
      // case 2
      if ((w -> left == NULL || (w -> left) -> color == black) && (w -> right == NULL || (w -> right) -> color == black)){
        w -> color = red;
        x = x -> parent;
      }
      else{
          // case 3
        if (w -> right == NULL || (w -> right) -> color == black){
          (w -> left) -> color = black;
          w -> color = black;
          rightRotate(w);
          w = (x -> parent) -> right;
        }
        // case 4
        w -> color = (x -> parent) -> color;
        (x -> parent) -> color = black;
        (w -> right) -> color = black;
        leftRotate(x -> parent);
        x = root;
      }
    }
    else{
      w = (x -> parent) -> left;
      // case 5
      if (w != NULL && w -> color == red){
        w -> color = black;
        (x -> parent) -> color = red;
        leftRotate(x -> parent);
        if (x -> parent != NULL)
        w = (x -> parent) -> left;
      }
      // case 6
      if ((w -> left == NULL || (w -> left) -> color == black) && (w -> right == NULL || (w -> right) -> color == black)){
        w -> color = red;
        x = x -> parent;
      }
      else{
          // case 7
        if (w -> left == NULL || (w -> left) -> color == black){
          (w -> right) -> color = black;
          w -> color = black;
          leftRotate(w);
          w = (x -> parent) -> left;
        }
        // case 8
        w -> color = (x -> parent) -> color;
        (x -> parent) -> color = black;
        (w -> left) -> color = black;
        rightRotate(x -> parent);
        x = root;
      }
    }
  }
}

void RBT::search(std::string s){
  numberOfSearch++;
  std::cout << find(s) << "\n";
}

void RBT::inorder(){
  numberOfInOrder++;
  if (root != NULL)
    inorderTreeWalk(root);
  std::cout<<"\n";
}
