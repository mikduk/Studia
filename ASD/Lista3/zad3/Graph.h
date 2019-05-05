//
//  Graph.h
//  Lista 3 "Dijkstra"
//
//  Created by Mikis Dukiel on 04/05/2019.
//  Copyright © 2019 Mikis Dukiel. All rights reserved.
//

#ifndef GRAPH_H
#define GRAPH_H

#include "PriorityQueue.h"
#include <iostream>

class Graph{

protected:
  int n; // |V|
  int m; // |E|
  double ** adjacencyMatrix;
  double inf; // sum of each edges + 1
  int source;

public:
  Graph(int nn, int mm);
  ~Graph();
  void addEdge(int u, int v, double w);
  void setSource(int s);
  void dijkstra();
  void showAdjacencyMatrix();

protected:
  void correctAdjacencyMatrix();
  void createQueue(PriorityQueue &Q, double d[]);
  void initializeSingleSource(int source, double d[], int previous[]);
  void relax(int u, int v, double d[], int previous[]);
  void relax(int u, int v, double d[], int previous[], PriorityQueue &Q);
  void printResult(double d[], int previous[]);
  void printErrResult(int v, int previous[]);

};

#endif // GRAPH_H
