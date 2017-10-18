#include "substring.h"
#include <cstring>

//iterative
int substring_position(const char* first, const char* second)
{
  int pos = 0;
  char temp[strlen(second)]; //check whether "first" is prefix of "temp"
  strcpy(temp, second);

  while (strlen(temp) >= strlen(first))
  {
    if (is_prefix(first, temp))
      return pos;

    //temp = temp - first character
    for (unsigned int i = 1; i <= strlen(temp); i++)
      temp[i-1] = temp[i];
    ++pos;
  }
  
  return -1;
}

bool is_prefix(const char* first, const char* second)
{
  //base case
  if (first[0] == '\0')
    return true;
  
  //check the first letter is the same and call is_prefix
  //on the remaining letters
  else if (first[0] == second[0])
  {
    char _first[strlen(first)], _second[strlen(second)];
    for (unsigned int i = 1; i <= strlen(first) + 1; i++)
    {
      _first[i-1] = first[i];
      _second[i-1] = second[i];
    }
    return is_prefix(_first, _second);
  }

  return false;
}
