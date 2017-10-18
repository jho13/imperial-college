#include <iostream>
using namespace std;

//FUNCTION WHICH PRODUCES A STRING "braille" THAT REPRESENTS THE
//BRAILLE ENCODING OF A SINGLE INPUT CHARACTER "ch". RETURNS THE
//LENGTH OF THE BRAILE-ENCDOED STRING.
int encode_character(const char ch, char* braille);

//FUNCTION WHICH PRODUCES THE BRAILLE ENCODING OF AN INPUT STRING
//"plaintext". "braille" IS THE PARAMETER THAT CONTAINS THE
//BRAILLE-ENCODED STRING.
void encode(const char* plaintext, char* braille);

//FUNCTION WHICH TAKEKS AN INPUT STRING "plaintext" AND WRITES THE
//CORRESPONDING SEQUENCE OF 3 X 2 BRAILLE CELLS TO AN OUTPUT STREAM "o".
void print_braille(const char* plaintext, ostream& o);
