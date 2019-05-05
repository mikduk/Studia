//
//  main.cpp
//  Lista 3 Zadanie 3 "Kruskal&Prim"
//
//  Created by Mikis Dukiel on 04/05/2019.
//  Copyright © 2019 Mikis Dukiel. All rights reserved.
//

#include "ExtendedGraph.h"

using namespace std;

int main(int argc, const char * argv[]){
  if (argc != 2){
    cout << "Only ./zad3 [-p/-k] is correct" << endl;
  }
  else{
  bool kruskal;
  if (argv[1][0] == '-' && argv[1][1] == 'k')
    kruskal = true;
  else if (argv[1][0] == '-' && argv[1][1] == 'p')
    kruskal = false;
  else{
    cout << "Only -p or -k are correct" << endl;
    return 0;
    }
  int n, m, u, v;
  double w;
  cout << "n = |V| = "; cin >> n;
  cout << "m = |E| = "; cin >> m;
  ExtendedGraph myGraph(n, m);
  for (int i = m; i > 0; i--){
    cout << i << ": "; cin >> u >> v >> w;
    myGraph.addEdge(u-1, v-1, w);
  }

  //example from "Introduction to Algorithms" n=9 m=14
  /*
  myGraph.addEdge(0, 1, 4);
  myGraph.addEdge(0, 7, 8);
  myGraph.addEdge(1, 2, 8);
  myGraph.addEdge(1, 7, 11);
  myGraph.addEdge(2, 3, 7);
  myGraph.addEdge(2, 5, 4);
  myGraph.addEdge(2, 8, 2);
  myGraph.addEdge(3, 4, 9);
  myGraph.addEdge(3, 5, 14);
  myGraph.addEdge(4, 5, 10);
  myGraph.addEdge(5, 6, 2);
  myGraph.addEdge(6, 7, 1);
  myGraph.addEdge(6, 8, 6);
  myGraph.addEdge(7, 8, 7);
  */

  if (kruskal)
    myGraph.kruskal();
  else
    myGraph.prim();
      
  }
  return 0;
}
