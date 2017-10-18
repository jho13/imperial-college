#include <iostream>
#include <cstring>
#include <cctype>
#include <cassert>
#include <map>
#include <string>
#include <fstream>

using namespace std;

#include "sonnet.h"

/* PRE-SUPPLIED HELPER FUNCTIONS START HERE */

/* NOTE: It is much more important to understand the interface to and
   the "black-box" operation of these functions (in terms of inputs and
   outputs) than it is to understand the details of their inner working. */

/* get_word(...) retrieves a word from the input string input_line
   based on its word number. If the word number is valid, the function
   places an uppercase version of the word in the output parameter
   output_word, and the function returns true. Otherwise the function
   returns false. */

bool get_word(const char *input_line, int word_number, char *output_word) {
  char *output_start = output_word;
  int words = 0;

  if (word_number < 1) {
    *output_word = '\0';
    return false;
  }
  
  do {
    while (*input_line && !isalnum(*input_line))
      input_line++;

    if (*input_line == '\0')
      break;

    output_word = output_start;
    while (*input_line && (isalnum(*input_line) || *input_line=='\'')) {
      *output_word = toupper(*input_line);
      output_word++;
      input_line++;
    }
    *output_word = '\0';

    if (++words == word_number)
      return true;

  } while (*input_line);

  *output_start = '\0';
  return false;
}

/* char rhyming_letter(const char *ending) generates the rhyme scheme
   letter (starting with 'a') that corresponds to a given line ending
   (specified as the parameter). The function remembers its state
   between calls using an internal lookup table, such that subsequents
   calls with different endings will generate new letters.  The state
   can be reset (e.g. to start issuing rhyme scheme letters for a new
   poem) by calling rhyming_letter(RESET). */

char rhyming_letter(const char *ending) {

  // the next rhyming letter to be issued (persists between calls)
  static char next = 'a';
  // the table which maps endings to letters (persists between calls)
  static map<string, char> lookup;

  // providing a way to reset the table between poems
  if (ending == RESET) {
    lookup.clear();
    next = 'a';
    return '\0';
  }

  string end(ending);

  // if the ending doesn't exist, add it, and issue a new letter
  if (lookup.count(end) == 0) {
    lookup[end]=next;
    assert(next <= 'z');
    return next++;
  }

  // otherwise return the letter corresponding to the existing ending
  return lookup[end];
}

/* START WRITING YOUR FUNCTION BODIES HERE */

int count_words(const char* line)
{
  char word[512];
  //there are no words
  if (!get_word(line, 1, word))
    return 0;

  //look for word number "count" in "line"
  int count = 1;
  while (get_word(line, count, word))
    count++;
  return (count - 1);
}

//helper function
bool contains_vowel(const char* word)
{
  int length = strlen(word);
  for (int i = 0; i < length; i++)
  {
    if (toupper(word[i]) == 'A' || toupper(word[i]) == 'E' || toupper(word[i]) == 'I'
	|| toupper(word[i]) == 'O' || toupper(word[i]) == 'U')
      return true;
  }
  return false;
}

bool find_phonetic_ending(const char* word, char* phonetic_ending)
{
  //open file "dictionary.txt"
  ifstream dictionary;
  dictionary.open("dictionary.txt");

  //get one word at a time from dictionary and compare with "word"
  char line[512], buffer[512];
  do {
    dictionary.getline(line, 512);
    get_word(line, 1, buffer);
  } while (strcmp(word, buffer));

  //"word" not found
  if (dictionary.eof())
  {
    dictionary.close();
    return false;
  }

  //"word" found
  //locate phonemes with vowel
  int num = count_words(line) + 1;
  do {
    num--;
    get_word(line, num, buffer);
  } while (!contains_vowel(buffer));
  //form phonetic ending
  strcpy(phonetic_ending, "");
  for (int i = num; i <= count_words(line); i++)
  {
    get_word(line, i, buffer);
    strcat(phonetic_ending, buffer);
  }
  
  dictionary.close();
  return true;
}

bool find_rhyme_scheme(const char* filename, char* scheme)
{
  //open file "filename"
  ifstream sonnet;
  sonnet.open(filename);
  if (sonnet.fail())
    return false;

  rhyming_letter(RESET);

  //
  char line[512], word[512], line_ending[16];
  int index = 0; //index of "scheme"
  int num; //number of words in "line"
  while (sonnet.getline(line, 512))
  {
    num = count_words(line);
    get_word(line, num, word);
    find_phonetic_ending(word, line_ending);
    scheme[index] = rhyming_letter(line_ending);
    index++;
  }
  scheme[index] = '\0';
  
  return true;
}

string identify_sonnet(const char* filename)
{
  //find rhyme scheme
  char scheme[50];
  find_rhyme_scheme(filename, scheme);

  //determine type
  if (!strcmp(scheme, "ababcdcdefefgg"))
    return "Shakespearean";

  if (!strcmp(scheme, "abbaabbacdcdcd"))
    return "Petrarchan";

  if (!strcmp(scheme, "ababbcbccdcdee"))
    return "Spenserian";

  //matches none of the above
  return "Unknown";
}
