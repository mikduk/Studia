//
//  NewGraph.h
//  Lista 3 "Składowe silnie spójne"
//
//  Created by Mikis Dukiel on 05/05/2019.
//  Copyright © 2019 Mikis Dukiel. All rights reserved.
//

#ifndef NEWGRAPH_H
#define NEWGRAPH_H
#include "Graph.h"

enum colour{
  white = 0,
  grey = 1,
  black = 2
};

class NewGraph :public Graph{

  protected:
    colour * color;
    int * previous;
    int * d;
    int * f;
  public:
    NewGraph(int nn, int mm);
    void addEdge(int u, int v);
    void stronglyConnectedComponents();

  protected:
    void dfsInit();
    void dfs();
    void dfsT();
    void dfsVisit(int u, int time);
    void dfsVisitT(int u, int time);
    void printStronglyConnectedComponents();

};

#endif // NEWGRAPH_H
