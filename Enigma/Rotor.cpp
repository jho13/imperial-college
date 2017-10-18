#include "Rotor.h"

bool Rotor::is_notch()
{
  if (notches[relpos])
    return true;
  return false;
}

void Rotor::rotate()
{
  //change config
  int temp = config[0] - 0;
  for (int i = 0; i < 25; i++)
    config[i] = ((i + (config[i+1] - (i+1)) + 26) % 26);
  config[25] = (((25+ temp) + 26) % 26);
  
  //change relpos
  relpos = ((relpos + 1) % 26); 
}

int Rotor::encode_in(int number)
{
  return config[number];
}

int Rotor::encode_out(int number)
{
  int index = 0;
  while (config[index] != number)
    index++;
  return index;
}
