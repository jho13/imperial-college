#include <iostream>

using namespace std;

//FUNCTION WHICH RETURNS THE POSITION OF THE FIRST "VOWEL"
//RETURNS -1 IF NO VOWEL IS FOUND.
int findFirstVowel(const char* word);

//FUNCTION WHICH STORES THE PIGLATIN TRANSLATION FOR A GIVEN
//WORD "english" IN THE CHARACTER ARRAY "piglatin".
void translateWord(const char* english, char* piglatin);

//FUNCTION WHICH TAKES WORDS FROM AN INPUT STREAM "in" AND WRITES
//A CORRESPONDING PIG LATIN TRANSLATION TO AN OUTPUT STREAM "out"
void translateStream(istream& in, ostream& out);
