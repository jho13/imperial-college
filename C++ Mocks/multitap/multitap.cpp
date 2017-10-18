#include <cctype>
#include <cstring>

#include "multitap.h"

int encode_character(const char ch, char* multitap)
{
  //space
  if (ch == ' ')
  {
    multitap[0] = '0';
    multitap[1] = '\0';
    return 1;
  }
  
  //alphabet
  if (isalpha(ch))
  {
    int length;
    if (tolower(ch) <= 'r')
    {
      char digit = '2' + (tolower(ch) - 'a')/3;
      length = 1 + ((tolower(ch) - 'a')%3);
      for (int i = 0; i < length; i++)
	multitap[i] = digit;

      multitap[length] = '\0';
      return length;
    }
    else
    {
      if (tolower(ch) == 's')
      {
	strcpy(multitap, "7777");
	return length;
      }
      if (tolower(ch) >= 't' && tolower(ch) <= 'v')
      {
	length = 1 + (tolower(ch) - 't');
	for (int i = 0; i < length; i++)
	  multitap[i] = '8';

	multitap[length] = '\0';
	return length;
      }
      else
      {
	length = 1 + (tolower(ch) - 'w');
	for (int i = 0; i < length; i++)
	  multitap[i] = '9';

	multitap[length] = '\0';
	return length;
      }
    }
  }

  //digit
  if (isdigit(ch))
  {
    multitap[0] = '*';
    multitap[1] = ch;
    multitap[2] = '\0';
    return 2;
  }

  //puctuations
  if (ch == '.')
  {
    strcpy(multitap, "1");
    return 1;
  }
  if (ch == ',')
  {
    strcpy(multitap, "11");
    return 2;
  }
  if (ch == '!')
  {
    strcpy(multitap, "111");
    return 3;
  }
  if (ch == '?')
  {
    strcpy(multitap, "1111");
    return 4;
  }
}

void encode(const char* plaintext, char* multitap)
{
  strcpy(multitap, "");

  //encode one character at a time
  char store[5];
  for (unsigned int i = 0; i < strlen(plaintext); i++)
  {
    encode_character(plaintext[i], store);

    //add pause
    if (store[0] == multitap[strlen(multitap) - 1])
      strcat(multitap, "|");
    
    //add '#' for uppercase
    if (isupper(plaintext[i]))
      strcat(multitap, "#");
    
    strcat(multitap, store);
  }
}
