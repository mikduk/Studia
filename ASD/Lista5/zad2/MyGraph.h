//
//  MyGraph.h
//  Lista 5
//
//  Created by Mikis Dukiel on 01/06/2019.
//  Copyright © 2019 Mikis Dukiel. All rights reserved.
//

#ifndef MYGRAPH_H
#define MYGRAPH_H


class MyGraph{
private:
  int ** v1;
  int ** v2;
  int my_k;
  int my_i;
public:
  MyGraph(int k, int i);
  ~MyGraph();
  void program();
  void glpk();
protected:
  int my_pow(int i);
  int * my_rand(int max, int i);
  void createV2(int k_2, int i);
};


#endif // MYGRAPH_H
