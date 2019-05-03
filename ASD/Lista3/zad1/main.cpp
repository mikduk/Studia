#include "PriorityQueue.h"
#include "Heap.h"
#include "Element.h"
#include <iostream>
#include <cctype>
#include <string>

using namespace std;

int insertX(string x){
  int stop=6;
  for (int i = 6; i < (int) x.length(); i++){
    if (isdigit(x[i]) == false){
      stop = i;
      break;
    }
  }
  x = x.substr(6, stop - 6);
  x = x.substr(0, 5);
  //int xi = atoi(x);

  return 0;
}

int main(){
  PriorityQueue myQueue;
  myQueue.insert(2,1);
  int m;
  cout << "Number of operations: "; cin >> m;
  while (m > 0){
    string x;
    getline(cin, x);
    char x1 = x[0];
    switch (x1){
      case 'i':
        if (x.substr(0,6) == "insert") cout << "true" << endl;
        else cout << "false" << endl;
        break;
      case 'e':
        if (x.substr(0,5) == "empty"){
            //myQueue.empty();
            m--;
        }
        else cout << "false" << endl;
        break;
      case 't':
        cout << "ins" << endl;
        break;
      case 'p':
        cout << "ins" << endl;
        break;
      default:
        cout << "sd" << endl;
        break;
     }
  }
  return 0;
}
