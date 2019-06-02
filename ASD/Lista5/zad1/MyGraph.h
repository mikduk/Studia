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
  long ** flow;
  long ** capacity;
  int * parent;
  bool * visited;
  int n, m;
public:
  MyGraph(int k, int i);
  ~MyGraph();
  void addEdge(int from, int to, long cap);
  long getMaxFlow(int s, int t);
  void showGraph(int numOfVerticles);
};

class HammingCode{
	public:
    int errorCorrection(int x);
};

#endif // MYGRAPH_H
