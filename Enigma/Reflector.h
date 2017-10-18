#ifndef REFLECTOR_H
#define REFLECTOR_H

class Reflector
{
  private:
    int config[26];
	public:
    //CONSTRUCTOR
    Reflector(int c[])
    {
    	for (int i = 0; i < 26; i++)
      	config[i] = c[i];
    }

    //FUNCTION WHICH ENCODES THE LETTER "number"
    //ACCORDING TO THE REFLECTOR CONFIGURATION
    int encode(int number);
};

#endif
	
