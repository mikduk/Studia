#include "MyGraph.h"
#include "MyGraphTest.h"
#include <iostream>
#include <string.h>
#include <stdio.h>
#include <ctime>
#include <time.h>
#include <cstdlib>

int main(int argc, const char * argv[]){

if (argc == 6 && !strcmp(argv[5], "--test")){

  int k = atoi(argv[2]);
  int i = atoi(argv[4]);
  int sum = 0;
  clock_t start, times = 0;
  int x = 10000;
  for (int j = 0; j < x; j++){
  MyGraphTest *G = new MyGraphTest(k, i, j);
  start = clock();
  sum += G -> program();
  times += (clock()-start);
  delete G;
  }

  std::cout << "k = " << k << ", i = " << i << std::endl;
  std::cout << "avg matches: " << (float) sum / x<< std::endl;
  std::cout << "avg time: " << times / x << " ms" << std::endl;
  return 0;
}
  else if (argc != 5  || strcmp(argv[1], "--size") || strcmp(argv[3], "--degree")){
    std::cout << "You must write \"./zad2 --size k --degree i" << std::endl;
    return 1;
  }

  int k = atoi(argv[2]);
  int i = atoi(argv[4]);
  clock_t start, stop;

  if (k < i){
    std::cout << "k musn't be lower than i" << std::endl;
    return 1;
  }
  else if (k > 16 || k < 1){
    std::cout << "k must be greater than 1 and lower than 16" << std::endl;
    return 1;
  }

  MyGraph G(k, i);
  std::cout << std::endl;
  start = clock();
  G.program();
  stop = clock();
  std::cerr << std::endl << "Duration of the entire program: "  << stop - start << " ms" << std::endl;
  return 0;
}
