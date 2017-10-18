#include "enum.h"

ostream& operator<<(ostream& o, const Team& t)
{
  if (t == black)
    return o << "Black";
  else
    return o << "White";
}

Team operator!(const Team& t)
{
  if (t == black)
    return white;
  else
    return black;
}
