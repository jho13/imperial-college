#include "braille.h"
#include <cctype>
#include <cstring>

/*********************helper functions***********************/

//special encodings

void encode_capchar(char* braille)
{
  for (int i = 0; i < 5; i++)
    braille[i] = '.';
  braille[5] = '0';
}

void encode_numchar(char* braille)
{
  braille[0] = '.';
  braille[1] = '.';
  for (int i = 2; i < 6; i++)
    braille[i] = '0';
}

void encode_blank(char* braille)
{
  for (int i = 0; i < 6; i++)
    braille[i] = '.';
  braille[6] = '\0';
}

//encodes "ch" using Braille in Braille cell number "cellnum"
//within "braille"

//assumes "ch" is a lower case alphabet 
void encode_alpha(const char ch, char* braille, const int cellnum)
{
  int index = cellnum * 6;
  for (int i = 0; i < 6; i++)
    braille[index + i] = '.';

  if (ch != 'i' && ch != 'j' && ch != 's' && ch != 't' && ch != 'w')
    braille[index] = '0';

  if (ch == 'b' || ch == 'f' || ch == 'g' || ch == 'h' || ch == 'i'
      || ch == 'j' || ch == 'l' || ch == 'p' || ch == 'q' || ch == 'r'
      || ch == 's' || ch == 't' || ch == 'v' || ch == 'w')
    braille[index + 1] = '0';

  if (ch >= 'k' && ch != 'w')
    braille[index + 2] = '0';

  if (ch != 'a' && ch != 'b' && ch != 'e' && ch != 'h' && ch != 'k'
      && ch != 'l' && ch != 'o' && ch != 'r' && ch != 'u' && ch != 'v'
      && ch != 'z')
    braille[index + 3] = '0';
  
  if (ch == 'd' || ch == 'e' || ch == 'g' || ch == 'h' || ch == 'j'
      || ch == 'n' || ch == 'o' || ch == 'q' || ch == 'r' || ch == 't'
      || ch == 'w' || ch == 'y' || ch == 'z')
    braille[index + 4] = '0';
  
  if (ch >= 'u')
    braille[index + 5] = '0';

  braille[(cellnum+1) * 6] = '\0';
}

//assumes "ch" is a punctuation character
void encode_punct(const char ch, char* braille)
{
  for (int i = 0; i < 6; i++)
    braille[i] = '.';

  if (ch != '-')
    braille[1] = '0';

  if (ch != '.' && ch != ',')
    braille[2] = '0';

  if (ch == '.' || ch == '!' || ch == '(' || ch == ')')
    braille[4] = '0';

  if (ch == '.' || ch == '-' || ch == '?' || ch == '(' || ch == ')')
    braille[5] = '0';

  braille[6] = '\0';
}

/************************************************************/

int encode_character(const char ch, char* braille)
{
  if (isupper(ch))
  {
    encode_capchar(braille);
    encode_alpha(tolower(ch), braille, 1);
    return 12;
  }

  if (islower(ch))
  {
    encode_alpha(ch, braille, 0);
    return 6;
  }

  if (isdigit(ch))
  {
    encode_numchar(braille);
    if (ch == '0')
      encode_alpha('j', braille, 1);
    else
      encode_alpha('a' + (ch - '1'), braille, 1);
    return 12;
  }

  if (ispunct(ch))
  {
    encode_punct(ch, braille);
    return 6;
  }
  
  encode_blank(braille);
  return 6;
}

void encode(const char* plaintext, char* braille)
{
  if (plaintext[0] == '\0')
  {
    braille[0] = '\0';
    return;
  }

  encode_character(plaintext[0], braille);

  char _plaintext[strlen(plaintext)];
  for (unsigned int i = 0; i <= strlen(plaintext); i++)
    _plaintext[i] = plaintext[i+1];
  
  char buffer[512];
  encode(_plaintext, buffer);
  strcat(braille, buffer);
}

void encode(const char* plaintext, char* braille, bool* is_char)
{
  static int index = 0;
  if (plaintext[0] == '\0')
  {
    braille[0] = '\0';
    index = 0;
    return;
  }

  if (encode_character(plaintext[0], braille) == 6)
  {
    is_char[index] = true;
    index++;
  }
  else
  {
    is_char[index] = false;
    is_char[index+1] = true;
    index += 2;
  }
  
  char _plaintext[strlen(plaintext)];
  for (unsigned int i = 0; i <= strlen(plaintext); i++)
    _plaintext[i] = plaintext[i+1];
  
  char buffer[512];
  encode(_plaintext, buffer, is_char);
  strcat(braille, buffer);
}

void print_braille(const char* plaintext, ostream& o)
{
  char braille[512];
  bool is_char[60]; //is_char[i] = true if ith Braille cell represents a character
  encode(plaintext, braille, is_char);
  for (unsigned int i = 0; i < strlen(braille); i+= 3)
  {
    o << braille[i];
    if (i%6 == 3)
      o << " ";
  }
  o << endl;
  for (unsigned int i = 1; i < strlen(braille); i+= 3)
  {
    o << braille[i];
    if (i%6 == 4)
      o << " ";
  }
  o << endl;
  for (unsigned int i = 2; i < strlen(braille); i+= 3)
  {
    o << braille[i];
    if (i%6 == 5)
      o << " ";
  }
  o << endl;

  int j = 0;
  for (unsigned int i = 0; i < strlen(braille)/6; i++)
  {
    if (is_char[i])
    {
      o << plaintext[j] << "  ";
      j++;
    }
    else
      o << "   ";
  }
  o << endl;
}

