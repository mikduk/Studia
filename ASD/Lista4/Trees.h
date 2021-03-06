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
public:
  Element * root;
  unsigned int numberOfElements;
  unsigned int maxNumberOfElements;
  unsigned int numberOfInsert;
  unsigned int numberOfDel;
  unsigned int numberOfSearch;
  unsigned int numberOfLoad;
  unsigned int numberOfInOrder;
  unsigned int numberOfComparison;
  unsigned int numberOfChangesOfElements;
public:
  virtual void insert(std::string s)=0;
  virtual void del(std::string s)=0;
  virtual void search(std::string s)=0;
          void load(std::string f);
  virtual void inorder()=0;
  std::string validation(std::string s);
  void statistic();
protected:
  virtual bool find(std::string s)=0;
  virtual Element * getElement(std::string s)=0;

};

class BST :public Trees{
public:
  BST();
  virtual void insert(std::string s);
  virtual void del(std::string s);
  virtual void search(std::string s);
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
  virtual void insert(std::string s);
  virtual void del(std::string s);
  virtual void search(std::string s);
  virtual void inorder();
protected:
  Element * minimum(Element * x);
  Element * maximum(Element * x);
  void leftRotate(Element * x);
  void rightRotate(Element * x);
  void insertFixup(Element * node);
  void deleteFixup(Element * node);
  void inorderTreeWalk(Element * x);
  virtual bool find(std::string s);
  virtual Element * getElement(std::string s);
  void transplant(Element * u, Element * v);
};

class Splay :public Trees{
public:
  Splay();
  virtual void insert(std::string s);
  virtual void del(std::string s);
  virtual void search(std::string s);
  virtual void inorder();
protected:
          void splay(Element * x);
          void leftRotate(Element * x);
          void rightRotate(Element * x);
          void inorderTreeWalk(Element * x);
  virtual bool find(std::string s);
  virtual Element * getElement(std::string s);
};

class AllOfThem :public Trees{
public:
  BST bst_tree; BST * bst;
  RBT rbt_tree; RBT * rbt;
  Splay splay_tree; Splay * splay;
  AllOfThem();
  virtual void insert(std::string s);
  virtual void del(std::string s);
  virtual void search(std::string s);
          void load(std::string f);
  virtual void inorder();
          void statistic();
protected:
  virtual bool find(std::string s);
  virtual Element * getElement(std::string s);
};

#endif // TREES_H
