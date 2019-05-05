//
//  ExtendedGraph.h
//  Lista 3 "Kruskal&Prim"
//
//  Created by Mikis Dukiel on 03/05/2019.
//  Copyright © 2019 Mikis Dukiel. All rights reserved.
//

#ifndef EXTENDEDGRAPH_H
#define EXTENDEDGRAPH_H
#include "Graph.h"

class ExtendedGraph :public Graph{
  protected:
    bool ** setOfSets;

  public:
    ExtendedGraph(int nn, int mm);
    ~ExtendedGraph();
    void kruskal();
    void prim();

  protected:
    void directedGraph();
    void makeSet(int v);
    void sortEdges(PriorityQueue &edges);
    int findSet(int x);
    void unionSet(int u, int v);
    void printResult(PriorityQueue &A);

};

#endif // EXTENDEDGRAPH_H
