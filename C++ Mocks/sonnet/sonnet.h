// RESET is a constant used by function rhyming_letter(...)
#define RESET NULL

/* get_word(...) retrieves a word from the input string input_line
   based on its word number. If the word number is valid, the function
   places an uppercase version of the word in the output parameter
   output_word, and the function returns true. Otherwise the function
   returns false. */

bool get_word(const char *input_line, int number, char *output_word);

/* char rhyming_letter(const char *ending) generates the rhyme scheme
   letter (starting with 'a') that corresponds to a given line ending
   (specified as the parameter). The function remembers its state
   between calls using an internal lookup table, such that subsequents
   calls with different endings will generate new letters.  The state
   can be reset (e.g. to start issuing rhyme scheme letters for a new
   poem) by calling rhyming_letter(RESET). */

char rhyming_letter(const char *ending);

//FUNCTION WHICH RETURNS THE NUMBER OF WORDS IN A GIVEN INPUT STRING
//"line"
int count_words(const char* line);

//FUNCTION WHICH USES THE PHONETIC DICTIONARY "dictionary.txt" TO
//CONSTRUCT THE PHONETIC ENDING FOR THE "word". IF THE WORD IS IN
//THE DICTIONARY THE PHONETIC ENDING IS STORED IN "phonetic_ending"
//AND FUNCTION RETURNS TRUE. FUNCTION RETURS FALSE OTHERWISE.
bool find_phonetic_ending(const char* word, char* phonetic_ending);

//FUCNTION WHICH PRODUCES THE RHYME SCHEME IN "scheme" FOR THE SONNET
//CONTAINED IN THE FILE "filename". IF THE FILE DOES NOT EXIST, FUNCTION
//RETURNS FALSE, OTHERWISE FUCNTION RETURNS TRUE.
bool find_rhyme_scheme(const char* filename, char* scheme);

//FUNCTION WHICH RETURNS ONE OF THE STRINGS:
/* "Shakespearean"
   "Petrarchan"
   "Spenserian"
   "Unknown" */
//ACCORDING TO WHETHER THE RHYME SCHEME OF SONNET IN FILE "filename"
//MATCHES ONE OF THE ABOVE. (NO MATCH FOUND RETURNS "Unknown".
string identify_sonnet(const char* filename);
