#include "NewGraph.h"
#include "Element.h"
#include <queue>

using namespace std;

NewGraph::NewGraph(int nn, int mm):Graph(nn, mm){}

void NewGraph::addEdge(int u, int v){
  Graph::addEdge(u, v, 1);
}

void NewGraph::addEdgeT(int v, int u){
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

void NewGraph::dfsVisit(int u, int &time){
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
  int time = 0;

  PriorityQueue F;
  for (int u = 0; u < n; u++)
    F.insert(u, f[u]);

  while(!F.empty()){
    int u = F.pop();
    if(color[u] == white){
      dfsVisitT(u, time);}
  }
  /* // to test
  for (int u = 0; u < n; u++){
    if(color[u] == white)
      dfsVisitT(u, time);
  }
  */
}

void NewGraph::dfsVisitT(int u, int &time){
  time++;
  d[u] = time;
  color[u] = grey;
  for (int v = 0; v < n; v++)
    if (adjacencyMatrix[v][u] >= 0)
      if (color[v] == white){
        previous[v] = u;
        dfsVisitT(v, time);
      }
  color[u] = black;
  time++;
  f[u] = time;
}

void NewGraph::printStronglyConnectedComponents(PriorityQueue topologicalSort){
  cout << endl;
  bool * visited = new bool[n];

  for (int i = 0; i < n; i++)
    visited[i] = false;

  queue <Element> result;
  while (!topologicalSort.empty()){
    int i = topologicalSort.pop();
    Element e(previous[i]+1, i+1);
    result.push(e);
  }
  Element guard(-1, -1);
  result.push(guard);
  int find = result.front().getValue();

  while (result.size() > 1){
    Element e = result.front();
    if (e.getValue() == find){
      if (find != 0){
        cout << e.getValue() << " ";
        find = e.getPriority();
      }
      else{
        cout << e.getPriority() << " ";
      }
      result.pop();
      visited[e.getValue()] = true;
    }
    else if (visited[e.getPriority()]){
      result.pop();
    }
    else if (e.getValue() == e.getPriority() && e.getValue() == -1){
      result.push(e);
      result.pop();
      cout << find << endl;
      find = result.front().getValue();
    }
    else if (e.getValue() == 0){
      int del = e.getPriority();
      result.push(e);
      result.pop();
      while (!(result.front().getValue() == 0 && result.front().getPriority() == del)){
        if (result.front().getValue() != del)
          result.push(result.front());
        result.pop();
      }
      result.push(result.front());
      result.pop();
    }
    else{
      result.push(e);
      result.pop();
    }
  }
  cout << endl;
}

void NewGraph::stronglyConnectedComponents(){
  color = new colour[n];
  previous = new int[n];
  d = new int[n];
  f = new int[n];

  dfsInit();
  dfs();

  PriorityQueue topologicalSort;
  for (int u = 0; u < n; u++)
    topologicalSort.insert(u, 2*m - f[u]);

  dfsInit();
  dfsT();
  printStronglyConnectedComponents(topologicalSort);

  delete [] f;
  delete [] d;
  delete [] previous;
  delete [] color;
}
