#ifndef PLUGBOARD_H
#define PLUGBOARD_H

class Plugboard
{
  private:
    int config[26];
  public:  
    //CONSTRUCTOR
    Plugboard(int c[])
    {
    	for (int i = 0; i < 26; i++)
      	config[i] = c[i];
    }
    
    //FUNCTION WHICH ENCODES THE LETTER "number"
    //ACCORDING TO THE PLUGBOARD CONFIGURATION
    int encode(int number);
};

#endif
