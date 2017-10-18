//FUCNTION WHICH PRODUCES THE SOUNDEX ENCODING CORRESPONDING
//TO A GIVEN SURNAME "surname". THE ENCODING IS STORED IN "soundex"
void encode(const char* surname, char* soundex);

//FUNCTION WHICH RETURNS 1 IF TWO SOUNDEX CODES
//"one" AND "two" ARE EQUAL, 0 OTHERWISE.
int compare(const char* one, const char* two);

//FUNCTION WHICH RETURNS THE NUMBER OF WORDS IN "sentence"
//WHICH HAVE THE SAME SOUNDEX ENCODING AS "surname"
int count(const char* surname, const char* sentence);
