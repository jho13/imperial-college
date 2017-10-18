#include "piglatin.h"
#include <cctype>
#include <cstring>

//helper function
bool isVowel(const char letter)
{
  return (letter == 'a' || letter == 'e' || letter == 'i'
	 || letter == 'o' || letter == 'u');
}

int findFirstVowel(const char* word)
{
  for (int i = 0; word[i] != '\0'; i++)
  {
    if (isVowel(word[i]))
      return i;
    if (word[i] == 'y' && i != 0 && word[i+1] != '\0')
      return i;
  }
  return -1;
}

void translateWord(const char* english, char* piglatin)
{
  //word begins with character
  if (!isalpha(english[0]))
  {
    strcpy(piglatin, english);
    return;
  }
  
  int vowelpos = findFirstVowel(english);
  //word begins with vowel
  if (vowelpos == 0)
  {
    strcpy(piglatin, english);
    strcat(piglatin, "way");
    return;
  }

  //word begins with consonant and contains a vowel
  if (vowelpos > 0)
  {
    char temp[100];
    //temp is the string up to the first vowel
    strcpy(temp, english);
    temp[vowelpos] = '\0';
    
    //piglatin is the string after (including) the first vowel
    strcpy(piglatin, english + vowelpos);

    //word begins with capital
    if (isupper(english[0]))
    {
      temp[0] = tolower(temp[0]);
      piglatin[0] = toupper(piglatin[0]);
    }
    
    strcat(piglatin, temp);
    strcat(piglatin, "ay");
    return;
  }

  //word contains no vowel
  if (vowelpos < 0)
  {
    strcpy(piglatin, english);
    strcat(piglatin, "ay");
    return;
  }
}

void translateStream(istream& in, ostream& out)
{
  char word[65], translation[65];
  char ch;
  int i = 0;
  while (in.get(ch))
  {
    if (isalnum(ch))
    {
      word[i] = ch;
      i++;
    }
    else
    {
      word[i] = '\0';
      i = 0;
      translateWord(word, translation);
      out << translation << ch;
    }
  }
}

/*
void translateStream(istream& in, ostream& out)
{
  char word[65], translation[65];
  in >> word;
  translateWord(word, translation);
  out << translation;
  translateStream(in, out);
}
*/
