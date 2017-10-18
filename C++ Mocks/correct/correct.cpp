#include "correct.h"
#include <iostream>
#include <cstring>
#include <cmath>

using namespace std;

/* You are supplied with two helper functions */

void ascii_to_binary(const char ch, char *binary) {
  for (int n = 128; n; n >>= 1) 
    *binary++ = (ch & n) ? '1' : '0';
  *binary = '\0';
}

char binary_to_ascii(const char *binary) {
  int ch = 0;
  for (int n=0, slide=128; n<8; n++, slide >>= 1) {
    if (binary[n] == '1')
      ch = ch | slide;
  }
  return ch;
}

/* now add your own functions here */

int binary_to_int(const char* binary)
{
  int sum = 0;
  int length = strlen(binary);
  int num[length];
  for (int i = 0; i < length; i++)
  {
    num[i] = binary[i] - '0';
    sum += num[i] * (pow(2,length-i-1));
  }
  return sum;
}

void text_to_binary(const char* str, char* binary)
{
  strcpy(binary, "");
  char byte[8];
  for (int i = 0; str[i] != '\0'; i++)
  {
    ascii_to_binary(str[i], byte);
    strcat(binary, byte);
  }
}

void binary_to_text(const char* binary, char* str)
{
  if (binary[0] == '\0')
  {
    strcpy(str, "");
    return;
  }
  
  char byte[9];
  for (int i = 0; i < 8; i++)
    byte[i] = binary[i];
  byte[8] = '\0';
  str[0] = binary_to_ascii(byte);
  str[1] = '\0';

  char _str[32];
  const char* _binary = binary + 8;
  binary_to_text(_binary, _str);
  strcat(str, _str);
}     

//computes the parity of three numbers
char parity(char ch1, char ch2, char ch3)
{
  int n1 = ch1 - '0', n2 = ch2 - '0', n3 = ch3 - '0';
  return ('0' + ((n1 + n2 + n3) % 2));
}

//computes the parity of four numbers
char parity(char ch1, char ch2, char ch3, char ch4)
{
  int n1 = ch1 - '0', n2 = ch2 - '0', n3 = ch3 - '0', n4 = ch4 - '0';
  return ('0' + ((n1 + n2 + n3 + n4) % 2));
}

//processes one "unit" which is four data bits
void correct_unit(const char* unit, char* corrected)
{
  char c1, c2, c3;
  c1 = parity(unit[0], unit[1], unit[3]);
  c2 = parity(unit[0], unit[2], unit[3]);
  c3 = parity(unit[1], unit[2], unit[3]);

  corrected[0] = c1;
  corrected[1] = c2;
  corrected[2] = unit[0];
  corrected[3] = c3;
  corrected[4] = unit[1];
  corrected[5] = unit[2];
  corrected[6] = unit[3];
  corrected[7] = '\0';
}

void add_error_correction(const char* data, char* corrected)
{
  strcpy(corrected, "");
  char unit[4], corrected_unit[8];
  for (int i = 0; data[i] != '\0'; i += 4)
  {
    for (int j = 0; j < 4; j++)
      unit[j] = data[i+j];
    correct_unit(unit, corrected_unit);
    strcat(corrected, corrected_unit);
  }
}

//processes one "unit" which is seven data bits
int decode_unit(const char* unit, char* decoded)
{
  char p1, p2, p3;
  p1 = parity(unit[3], unit[4], unit[5], unit[6]);
  p2 = parity(unit[1], unit[2], unit[5], unit[6]);
  p3 = parity(unit[0], unit[2], unit[4], unit[6]);

  char error[4];
  error[0] = p1;
  error[1] = p2;
  error[2] = p3;
  error[3] = '\0';

  int num =  binary_to_int(error);
  char corrected_unit[7];
  for (int i = 0; i < 7; i++)
    corrected_unit[i] = unit[i];
  if (num != 0)
    corrected_unit[num-1] = (corrected_unit[num-1] == '1' ? '0' : '1');

  decoded[0] = corrected_unit[2];
  decoded[1] = corrected_unit[4];
  decoded[2] = corrected_unit[5];
  decoded[3] = corrected_unit[6];
  decoded[4] = '\0';

  if (num != 0)
    return 1;
  else
    return 0;
}

int decode(const char* received, char* decoded)
{
  int num_errors = 0;
  
  strcpy(decoded, "");
  char unit[7], decoded_unit[5];
  for (int i = 0; received[i] != '\0'; i += 7)
  {
    for (int j = 0; j < 7; j++)
      unit[j] = received[i+j];
    num_errors += decode_unit(unit, decoded_unit);
    strcat(decoded, decoded_unit);
  }
  
  return num_errors;
}
