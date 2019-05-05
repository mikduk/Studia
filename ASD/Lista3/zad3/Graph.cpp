//
//  Graph.cpp
//  Lista 3 "Dijkstra"
//
//  Created by Mikis Dukiel on 04/05/2019.
//  Copyright © 2019 Mikis Dukiel. All rights reserved.
//

#include "Graph.h"
#include "PriorityQueue.h"
#include <iostream>

using namespace std;

Graph::Graph(int nn, int mm){
  n = nn;
  m = mm;
  source = 0;
  inf = 1;
  adjacencyMatrix = new double * [n];
  for (int i = 0; i < n; i++)
    adjacencyMatrix[i] = new double [n];

  for (int i = 0; i < n; i++)
    for (int j = 0; j < n; j++)
      adjacencyMatrix[i][j] = -1;

  for (int i = 0; i < n; i++)
    adjacencyMatrix[i][i] = 0;
}

Graph::~Graph(){
  for (int i = 0; i < n; i++)
    delete [] adjacencyMatrix[i];
  delete [] adjacencyMatrix;
}

void Graph::addEdge(int u, int v, double w){
  if (w >= 0)
    if (adjacencyMatrix[u][v] > w || adjacencyMatrix[u][v] < 0){
      adjacencyMatrix[u][v] = w;
      inf += w;
    }
}

void Graph::setSource(int s){
  source = s;
}

void Graph::correctAdjacencyMatrix(){
  for (int i = 0; i < n; i++)
    for (int j = 0; j < n; j++)
      if (adjacencyMatrix[i][j] == -1)
        adjacencyMatrix[i][j] = inf;
}

void Graph::createQueue(PriorityQueue &Q, double d[]){
  for (int v = 0; v < n; v++){
    Q.insert(v, (int) d[v]);
  }
}

void Graph::initializeSingleSource(int source, double d[], int previous[]){
  for (int v = 0; v < n; v++){
    d[v] = inf;
    previous[v] = -1;
  }
  d[source] = 0;
}

void Graph::relax(int u, int v, double d[], int previous[]){
  if (d[v] > (d[u] + adjacencyMatrix[u][v])){
    d[v] = d[u] + adjacencyMatrix[u][v];
    previous[v] = u;
  }
}

void Graph::relax(int u, int v, double d[], int previous[], PriorityQueue &Q){
  if (d[v] > (d[u] + adjacencyMatrix[u][v])){
    d[v] = d[u] + adjacencyMatrix[u][v];
    previous[v] = u;
    Q.priority(v, (int) d[v]);
  }
}

void Graph::printResult(double d[], int previous[]){
  for (int v = 0; v < n; v++){
    cout << v+1 << " " << d[v] << "\n";
    printErrResult(v, previous);
  }
}

void Graph::printErrResult(int v, int previous[]){
  cerr << v+1;
  while (previous[v] != -1){
    cerr << " <-(" << adjacencyMatrix[previous[v]][v] << ")- " << previous[v]+1;
    v = previous[v];
  }
  cerr << endl;
}

void Graph::dijkstra(){
    double * d = new double [n];
    int * previous = new int [n];
    correctAdjacencyMatrix();
    initializeSingleSource(source, d, previous);
    PriorityQueue Q;
    createQueue(Q, d);

    while (!Q.empty()){
      int u = Q.pop();
      for (int v = 0; v < n; v++){
        if (adjacencyMatrix[u][v] != inf)
          relax(u, v, d, previous, Q);
      }
    }
    printResult(d, previous);
    delete [] previous;
    delete [] d;
}

void Graph::showAdjacencyMatrix(){
  for (int i = 0; i < n; i++){
    for (int j = 0; j < n; j++)
      cout << adjacencyMatrix[i][j] << " ";
    cout << endl;
  }
   cout << "inf = " << inf << endl;
}
