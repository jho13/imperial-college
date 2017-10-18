#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <vector>
#include <algorithm>
#include "errors.h"
#include "config.h"
#include "Plugboard.h"
#include "Rotor.h"
#include "Reflector.h"
using namespace std;

int main(int argc, char** argv)
{
	//check for INSUFFICIENT_NUMBER_OF_PARAMETERS
	if (argc <= 2)
	{
		cerr << "usage: enigma plugboard-file reflector-file " 
				 << "(<rotor-file>* rotor-positions)?\n";
		return INSUFFICIENT_NUMBER_OF_PARAMETERS;
	}
		
  /*configure plugboard*/
  //process the plugboard configuration file and check for any errors
  int plugboard_config[26];//file should contain at most 26 numbers
  int error = process_plugboard_config(*(argv+1), plugboard_config);
  if (error != 0)
    return error;
  Plugboard plugboard(plugboard_config);
  /*end of plugboard configuration*/
  
  /*configure rotors*/
  const int number_of_rotors = max(argc-4, 0);
  Rotor* rotor_group = NULL; 
  if (number_of_rotors >= 1) //there is at least one rotor
  {
  	rotor_group = new Rotor[number_of_rotors];
    //process the rotor configurations file and check for any errors
    int rotor_config[26];
    bool rotor_notches[26]; //notches[i] = true if there is a notch at i
    for (int i = 0; i <= number_of_rotors - 1; i++)
    { 
      error = process_rotor_config(*(argv + 3 + i), rotor_config, rotor_notches);
      if (error != 0)
				return error;
      rotor_group[i].set(rotor_config, rotor_notches);    
    }
    
    //process the rotor starting positions file and check for any errors
    int rotor_startpos[number_of_rotors];
    error = process_rotor_startpos(*(argv+(argc-1)), rotor_startpos, number_of_rotors);
    if (error != 0)
      return error;

    //set up rotors according to starting positions
    for (int i = 0; i <= number_of_rotors - 1; i++)
    {
    	for (int j = 1; j <= rotor_startpos[i]; j++)
				rotor_group[i].rotate();
		}
  }
  /*end of rotors configuration*/
  
  /*configure reflector*/
  //process the reflector configuration and check for any errors
  int reflector_config[26];
  error = process_reflector_config(*(argv+2), reflector_config);
  if (error != 0)
    return error;
  Reflector reflector(reflector_config);
  /*end of reflector configuration*/
 
  //input message
  char letter; int number;
  while (cin >> letter)
  {
    //check for INVALID_INPUT_CHARACTER
    if (!isspace(letter) && (letter < 'A' || letter > 'Z'))
    {
      cerr << letter << " is not a valid input character "
      		 << "(input characters must be upper case letters A-Z)!\n";
      return INVALID_INPUT_CHARACTER;
    }

    //convert to 'int' where 0 <= number <= 26
    //to pass through encoding components
    number = letter - 'A'; 
    
    //rotate rotors (if there are non zero rotors)
    if (number_of_rotors >= 1)
		{
			int k = number_of_rotors - 1;
  		rotor_group[k].rotate();
  		while (rotor_group[k].is_notch() && k >= 1)
  		{
				k--;
				rotor_group[k].rotate();
  		}
		}
    //encode
    number = plugboard.encode(number);
    for (int i = number_of_rotors - 1; i>= 0; i--)
      number = rotor_group[i].encode_in(number);
    number = reflector.encode(number);
    for (int i = 0; i <= number_of_rotors - 1; i++)
      number = rotor_group[i].encode_out(number);
    number = plugboard.encode(number);
    
    //convert back to 'char'
    letter = 'A' + number;
    cout << letter;
  }
  
  delete [] rotor_group;
  return NO_ERROR;
}
