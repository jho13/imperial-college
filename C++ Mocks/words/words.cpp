#include "words.h"
#include <cstring>
#include <cctype>

#include <iostream>
using namespace std;

void reverse(const char* str1, char* str2)
{
  int len = strlen(str1);
  for (int i = 0; i < len; i++)
    str2[i] = str1[len-1-i];
  str2[len] = str1[len];
}

/***********************helper functions************************/

//copies "str" into "lower" with all characters lowered
void lower(const char* str, char* lower)
{
  for (unsigned int i = 0; i <= strlen(str); i++)
    lower[i] = tolower(str[i]);
}

//copies "str" into "no_punct" ignoring all non-alphabets
void no_punct(const char* str, char* no_punct)
{
  int j = 0;
  for (unsigned int i = 0; i <= strlen(str); i++)
  {
    if (isalpha(str[i]))
    {
      no_punct[j] = str[i];
      ++j;
    }
  }
  no_punct[j] = '\0';
}

void swap(char& c1, char& c2)
{
  char temp = c1;
  c1 = c2;
  c2 = temp;
}

//sorts "str" in alphabetical order
void sort(char* str)
{
  unsigned int index = 0;
  while (index < strlen(str))
  {
    int index_of_least = index;
    unsigned int comp_index = index + 1;
    while (comp_index < strlen(str))
    {
      if (str[index_of_least] > str[comp_index])
	index_of_least = comp_index;
      comp_index++;
    }
    swap(str[index], str[index_of_least]);
    index++;
  }
}

/*************************************************************/

int compare(const char* one, const char* two)
{
  char first[strlen(one) + 1], second[strlen(two) + 1];
  strcpy(first, one);
  strcpy(second, two);
  
  static bool first_time = true;
  if (first_time)
  {
    char temp1[strlen(one) + 1];
    no_punct(first, temp1);
    lower(temp1, first);
    
    char temp2[strlen(two) + 1];
    no_punct(second, temp2);
    lower(temp2, second);

    first_time = false;
  }

  if (second[0] == '\0')
  {
    if (second[0] == '\0')
    {
      first_time = true;
      return 1;
    }
    else
      return 0;
  }
  
  char _one[strlen(first)], _two[strlen(second)];
  if (first[0] == second[0])
  {
    for (unsigned int i = 0; i < strlen(first); i++)
      _one[i] = first[i+1];
    for (unsigned int i = 0; i < strlen(second); i++)
      _two[i] = second[i+1];

    return compare(_one, _two);
  }

  return 0;
}

int palindrome(const char* sentence)
{
  char rev[strlen(sentence) + 1];
  reverse(sentence, rev);
  return compare(sentence, rev);
}


int anagram(const char* str1, const char* str2)
{
  char one[strlen(str1) + 1], two[strlen(str2) + 1];
  no_punct(str1, one);
  no_punct(str2, two);

  char _one[strlen(one) + 1], _two[strlen(two) + 1];
  lower(one, _one);
  lower(two, _two);

  sort(_one);
  sort(_two);

  return compare(_one, _two);
}
