#include <iostream>
#include <cstdio>
#include "sudoku.h"
#include <ctime>

using namespace std;

int main() {

  char board[9][9];

  // This section illustrates the use of the pre-supplied helper functions.
  cout << "============== Pre-supplied functions ==================" << endl << endl;

  cout << "Calling load_board():" << endl;
  load_board("easy.dat", board);

  cout << endl << "Displaying Sudoku board with display_board():" << endl;
  display_board(board);
  cout << "Done!" << endl << endl;

  cout << "====================== Question 1 ======================" << endl << endl;

  load_board("easy.dat", board);
  cout << "Board is ";
  if (!is_complete(board))
    cout << "NOT ";
  cout << "complete." << endl << endl;

  load_board("easy-solution.dat", board);
  cout << "Board is ";
  if (!is_complete(board))
    cout << "NOT ";
  cout << "complete." << endl << endl;

  cout << "====================== Question 2 ======================" << endl << endl;

  load_board("easy.dat", board);

  // Should be OK
  cout << "Putting '1' into I8 is ";
  if (!make_move("I8", '1', board)) 
    cout << "NOT ";
  cout << "a valid move. The board is:" << endl;
  display_board(board);
  cout << endl;
  
  // Should fail due to invalid position
  cout << "Putting '1' into J2 is ";
  if (!make_move("J2", '1', board)) 
    cout << "NOT ";
  cout << "a valid move. The board is:" << endl;
  display_board(board);
  cout << endl;
  
  // Should fail due to logical error
  cout << "Putting '2' into I9 is ";
  if (!make_move("I9", '2', board)) 
    cout << "NOT ";
  cout << "a valid move. The board is:" << endl;
  display_board(board);
  cout << endl;
  
  cout << "====================== Question 3 ======================" << endl << endl;

  load_board("easy.dat", board);
  if (save_board("easy-copy.dat", board))
    cout << "Save board to 'easy-copy.dat' successful." << endl;
  else
    cout << "Save board failed." << endl;
  cout << endl;

  load_board("medium.dat", board);
  //change one of the entries. save should fail
  board[8][8] = 'a'; //invalid character
  cout << "Character in position I9 changed to 'a'.\n";
  if (save_board("medium-copy.dat", board))
    cout << "Save board to 'test-copy.dat' successful." << endl;
  else
    cout << "Save board failed." << endl;
  cout << endl;  

  cout << "====================== Question 4 ======================" << endl << endl;

  //use 'clock' to time how long it takes to solve the mysteries. 
  //(alternatively could count how many possibilities the program computes
  //to solve the mysteries...)
  int start_s, stop_s;
  
  load_board("easy.dat", board);
  start_s = clock();
  if (solve_board(board)) {
    cout << "The 'easy' board has a solution:" << endl;
    display_board(board);
  } else 
    cout << "A solution cannot be found." << endl;
  cout << endl;
  stop_s = clock();
  cout << "Time taken to solve 'easy' is "
  	   << (stop_s-start_s)/static_cast<double>(CLOCKS_PER_SEC) << endl << endl;
  	   
  load_board("medium.dat", board);
  start_s = clock();
  if (solve_board(board)) {
    cout << "The 'medium' board has a solution:" << endl;
    display_board(board);
  } else 
    cout << "A solution cannot be found." << endl;
  cout << endl;
  stop_s = clock();
  cout << "Time taken to solve 'medium' is "
  	   << (stop_s-start_s)/static_cast<double>(CLOCKS_PER_SEC) << endl << endl;
  	   
  cout << "====================== Question 5 ======================" << endl << endl;

  //"mystery1"
  load_board("mystery1.dat", board);
  cout << endl << "Displaying Sudoku board 'mystery1'" << endl;
  display_board(board);
  cout << "Done!" << endl << endl;
  
  start_s = clock();  
  if (solve_board(board)) {
    cout << "The 'mystery1' board has a solution:" << endl;
    display_board(board);
  } else 
    cout << "A solution cannot be found." << endl;
  stop_s = clock();
  cout << "Time taken to solve 'mystery1' is "
  	   << (stop_s-start_s)/static_cast<double>(CLOCKS_PER_SEC) << endl << endl;

  //"mystery2"
  load_board("mystery2.dat", board);
  cout << endl << "Displaying Sudoku board 'mystery2'" << endl;
  display_board(board);
  cout << "Done!" << endl << endl;

  if (solve_board(board)) {
    cout << "The 'mystery2' board has a solution:" << endl;
    display_board(board);
  } else 
    cout << "A solution cannot be found." << endl;
  cout << endl;

  //"mystery3"
  load_board("mystery3.dat", board);
  cout << endl << "Displaying Sudoku board 'mystery3'" << endl;
  display_board(board);
  cout << "Done!" << endl << endl;

  start_s = clock();
  if (solve_board(board)) {
    cout << "The 'mystery3' board has a solution:" << endl;
    display_board(board);
  } else 
    cout << "A solution cannot be found." << endl;
  stop_s = clock();
  cout << "Time taken to solve 'mystery3' is "
  	   << (stop_s-start_s)/static_cast<double>(CLOCKS_PER_SEC) << endl << endl;

  return 0;
}
