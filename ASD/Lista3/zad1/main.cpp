#include "PriorityQueue.h"
#include "Heap.h"
#include "Element.h"
#include <iostream>
#include <cctype>
#include <string>

using namespace std;

int insertX(string x){
  int stop=7;
  for (int i = 7; i < (int) x.length(); i++){

    if (isdigit(x[i]) == false && x[i] != '-'){
      stop = i;
      break;
    }
  }

  x = x.substr(7, stop - 7);
  x = x.substr(0, 6);

  return stoi(x);
}

int insertP(string p){
  int start = (int) p.length() - 1;
  for (int i = start; i > 0; i--){
    if (isdigit(p[i]) == false && p[i] != '-')
      break;
    start--;
  }
  p = p.substr(start+1, p.length()-start);

  return stoi(p);
}

int priorityX(string x){
  int stop=10;
  for (int i = 10; i < (int) x.length(); i++){

    if (isdigit(x[i]) == false && x[i] != '-'){
      stop = i;
      break;
    }
  }

  x = x.substr(10, stop - 10);
  x = x.substr(0, 9);

  return stoi(x);
}

int priorityP(string p){
  int start = (int) p.length() - 1;
  for (int i = start; i > 0; i--){
    if (isdigit(p[i]) == false && p[i] != '-')
      break;
    start--;
  }
  p = p.substr(start+1, p.length()-start);

  return stoi(p);
}

int main(){
  PriorityQueue myQueue;
  int m;
  cout << "Number of operations: "; cin >> m;
  while (m > 0){
    string x;
    getline(cin, x);
    char x1 = x[0];
    switch (x1){
      case 'i':
        if (x.substr(0,6) == "insert"){
          myQueue.insert(insertX(x), insertP(x));
          m--;
        }
        break;
      case 'e':
        if (x == "empty"){
            myQueue.empty();
            m--;
        }
        break;
      case 't':
        if (x == "top"){
          myQueue.top();
          m--;
        }
        break;
      case 'p':
        if (x == "pop"){
          myQueue.pop();
          m--;
        }
        else if (x == "print"){
          myQueue.print();
          m--;
        }
        else if (x.substr(0,9) == "priority"){
          myQueue.priority(priorityX(x), priorityP(x));
          m--;
        }
        break;
     }
  }
  cout << ":: Koniec programu ::" << endl;
  return 0;
}
