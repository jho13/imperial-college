#include "soundex.h"
#include <iostream>
#include <cctype>
#include <cstring>

using namespace std;

//internal helper function
bool valid_char(const char letter)
{
  return (isalpha(letter) || letter == '\'');
}

//internal helper function
int encode(char letter)
{
  letter = tolower(letter);
  if (letter == 'b' || letter == 'f' || letter == 'p' || letter == 'v')
    return 1;
  else if (letter == 'c' || letter == 'g' || letter == 'j' || letter == 'k'
	   || letter == 'q' || letter == 's' || letter == 'x' || letter == 'z')
    return 2;
  else if (letter == 'd' || letter == 't')
    return 3;
  else if (letter == 'l')
    return 4;
  else if (letter == 'm' || letter == 'n')
    return 5;
  else if (letter == 'r')
    return 6;
  else
    return 0;
}

void encode(const char* surname, char* soundex)
{
  //default characters
  soundex[0] = toupper(surname[0]);
  soundex[4] = '\0';

  int surname_index = 1, soundex_index = 1;
  char prev_char = '\0', new_char;
  while (soundex_index <= 3 && surname[surname_index] != '\0')
  { 
    new_char = '0' + encode(surname[surname_index]);
    //conditions 2) and 3)
    if (new_char != '0' && new_char != prev_char)
    {
      soundex[soundex_index] = new_char;
      ++soundex_index;
    }
    prev_char = new_char;
    ++surname_index;
  }

  //soundex encoding is underfilled
  if (soundex_index <= 3)
  {
    for (int i = soundex_index; i <= 3; i++)
      soundex[i] = '0';
  }
}

//assumes "one" and "two" are correct soundex codes
int compare(const char* one, const char* two)
{
  if (one[0] == two[0])
  {
    if (one[0] == '\0')
      return 1;

    char new_one[5], new_two[5];
    for (int i = 0; one[i] != '\0'; i++)
    {
      new_one[i] = one[i+1];
      new_two[i] = two[i+1];
    }

    return compare(new_one, new_two);
  }

  return 0;
}

int count(const char* surname, const char* sentence)
{
  int count = 0;
  char word[strlen(sentence)+1];
  int sent_index = 0; int word_index = 0;
  char surname_code[5], word_code[5];
  encode(surname, surname_code);
  while (sentence[sent_index] != '\0')
  {
    if (valid_char(sentence[sent_index])) 
    {
      word[word_index] = sentence[sent_index];
      ++word_index;
    }
    else
    {
      word[word_index] = '\0';
      encode(word, word_code);
      if (compare(surname_code, word_code))
	++count;
      word_index = 0;
    }
    ++sent_index;
  }
  return count;
}
