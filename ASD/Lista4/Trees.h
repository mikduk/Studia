//
//  Trees.h
//  Lista 4
//
//  Created by Mikis Dukiel on 08/05/2019.
//  Copyright © 2019 Mikis Dukiel. All rights reserved.
//

#ifndef TREES_H
#define TREES_H
#include <string>
#include "Element.h"

class Trees{
protected:
  Element * root;
  unsigned int numberOfElements;
public:
  virtual void insert(std::string s)=0;
  virtual void del(std::string s)=0;
  virtual bool search(std::string s)=0;
  virtual void load(std::string f)=0;
  virtual void inorder()=0;
protected:
  std::string validation(std::string s);
};

class BST :public Trees{
public:
  BST();
  virtual void insert(std::string s);
  virtual void del(std::string s);
  virtual bool search(std::string s);
  virtual void load(std::string f);
  virtual void inorder();
protected:
  Element * minimum(Element * x);
  Element * maximum(Element * x);
  void inorderTreeWalk(Element * x);
};

class RBT :public Trees{
public:
  RBT();
  virtual void insert(std::string s)=0;
  virtual void del(std::string s)=0;
  virtual bool search(std::string s)=0;
  virtual void load(std::string f)=0;
  virtual void inorder()=0;
};

class Splay :public Trees{
public:
  Splay();
  virtual void insert(std::string s)=0;
  virtual void del(std::string s)=0;
  virtual bool search(std::string s)=0;
  virtual void load(std::string f)=0;
  virtual void inorder()=0;
};

#endif // TREES_H
