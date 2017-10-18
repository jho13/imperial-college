#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include "sudoku.h"

using namespace std;

/* You are pre-supplied with the functions below. Add your own
   function definitions to the end of this file. */

/* pre-supplied function to load a Sudoku board from a file */
void load_board(const char* filename, char board[9][9]) {

  cout << "Loading Sudoku board from file '" << filename << "'... ";

  ifstream in(filename);
  if (!in)
    cout << "Failed!" << endl;
  assert(in);

  char buffer[512];

  int row = 0;
  in.getline(buffer,512);
  while (in && row < 9) {
    for (int n=0; n<9; n++) {
      assert(buffer[n] == '.' || isdigit(buffer[n]));
      board[row][n] = buffer[n];
    }
    row++;
    in.getline(buffer,512);
  }

  cout << ((row == 9) ? "Success!" : "Failed!") << endl;
  assert(row == 9);
}

/* internal helper function */
void print_frame(int row) {
  if (!(row % 3))
    cout << "  +===========+===========+===========+" << endl;
  else
    cout << "  +---+---+---+---+---+---+---+---+---+" << endl;
}

/* internal helper function */
void print_row(const char* data, int row) {
  cout << (char) ('A' + row) << " ";
  for (int i=0; i<9; i++) {
    cout << ( (i % 3) ? ':' : '|' ) << " ";
    cout << ( (data[i]=='.') ? ' ' : data[i]) << " ";
  }
  cout << "|" << endl;
}

/* pre-supplied function to display a Sudoku board */
void display_board(const char board[9][9]) {
  cout << "    ";
  for (int r=0; r<9; r++) 
    cout << (char) ('1'+r) << "   ";
  cout << endl;
  for (int r=0; r<9; r++) {
    print_frame(r);
    print_row(board[r],r);
  }
  print_frame(9);
}

/*own functions*/

//FUNCTION WHICH RETURNS 'true' IF ALL THE ENTRIES IN "board" ARE DIGITS.
//RETURNS 'false' OTHERWISE.
bool is_complete(const char board[9][9])
{
	for (int i = 0; i <= 8; i++)
	{
		for (int j = 0; j <= 8; j++)
		{
			if (!isdigit(board[i][j]))
				return false;
		}
	}
	return true;
}

//FUNCTION WHICH ATTEMPTS TO PLACE A DIGIT "digit" AT POSITION "position"
//(e.g. I8), OF THE SUDOKU BOARD "board".
//RETURNS 'false' IF:
// -"position" IS INVALID
// -PLACING "digit" AT "position" IS LOGICALLY INVALID
//OTHERWISE "board" IS UPDATED AND FUNCTION RETURNS 'true'
bool make_move(const char position[], char digit, char board[9][9])
{
	//check "position" is valid
	if (position[0] < 'A' || position[0] > 'I' || position[1] < '1' || position[1] > '9')
		return false;

	int i,j;
	i = (position[0] - 'A');
	j = (position[1] - '1');

	//check it is logically valid to place "digit" at "position"
	//check row i;
	for (int colnum = 0; colnum <= 8; colnum++)
	{
		if (board[i][colnum] == digit)
			return false;
	}
	//check column j;
	for (int rownum = 0; rownum <= 8; rownum++)
	{
		if (board[rownum][j] == digit)
			return false;
	}
	//check 3x3 sub-baord
	for (int k = 3*(i/3); k <= 3*(i/3) + 2; k++)
	{
		for (int l = 3*(j/3); l <= 3*(j/3) + 2; l++)
		{
			if (board[k][l] == digit)
				return false;
		}
	}

	board[i][j] = digit;
	return true;
}

//FUNCTION WHICH OUTPUTS THE SUDOKU BOARD "board" TO A FILE WITH NAME "filename"
//FUNCTION RETURNS 'true' IF THE FILE WAS SUCCESSFULLY WRITTEN,
//'false' OTHERWISE.
bool save_board(const char* filename, const char board[9][9])
{
	ofstream out_stream;
	out_stream.open(filename);
	if (out_stream.fail())
		return false;
	for (int i = 0; i <= 8; i++)
	{
		for (int j = 0; j <=8; j++)
		{
			if (!(board[i][j] == '.' || isdigit(board[i][j])))
				return false;
			out_stream << board[i][j];
		}
		out_stream << endl;
	}
	out_stream.close();
	return true;
}

//FUNCTION WHICH ATTEMPTS TO SOLVE THE SUDOKU PUZZLE IN "board"
//FUNCTION RETURNS 'true' IF A SOLUTION IS FOUND, AND "board" CONTAINS THE SOLUTION
//OHTERWISE RETURNS 'false' (i.e. SOLUTION DOESN'T EXIST) AND "board" CONATAINS
//THE ORIGINAL BOARD
bool solve_board(char** board)
{
	if (is_complete(board))
		return true;
	else
	{
		//identify empty position on "board"
		char empty_position[2];
		int i = 0, j = 0;
		while (!(board[i][j] == '.'))
		{
			if (i == 8)
			{
				i = 0;
				j++;
			}
			else
				i++;
		}
		empty_position[0] = 'A' + i;
		empty_position[1] = '1' + j;

		//fill "empty_position" with logically valid number then call 'solve_board'
		char input = '1' - 1;
		do
		{
			//use 'make_move' to input a valid number
			do
			{
				//if "input" reaches 9, end function call 'solve_board';
				//go back to previous board and keep increment previous "empty_position".
				if (input == '9')
				{
					board[i][j] = '.';
					return false;
				}
				input = input + 1;
			}while (!make_move(empty_position, input, board));
			
		} while (!solve_board(board));

		return true;
	}
}










	

