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
  virtual void search(std::string s)=0;
  virtual void load(std::string f)=0;
  virtual void inorder()=0;
protected:
  std::string validation(std::string s);
  virtual bool find(std::string s)=0;
  virtual Element * getElement(std::string s)=0;

};

class BST :public Trees{
public:
  BST();
  virtual void insert(std::string s);
  virtual void del(std::string s);
  virtual void search(std::string s);
  virtual void load(std::string f);
  virtual void inorder();
protected:
  Element * minimum(Element * x);
  Element * maximum(Element * x);
  void inorderTreeWalk(Element * x);
  virtual bool find(std::string s);
  virtual Element * getElement(std::string s);
  void transplant(Element * u, Element * v);
};

class RBT :public Trees{
public:
  RBT();
  virtual void insert(std::string s)=0;
  virtual void del(std::string s)=0;
  virtual void search(std::string s)=0;
  virtual void load(std::string f)=0;
  virtual void inorder()=0;
  virtual bool find(std::string s);
protected:
  virtual Element * getElement(std::string s);
};

class Splay :public Trees{
public:
  Splay();
  virtual void insert(std::string s)=0;
  virtual void del(std::string s)=0;
  virtual void search(std::string s)=0;
  virtual void load(std::string f)=0;
  virtual void inorder()=0;
  virtual bool find(std::string s);
protected:
  virtual Element * getElement(std::string s);
};

#endif // TREES_H
