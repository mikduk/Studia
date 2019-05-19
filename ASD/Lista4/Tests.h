//
//  Tests.h
//  Lista 4
//
//  Created by Mikis Dukiel on 19/05/2019.
//  Copyright © 2019 Mikis Dukiel. All rights reserved.
//

#ifndef TESTS_H
#define TESTS_H
#include <string>
#include "Trees.h"

int test(Trees * tree);
void loadInsert(Trees * tree, std::string f, clock_t &time);
void loadDelete(Trees * tree, std::string f, clock_t &time);
void loadSearch(Trees * tree, std::string f, clock_t &time);

#endif // TESTS_H
