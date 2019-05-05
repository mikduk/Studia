#include "NewGraph.h"

using namespace std;

NewGraph::NewGraph(int nn, int mm):Graph(nn, mm){}

void NewGraph::addEdge(int u, int v){
  Graph::addEdge(u, v, 1);
}

void NewGraph::dfsInit(){
  for (int u = 0; u < n; u++){
    color[u] = white;
    previous[u] = -1;
  }
}

void NewGraph::dfs(){
  int time = 0;
  for (int u = 0; u < n; u++){
    if(color[u] == white)
      dfsVisit(u, time);
  }
}

void NewGraph::dfsVisit(int u, int time){
  time++;
  d[u] = time;
  color[u] = grey;
  for (int v = 0; v < n; v++)
    if (adjacencyMatrix[u][v] >= 0)
      if (color[v] == white){
        previous[v] = u;
        dfsVisit(v, time);
      }
  color[u] = black;
  time++;
  f[u] = time;
}

void NewGraph::dfsT(){
  for (int u = 0; u < n; u++){
    color[u] = white;
    previous[u] = -1;
  }
  int time = 0;

  PriorityQueue F;
  for (int u = 0; u < n; u++)
    F.insert(u, f[u]);

  while(!F.empty()){
    int u = F.pop();
    if(color[u] == white)
      dfsVisitT(u, time);
  }
}

void NewGraph::dfsVisitT(int u, int time){
  time++;
  d[u] = time;
  color[u] = grey;
  for (int v = 0; v < n; v++)
    if (adjacencyMatrix[v][u] >= 0)
      if (color[v] == white){
        previous[v] = u;
        dfsVisit(v, time);
      }
  color[u] = black;
  time++;
  f[u] = time;
}

void NewGraph::printStronglyConnectedComponents(){
  for (int i = 0; i < n; i++)
    cout << "i: " << (char) (i+97) << ", i.d = " << d[i] << ", i.f = " << f[i] << endl;
}

void NewGraph::stronglyConnectedComponents(){
  color = new colour[n];
  previous = new int[n];
  d = new int[n];
  f = new int[n];
  dfsInit();
  dfs();
  //dfsT();
  printStronglyConnectedComponents();
  delete [] f;
  delete [] d;
  delete [] previous;
  delete [] color;
}
