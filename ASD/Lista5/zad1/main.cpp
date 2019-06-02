#include "MyGraph.h"
#include <iostream>
#include <string.h>
#include <stdio.h>
#include <ctime>
#include <time.h>
#include <cstdlib>
#include <math.h>
#include <algorithm>

int main(int argc, const char * argv[]){

  clock_t start;

     if((argc == 5 || argc == 3) && !strcmp(argv[1], "--size")) {

       int k = atoi(argv[2]); // k-dimensional hypercube
       if(k < 0 || k > 16){
           std::cout << "k must be greater than 1 and lower than 16" << std::endl;
           return 1;
       }
       else{

         int numOfVertices = exp2(k);
         int numOfEdges = numOfVertices * k;
         int source = 0;
         int target = numOfVertices - 1; // 2^k-1

         std::cout << "|V| = " << numOfVertices << std::endl;
         std::cout << "|E| = " << numOfEdges << std::endl;


       // create k-dimensional hypercube
       MyGraph * hypercube = new MyGraph(numOfVertices, numOfEdges);

       HammingCode * hamCode = new HammingCode();

       for(int i = 0; i < numOfVertices; i++) {
         for(int j = 0; j < numOfVertices; j++) {
           int l = (int) std::max((hamCode -> errorCorrection(i)), (hamCode -> errorCorrection(j)));
           srand(time(NULL));
           int cap = (rand() % ((int)exp2(l)+1)) + 1; // [1, 2^l]
           // init capacity in hypercube
           hypercube -> addEdge(i, j, cap);
         }
       }
       hypercube -> showGraph(numOfVertices);
       start = clock();
       std::cout << "Result: " << hypercube -> getMaxFlow(source, target) << std::endl;
       std::cerr << "Time: " << clock() - start << std::endl;

 }
}
else{
  std::cout << "You must write \"./zad1 --size k" << std::endl;
  return 1;
}
}
