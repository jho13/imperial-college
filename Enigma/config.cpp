#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include "config.h"
#include "errors.h"
#include "Plugboard.h"
#include "Rotor.h"
#include "Reflector.h"
using namespace std;

//Internal helper function which returns true if there is a 
//non-numeric character (ignoring white spaces)in a file. 
//Returns false otherwise.
bool non_numeric_char(ifstream& in_stream)
{
	char ch;
	in_stream.get(ch);
	while (!in_stream.eof())
	{
		if (!isdigit(ch) && !isspace(ch))
			return true;
		in_stream.get(ch);
	}
	return false;
}

int process_plugboard_config(char* filename, int config[])
{
  ifstream in_stream;
  in_stream.open(filename);
  //check for ERROR_OPENING_CONFIGURATION_FILE
  if (in_stream.fail())
  {
    cerr << "The plugboard file " << filename
    		 << " could not be opened\n";
    return ERROR_OPENING_CONFIGURATION_FILE;
  }
			
  //check for NON_NUMERIC_CHARACTER	
	if (non_numeric_char(in_stream))
  {
    cerr << "Non-numeric character in plugboard file " << filename << endl;
    return NON_NUMERIC_CHARACTER;
  }
  in_stream.close();
	
  in_stream.open(filename);
  int next, index = 0;
  while (in_stream >> next)
  {
  	//check for INCORRECT_NUMBER_OF_PLUGBOARD_PARAMETERS
  	if (index == 26)
  	{
      cerr << "Incorrect (more than 26) number of parameters in plugboard file "
    			 << filename << endl;
    	return INCORRECT_NUMBER_OF_PLUGBOARD_PARAMETERS;
    }
    
    //check for INVALID_INDEX
    if (next < 0 || next > 25)
    {
      cerr << "Invalid index (" << next << ") in plugboard file "
      		 << filename << endl;
      return INVALID_INDEX;
    }
		
    config[index] = next;
			
    //check for IMPOSSIBLE_PLUGBOARD_CONFIGURATION
    for (int i = 0; i < index; i++)
    {
      if (config[i] == config[index])
      {
				cerr << "Impossible plugboard configuration (" 
						 << config[i] << ") appears multiple times in plugboard file " 
						 << filename << endl;
				return IMPOSSIBLE_PLUGBOARD_CONFIGURATION;
      }
    }
 
    index++;
  }

  //fill the rest of "config" with redundant entries eg.-1 
  for (int i = index; i < 26; i++)
    config[i] = -1;
		
  //check for INCORRECT_NUMBER_OF_PLUGBOARD_PARAMETERS
  if (index%2 != 0)
  {
    cerr << "Incorrect (odd) number of parameters in plugboard file "
    		 << filename << endl;
    return INCORRECT_NUMBER_OF_PLUGBOARD_PARAMETERS;
  }
			
  in_stream.close();

  //no error
  return NO_ERROR;
}

int process_rotor_config(char* filename, int config[], bool notches[])
{
  for (int i = 0; i < 26; i++)
    notches[i] = false; //reset "notches" to all 0's
    
  ifstream in_stream;
  in_stream.open(filename);
  if (in_stream.fail())
  {
    cerr << "The rotor file " << filename
    		 << " could not be opened\n";
    return ERROR_OPENING_CONFIGURATION_FILE;
  }
  
  //check for NON_NUMERIC_CHARACTER	
	if (non_numeric_char(in_stream))
  {
    cerr << "Non-numeric character for mapping in rotor file "
    		 << filename << endl;
    return NON_NUMERIC_CHARACTER;
  }
  in_stream.close();

  in_stream.open(filename);
  int next, index = 0;
  while (in_stream >> next && index < 52) 
  {
    //check for INVALID_INDEX
    if (next < 0 || next > 25)
    {
      cerr << "Invalid index (" << next << ") in rotor file "
      		 << filename << endl;
      return INVALID_INDEX;
    }

    //fill "config"
    if (index < 26)
    {
      config[index] = next;
      //check for INVALID_ROTOR_MAPPING
      for (int i = 0; i < index; i++)
      {
				if (config[i] == config[index])
        {
	  			cerr << "Invalid rotor mapping (non-injective mapping onto "
	  				   << config[i] << ") in rotor file " << filename << endl;
	  			return INVALID_ROTOR_MAPPING;
				}
      }
    }
    
    //fill "notches"
    else
      notches[next] = true;

    index++;
  }

  //check for INVALID_ROTOR_MAPPING
  if (index < 26)
  {
    cerr << "Not all inputs mapped in rotor file " << filename << endl;
    return INVALID_ROTOR_MAPPING;
  }
			
  in_stream.close();

  //no error
  return 0;
}

