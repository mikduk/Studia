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
  Element nil("*nil*", NULL, NULL, NULL);
  tree.push_back(nil);
}

void BST::insert(std::string s){ std::cout<<"[insert] s: "<<s<<"\n";
  if (numberOfElements == 0){
    Element * nil = &tree[0]; std::cout << "nil: " << nil << "\n";
    Element root(s, nil, nil, nil);
    tree.push_back(root);
  }
  else{
    Element * y = &tree[0]; // NIL
    Element * x = &tree[1]; // root
    std::cout<<"y = " << y << ", x = "<< x <<"\n";
    std::cout<<"key: "<< x -> key << ", left: " << x->left << "\n";
    /*while (&x != &tree[0]){
      y = x;
      if (s < (x -> key))
          x = (x -> left);
      else
          x = (x -> right);
    }*/
    Element * parent = y;
  }
  numberOfElements++;
}

void BST::del(std::string s){}
bool BST::search(std::string s){return true;}
void BST::load(std::string f){}
void BST::inorder(){}
