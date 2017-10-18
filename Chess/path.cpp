#include <cstdlib>
#include <string>
#include <map>
#include "ChessPiece.h"

using namespace std;

bool same(const string& from, const string& to)
{
  return (!from.compare(to));
}

bool str_path(const string& from, const string& to)
{
  return (from[0]-to[0] == 0 || from[1]-to[1] ==0);
}

bool diag_path(const string& from, const string& to)
{
  return (abs(from[0]-to[0]) == abs(from[1]-to[1]));
}

bool l_path(const string& from, const string& to)
{
  return ( (abs(from[0] - to[0]) == 1 && abs(from[1] - to[1]) == 2)
	   || (abs(from[0] - to[0]) == 2 && abs(from[1] - to[1]) == 1) );
}

bool adj(const string& from, const string& to)
{
  return (abs(from[0]-to[0]) <= 1 && abs(from[1]-to[1]) <=1);
}
