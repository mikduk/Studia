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

std::string Trees::validation(std::string s){
  while (!( ((((char) s[0] > 64) && ((char) s[0] < 91)) || (((char) s[0] > 96) && ((char) s[0] < 123))) && ((((char) s[s.length()-1] > 64) && ((char) s[s.length()-1] < 91)) || (((char) s[s.length()-1] > 96) && ((char) s[s.length()-1] < 123))))){
    if (!((((char) s[0] > 64) && ((char) s[0] < 91)) || (((char) s[0] > 96) && ((char) s[0] < 123))))
      s = s.substr(1, s.length()-1);
    if (!((((char) s[s.length()-1] > 64) && ((char) s[s.length()-1] < 91)) || (((char) s[s.length()-1] > 96) && ((char) s[s.length()-1] < 123))))
      s = s.substr(0, s.length()-1);
  }
  return s;
}

void BST::insert(std::string s){ std::cout<<"[insert] s: "<<s<<"\n";
  s = validation(s); std::cout<<"[insert] s: "<<s<<"\n";
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
  std::cout<<"[inorder]\n";
  inorder();
  std::cout<<"[/inorder]\n";
  std::cout << "root: " << root << " " << root -> key << " " << root -> left << " " << root -> right << "\n";
}

void BST::inorderTreeWalk(Element * x){
  if (x != NULL){
    inorderTreeWalk(x -> left);
    //std::cout << x << " " << x -> key << " " << x -> left << " " << x -> right << " " << x -> parent << "\n";
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

void BST::del(std::string s){}
bool BST::search(std::string s){return true;}
void BST::load(std::string f){}
void BST::inorder(){
  inorderTreeWalk(root);
  std::cout<<"\n";
}
