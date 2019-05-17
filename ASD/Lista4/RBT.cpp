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

void RBT::leftRotate(Element * x){
  Element * y = x -> right;
  x -> right = y -> left;

  if (y -> left != NULL)
    (y -> left) -> parent = x;
  y -> parent = x -> parent;

  if (x -> parent == NULL)
    root = y;
  else if (x == (x -> parent) -> left)
    (x -> parent) -> left = y;
  else
    (x -> parent) -> right = y;
  y -> left = x;
  x -> parent = y;
}

void RBT::rightRotate(Element * x){
  Element * y = x -> left;
  x -> left = y -> right;

  if (y -> right != NULL)
    (y -> right) -> parent = x;
  y -> parent = x -> parent;

  if (x -> parent == NULL)
    root = y;
  else if (x == (x -> parent) -> left)
    (x -> parent) -> left = y;
  else
    (x -> parent) -> right = y;
  y -> right = x;
  x -> parent = y;
}

void RBT::insert(std::string s){
  //s = validation(s);
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
}

void RBT::insertFixup(Element * node){
  Element * y = (Element*)malloc(sizeof *y);
  while(node -> parent != NULL && (node -> parent) -> color == red){
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
          // case 5
        if (node == (node -> parent) -> left){
          node = node -> parent;
          rightRotate(node);
        }
        // case 6
        (node -> parent) -> color = black;
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
  Element *x, *y, *z;
  colour yOriginalColor;
  if (find(s)){
    z = getElement(s);
    y = z;
    yOriginalColor = y -> color;
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
  }
  if (yOriginalColor == black)
    deleteFixup(x);
  numberOfElements--;
}

void RBT::deleteFixup(Element * x){
  Element * w;
  while (x != NULL && x -> color == black && x != root){
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
  std::cout << find(s) << "\n";
}

void RBT::load(std::string f){

}

void RBT::inorder(){
  inorderTreeWalk(root);
  std::cout<<"\n";
}
