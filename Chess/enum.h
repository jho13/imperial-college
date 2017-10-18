#ifndef ENUM_H
#define ENUM_H

#include <iostream>

using namespace std;

enum Team{black, white};

/****overload operators*****/

ostream& operator<<(ostream& o, const Team& t);

Team operator!(const Team& t);

#endif
