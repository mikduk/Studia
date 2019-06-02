#include "MyGraph.h"
#include <iostream>
#include <string.h>
#include <stdio.h>
#include <ctime>

int main(int argc, const char * argv[]){

  if (argc != 5  || strcmp(argv[1], "--size") || strcmp(argv[3], "--degree")){
    std::cout << "You must write \"./zad2 --size k --degree i" << std::endl;
    return 1;
  }

  int k = atoi(argv[2]);
  int i = atoi(argv[4]);
  clock_t start, stop;

  MyGraph G(k, i);
  std::cout << std::endl;
  start = clock();
  G.program();
  stop = clock();
  std::cerr << std::endl << "Duration of the entire program: "  << stop - start << " ms" << std::endl;
  return 0;
}
