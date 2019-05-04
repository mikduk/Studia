//
//  main.cpp
//  Lista 3 Zadanie 2 "Dijkstra"
//
//  Created by Mikis Dukiel on 04/05/2019.
//  Copyright © 2019 Mikis Dukiel. All rights reserved.
//

#include "Graph.h"
#include "PriorityQueue.h"
#include <ctime>

using namespace std;

int main(){
  int n, m, u, v;
  double w;
  clock_t start, stop;
  cout << "n = |V| = "; cin >> n;
  cout << "m = |E| = "; cin >> m;
  Graph myGraph(n, m);
  for (int i = m; i > 0; i--){
    cout << i << ": "; cin >> u >> v >> w;
    myGraph.addEdge(u-1, v-1, w);
  }/*
  //example from "Introduction to Algorithms"
  myGraph.addEdge(0, 1, 10);
  myGraph.addEdge(0, 3, 5);
  myGraph.addEdge(1, 2, 1);
  myGraph.addEdge(1, 3, 2);
  myGraph.addEdge(2, 4, 4);
  myGraph.addEdge(3, 1, 3);
  myGraph.addEdge(3, 2, 9);
  myGraph.addEdge(3, 4, 2);
  myGraph.addEdge(4, 0, 7);
  myGraph.addEdge(4, 2, 6);
  */
  cout << "source = "; cin >> u; cout << endl;
  myGraph.setSource(u-1);
  //myGraph.showAdjacencyMatrix();
  start = clock();
  myGraph.dijkstra();
  stop = clock();
  cerr << endl << "time of program execution: " << stop - start << " ms" << endl;
  return 0;
}
