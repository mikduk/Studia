#include "ExtendedGraph.h"
#include "Heap.h"

using namespace std;

ExtendedGraph::ExtendedGraph(int nn, int mm):Graph(nn, mm){
  setOfSets = new bool * [n];
  for (int i = 0; i < n; i++)
    setOfSets[i] = new bool [n];
}

ExtendedGraph::~ExtendedGraph(){
  for (int i = 0; i < n; i++){
    //delete [] adjacencyMatrix[i];
    delete [] setOfSets[i];
  }
  delete [] setOfSets;
  //delete [] adjacencyMatrix;
}

void ExtendedGraph::kruskal(){
  directedGraph();
  PriorityQueue A;
  for (int v = 0; v < n; v++)
    makeSet(v);
  PriorityQueue edges;
  sortEdges(edges);
  while (!edges.empty()){
    int id, u, v;
    id = edges.pop();
    u = id / n;
    v = id % n;
    if (findSet(u) != findSet(v)){
      A.insert(n*u + v, (int) adjacencyMatrix[u][v]);
      unionSet(u, v);
    }
  }
  printResult(A);
}

void ExtendedGraph::directedGraph(){
  for (int u = 0; u < n - 1; u++)
    for (int v = u + 1; v < n; v++){
      if (adjacencyMatrix[u][v] != adjacencyMatrix[v][u]){
        if (adjacencyMatrix[u][v] >= 0 && adjacencyMatrix[v][u] >= 0){
          if (adjacencyMatrix[u][v] > adjacencyMatrix[v][u])
            adjacencyMatrix[u][v] = adjacencyMatrix[v][u];
          else
            adjacencyMatrix[v][u] = adjacencyMatrix[u][v];
        }
        else{
          if (adjacencyMatrix[u][v] < 0)
            adjacencyMatrix[u][v] = adjacencyMatrix[v][u];
          else
            adjacencyMatrix[v][u] = adjacencyMatrix[u][v];
        }
      }
    }
}

void ExtendedGraph::makeSet(int v){
  for (int i = 0; i < n; i++)
    for (int j = 0; j < n; j++)
      setOfSets[i][j] = false;

  for (int i = 0; i < n; i++)
    setOfSets[i][i] = true;
}

void ExtendedGraph::sortEdges(PriorityQueue &edges){
  for (int u = 0; u < n - 1; u++)
    for (int v = u + 1; v < n; v++){
      int id = n*u + v;
      if (adjacencyMatrix[u][v] >= 0)
        edges.insert(id, (int) adjacencyMatrix[u][v]);
    }
}

int ExtendedGraph::findSet(int x){
  for (int i = 0; i < n; i++)
      if (setOfSets[i][x])
        return i;
  return -1;
}

void ExtendedGraph::unionSet(int u, int v){
  int findU, findV;
  findU = findSet(u);
  findV = findSet(v);

  for (int i = 0; i < n; i++)
    if (setOfSets[findV][i]){
      setOfSets[findV][i] = false;
      setOfSets[findU][i] = true;
    }
}

void ExtendedGraph::printResult(PriorityQueue &A){
  int id, w, sum = 0;
  while(!A.empty()){
    w = A.topPriority();
    id = A.pop();
    cout << id / n + 1 << " " << id % n + 1 << " " << w << endl;
    sum += w;
  }
  cout << "sum of each edges: " << sum << endl;
}
