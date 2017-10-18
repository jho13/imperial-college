#ifndef CONFIG_H
#define CONFIG_H

#include "Rotor.h"

//FUNCTION TO CHECK FOR ERRORS AND COVERT THE PLUGBOARD CONFIGUARTION
//FILE "filename" INTO AN ARRAY OF INTEGERS "config".
int process_plugboard_config(char* filename, int config[]);

//FUNCTION TO CHECK FOR ERRORS AND COVERT THE ROTOR CONFIGUARTION
//FILE "filename" INTO TWO ARRAYS "config" (FOR THE ROTOR MAPPINGS)
//AND "notches" (FOR THE ROTOR NOTCHES). HERE notches[i] = true IFF
//THERE IS A NOTCH AT POSITION i.
int process_rotor_config(char* filename, int config[], bool notches[]);

//FUNCTION TO CHECK FOR ERRORS AND COVERT THE ROTOR STARTING POSITIONS
//FILE "filename" INTO AN ARRAY OF INTEGERS "startpos".  
int process_rotor_startpos(char* filename, int startpos[], int number_of_rotors);

//FUNCTION TO CHECK FOR ERRORS AND COVERT THE REFLECTOR CONFIGUARTION
//FILE "filename" INTO AN ARRAY OF INTEGERS "config".
int process_reflector_config(char* filename, int config[]);

#endif
