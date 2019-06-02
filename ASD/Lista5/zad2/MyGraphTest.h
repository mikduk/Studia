//
//  MyGraphTest.h
//  Lista 5
//
//  Created by Mikis Dukiel on 02/06/2019.
//  Copyright © 2019 Mikis Dukiel. All rights reserved.
//

#ifndef MYGRAPHTEST_H
#define MYGRAPHTEST_H


class MyGraphTest{
private:
  int ** v1;
  int ** v2;
  int my_k;
  int my_i;
public:
  MyGraphTest(int k, int i, int j);
  ~MyGraphTest();
  int program();
protected:
  int my_pow(int i);
  int * my_rand(int max, int i);
  void createV2(int k_2, int i);
};


#endif // MYGRAPHTEST_H
