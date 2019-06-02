#include "MyGraphTest.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <queue>

MyGraphTest::MyGraphTest(int k, int i, int j){

  my_k = k;
  my_i = i;

  int k_2 = my_pow(k);
  v1 = new int * [k_2];
  v2 = new int * [k_2];

  for (int x = 0; x < k_2; x++){
    v1[x] = new int [i];
  }
  srand(time(NULL)*j*j);
  for (int x = 0; x < k_2; x++)
      v1[x] = my_rand(k_2, i);

  createV2(k_2, i);
}

MyGraphTest::~MyGraphTest(){
  for (int x = 0; x < my_pow(my_k); x++){
    delete v1[x];
    delete v2[x];
  }
  delete [] v1;
  delete [] v2;
}

int MyGraphTest::my_pow(int i){
  int pow = 1;
  for (; i > 0; i--)
    pow *= 2;
  return pow;
}

int * MyGraphTest::my_rand(int max, int i){
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

int MyGraphTest::program(){

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


  for(i = 0; i <= 2*k_2 + 1; i++){
      delete [] C[i];
      delete [] F[i];
  }
  delete [] C;
  delete [] F;

  delete [] P;
  delete [] CFP;

  return fmax;
}

void MyGraphTest::createV2(int k_2, int i){
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

}
