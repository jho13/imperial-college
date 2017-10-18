#include "Plugboard.h"

int Plugboard::encode(int number)
{
  //check whether "number" appears in the plugboard configuration
  int i = 0;
  while (number != config[i])
  {
    if (i == 25)
      return number;
    i++;
  }

  //swap numbers appropriately
  if (i%2 == 0)
    return config[i+1];
  else
    return config[i-1];
}


