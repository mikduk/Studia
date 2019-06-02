#include "MyGraph.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <queue>
#include <fstream>

MyGraph::MyGraph(int k, int i){
  my_k = k;
  my_i = i;

  int k_2 = my_pow(k);
  v1 = new int * [k_2];
  v2 = new int * [k_2];

  for (int x = 0; x < k_2; x++){
    v1[x] = new int [i];
  }

  srand(time(NULL));
  for (int x = 0; x < k_2; x++)
      v1[x] = my_rand(k_2, i);

  std::cout << std::endl << "::GRAPH::" << std::endl;
  std::cout << "|V| = |L| + |R|, |L| = |R| = " << k_2 << std::endl;
  std::cout << "|E| = |L| * " << i << " = " << k_2 * my_i << std::endl;
  std::cout << std::endl << "L:" << std::endl;

  for (int x = 0; x < k_2; x++){
    std::cout << x << ": ";
    for (int y = 0; y <i; y++)
      std::cout << v1[x][y]+k_2 << " ";
    std::cout << std::endl;
  }
  createV2(k_2, i);
}

MyGraph::~MyGraph(){
  for (int x = 0; x < my_pow(my_k); x++){
    delete v1[x];
    delete v2[x];
  }
  delete [] v1;
  delete [] v2;
}

int MyGraph::my_pow(int i){
  int pow = 1;
  for (; i > 0; i--)
    pow *= 2;
  return pow;
}

int * MyGraph::my_rand(int max, int i){
  int * mrand = new int [i];
  int result;
  for (int x = 0; x < i; x++){
    generate:
    result = rand() % max;
    mrand[x] = result;
    for (int y = 0; y < x; y++)
      if (mrand[y] == mrand[x])
        goto generate;
  }
  std::sort(mrand, mrand+i);
  return mrand;
}

void MyGraph::program(){

  int k_2 = my_pow(my_k);
  std::queue <int> Q;
  int i, v, u, cp;

  int ** C = new int * [2*k_2+2];            // Macierz przepustowości krawędzi
  int ** F = new int * [2*k_2+2];            // Macierz przepływów netto
  for(i = 0; i <= 2*k_2 + 1; i++)
  {
    C[i] = new int [2*k_2+2];
    F[i] = new int [2*k_2+2];
    for(int j = 0; j <= 2*k_2 + 1; j++)
    {
      C[i][j] = 0;
      F[i][j] = 0;
    }
  }

  for(i = k_2; i < 2*k_2; i++){
    int pr = 0;
    while (v2[i-k_2][pr] != -1){
    C[i][v2[i-k_2][pr]] = 1;
    C[2*k_2][i] = 1;
    pr++;
    }
  }

  for (i = 0; i < k_2; i++)
    C[i][2*k_2+1] = 1;


  int * P = new int [2*k_2+2];              // Tablica poprzedników
  int * CFP = new int [2*k_2+2];
  int fmax = 0;

  while(true)
  {
    for(i = 0; i <= 2*k_2 + 1; i++) P[i] = -1;

    P[2*k_2] = -2;
    CFP[2*k_2] = 2*k_2+1;

    while(!Q.empty()) Q.pop();
    Q.push(2*k_2);

    bool esc = false;

    while(!Q.empty())
    {
      v = Q.front(); Q.pop();

      for(u = 0; u <= 2*k_2 + 1; u++)
      {
        cp = C[v][u] - F[v][u];
        if(cp && (P[u] == -1))
        {
          P[u] = v;
          if(CFP[v] > cp) CFP[u] = cp; else CFP[u] = CFP[v];
          if(u == 2*k_2+1)
          {
            fmax += CFP[2*k_2+1];
            i = u;
            while(i != 2*k_2)
            {
              v = P[i];
              F[v][i] += CFP[2*k_2+1];
              F[i][v] -= CFP[2*k_2+1];
              i = v;
            }
            esc = true; break;
          }
          Q.push(u);
        }
      }
      if(esc) break;
    }
    if(!esc) break;
  }
  std::cout << "Number of matches: " << fmax << std::endl << std::endl;
  if(fmax > 0)
    for(v = 0; v < 2*k_2; v++)
      for(u = 0; u < 2*k_2; u++)
        if((C[v][u] == 1) && (F[v][u] == 1))
          std::cout << u << " - " << v << std::endl;

  for(i = 0; i <= 2*k_2 + 1; i++){
      delete [] C[i];
      delete [] F[i];
  }
  delete [] C;
  delete [] F;

  delete [] P;
  delete [] CFP;
}

void MyGraph::createV2(int k_2, int i){
  std::queue <int> myQueue;
  for (int z = 0; z < k_2; z++){
    for (int x = 0; x < k_2; x++)
      for (int y = 0; y < i; y++)
        if (v1[x][y] == z){
          myQueue.push(x);
          break;
        }
    v2[z] = new int [myQueue.size() + 1];
    int counter = 0;
    while (!myQueue.empty()){
    v2[z][counter] = myQueue.front();
    myQueue.pop();
    counter++;
    }
    v2[z][counter] = -1;
  }
  std::cout << std::endl << "R:" << std::endl;
  for (int x = 0; x < k_2; x++){
    std::cout << x + k_2 << ": ";
    int y = 0;
    while (v2[x][y] != -1){
      std::cout << v2[x][y] << " ";
      y++;
    }
    std::cout << std::endl;
  }
}

void MyGraph::glpk(){
  std::fstream fin;
  int k_2 = my_pow(my_k);
  fin.open("zad4.txt", std::ios::out);
	fin << "param n := " << 2*k_2 - 1 << ";" << std::endl;
	fin << "param : E : w :=" << std::endl;
	for(int i = 0; i < k_2; i++) {
		for(int j = 0; j < my_i; j++) {
		   fin << i << " " << v1[i][j] << " " << 1 << std::endl;
		}
	}
	fin << ";" << std::endl;
	fin.close();
}
