#ifndef CORRECT_H
#define CORRECT_H

/* converts a character into a binary string representation */
void ascii_to_binary(const char letter, char* output);

/* converts a binary string representation into a character */
char binary_to_ascii(const char* binary);

//FUNCTION WHICH CONVERTS A STRING OF CHARACTERS "str" INTO A
//CORRESPONDING STREAM OF BITS "binary".
void text_to_binary(const char* str, char* binary);

//FUNCTION WHICH CONVERTS A STREAM OF BITS "binary" INTO A
//CORRESPONDING STRING OF CHARACTERS "str".
void binary_to_text(const char* binary, char* str);

//FUNCTION WHICH OUTPUTS (INTO THE STRING PARAMETER "corrected")
//AN ERROR-CORRECTED DATA BIT STREAM "data".
void add_error_correction(const char* data, char* corrected);

//FUNCTION WHICH OUTPUTS (INTO THE STRING PARAMETER "decoded")
//AN ERROR-CORRECTED VERSION OF A RECEIVED BIT STREAM "received".
//RETURNS THE NUMBER OF ERRORS CORRECTED.
int decode(const char* received, char* decoded);

#endif
