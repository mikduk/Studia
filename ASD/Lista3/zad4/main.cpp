//
//  main.cpp
//  Lista 3 Zadanie 4 "Składowe silnie spójne"
//
//  Created by Mikis Dukiel on 05/05/2019.
//  Copyright © 2019 Mikis Dukiel. All rights reserved.
//

#include "NewGraph.h"

using namespace std;

int main(int argc, const char * argv[]){

  int n, m, u, v;
  cout << "n = |V| = "; cin >> n;
  cout << "m = |E| = "; cin >> m;
  NewGraph myGraph(n, m);
  /*
  for (int i = m; i > 0; i--){
    cout << i << ": "; cin >> u >> v >> w;
    myGraph.addEdge(u-1, v-1);
  }
  */
  //example from "Introduction to Algorithms" n=8 m=15
  /*
  myGraph.addEdge(0, 1);
  myGraph.addEdge(0, 4);
  myGraph.addEdge(1, 2);
  myGraph.addEdge(1, 4);
  myGraph.addEdge(1, 5);
  myGraph.addEdge(2, 3);
  myGraph.addEdge(2, 6);
  myGraph.addEdge(3, 2);
  myGraph.addEdge(3, 7);
  myGraph.addEdge(4, 0);
  myGraph.addEdge(4, 5);
  myGraph.addEdge(5, 6);
  myGraph.addEdge(6, 5);
  myGraph.addEdge(6, 7);
  myGraph.addEdge(7, 7);
  */
  // example for DFS from "Introduction to Algorithms" n=6 m=8

  myGraph.addEdge(0, 1);
  myGraph.addEdge(0, 3);
  myGraph.addEdge(1, 4);
  myGraph.addEdge(2, 4);
  myGraph.addEdge(2, 5);
  myGraph.addEdge(3, 1);
  myGraph.addEdge(4, 3);
  myGraph.addEdge(5, 5);  

  myGraph.stronglyConnectedComponents();

  return 0;
}
