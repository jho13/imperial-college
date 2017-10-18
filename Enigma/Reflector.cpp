#include "Reflector.h"

int Reflector::encode(int number)
{
	//find index for which config[index] = number)
  int i = 0;
  while (number != config[i])
    i++;

	//swap numbers appropriately
  if (i%2 == 0)
    return config[i+1];
  else
    return config[i-1];
}
      