int process_rotor_startpos(char* filename, int startpos[], int number_of_rotors)
{
  ifstream in_stream;
  in_stream.open(filename);
  if (in_stream.fail())
  {
    cerr << "The rotor positions file " << filename
    		 << " could not be opened\n";
    return ERROR_OPENING_CONFIGURATION_FILE;
  }
  
  //check for NON_NUMERIC_CHARACTER	
	if (non_numeric_char(in_stream))
  {
    cerr << "Non-numeric character in rotor positions file "
    		 << filename << endl;
    return NON_NUMERIC_CHARACTER;
  }
  in_stream.close();
	
  in_stream.open(filename);
  int next, index = 0;
  while (in_stream >> next && index < number_of_rotors)
  {
    //check for INVALID_INDEX
    if (next < 0 || next > 25)
    {
      cerr << "Invalid index (" << next << ") in rotor positions file "
      		 << filename << endl;
      return INVALID_INDEX;
    }
    
    startpos[index] = next;
    index++;
  }
  
  //check for NO_ROTOR_STARTING_POSITION
  if (index < number_of_rotors)
  {
    cerr << "Not enough rotor starting positions in "
    	   << "rotor positions file " << filename << endl;
    return NO_ROTOR_STARTING_POSITION;
  }
			
  in_stream.close();

  //no error
  return NO_ERROR; 	
}
	
int process_reflector_config(char* filename, int config[])
{
  ifstream in_stream;
  in_stream.open(filename);
  if (in_stream.fail())
  {
    cerr << "The reflector file " << filename
    		 << " could not be opened\n";
    return ERROR_OPENING_CONFIGURATION_FILE;
  }
			
  //check for NON_NUMERIC_CHARACTER	
	if (non_numeric_char(in_stream))
  {
    cerr << "Non-numeric character in reflector file "
    		 << filename << endl;
    return NON_NUMERIC_CHARACTER;
  }
  in_stream.close();
	
  in_stream.open(filename);
  int next, index = 0;
  while (in_stream >> next)
  {
  	//check for INCORRECT_NUMBER_OF_REFLECTOR_PARAMETERS
  	if (index == 26)
  	{
      cerr << "Incorrect (more than 26) number of parameters in reflector file "
    			 << filename << endl;
    	return INCORRECT_NUMBER_OF_REFLECTOR_PARAMETERS;
    }
    	
    //check for INVALID_INDEX
    if (next < 0 || next > 25)
    {
      cerr << "Invalid index (" << next << ") in reflector file "
      		 << filename << endl;
      return INVALID_INDEX;
    }

 		config[index] = next;
 					
    //check for INVALID_REFLECTOR_MAPPING
    for (int i = 0; i < index; i++)
    {
      if (config[i] == config[index])
      {
				cerr << "Invalid reflector mapping (" << config[i] << ") appears "
						 << "multiple times in reflector file " << filename << endl;
				return INVALID_REFLECTOR_MAPPING;
      }
    }
 
    index++;
  }

  //check for INCORRECT_NUMBER_OF_REFLECTOR_PARAMETERS
  if (index != 26)
  {
    cerr << "Incorrect number of parameters in reflector file "
    		 << filename << " (file must contain exactly 26 numbers)" << endl;
    return INCORRECT_NUMBER_OF_REFLECTOR_PARAMETERS;
  }
			
  in_stream.close();

  //no error
  return NO_ERROR;
}
