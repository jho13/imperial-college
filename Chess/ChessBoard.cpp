#include <iostream>
#include <map>
#include <cctype>
#include "ChessBoard.h"
#include "ChessPiece.h"
#include "King.h"
#include "Rook.h"
#include "Queen.h"
#include "Knight.h"
#include "Bishop.h"
#include "Pawn.h"
#include "path.h"

using namespace std;

/************************ private functions  ************************/

void ChessBoard::setup()
{
  //white team
  board["A1"] = new Rook(white,this);
  board["B1"] = new Knight(white,this);
  board["C1"] = new Bishop(white,this);
  board["D1"] = new Queen(white,this);
  board["E1"] = new King(white,this);
  board["F1"] = new Bishop(white,this);
  board["G1"] = new Knight(white,this);
  board["H1"] = new Rook(white,this);
  board["A2"] = new Pawn(white,this);
  board["B2"] = new Pawn(white,this);
  board["C2"] = new Pawn(white,this);
  board["D2"] = new Pawn(white,this);
  board["E2"] = new Pawn(white,this);
  board["F2"] = new Pawn(white,this);
  board["G2"] = new Pawn(white,this);  
  board["H2"] = new Pawn(white,this);  

  //black team
  board["A8"] = new Rook(black,this);
  board["B8"] = new Knight(black,this);
  board["C8"] = new Bishop(black,this);
  board["D8"] = new Queen(black,this);
  board["E8"] = new King(black,this);
  board["F8"] = new Bishop(black,this);
  board["G8"] = new Knight(black,this);
  board["H8"] = new Rook(black,this);
  board["A7"] = new Pawn(black,this);
  board["B7"] = new Pawn(black,this);
  board["C7"] = new Pawn(black,this);
  board["D7"] = new Pawn(black,this);
  board["E7"] = new Pawn(black,this);
  board["F7"] = new Pawn(black,this);
  board["G7"] = new Pawn(black,this);  
  board["H7"] = new Pawn(black,this);  
}

void ChessBoard::clearBoard()
{
  map<const string, ChessPiece*>::iterator it;
  for (it = board.begin(); it != board.end(); it++)
    delete it->second;
  board.clear();
}

void ChessBoard::makeMove(const string from, 
                          const string to, ChessPiece*& store)
{
  if (board.count(to) != 0)
    store = board[to];
  board[to] = board[from];
  board.erase(from);
}

void ChessBoard::rollBack(const string from, 
                          const string to, ChessPiece* store)
{
  board[from] = board[to];
  if (store != NULL)
     board[to] = store;
  else
    board.erase(to);
}  

string ChessBoard::kingPos(Team t) const
{
  map<const string, ChessPiece*>::const_iterator it;
  for (it = board.begin(); it != board.end(); it++)
  {
    if ((it->second)->get_team() == t)
    {
      King* p = dynamic_cast<King*>(it->second);
      if (p != NULL)
        return it->first;
    }
  }
  //error: king is not present
  return "";
}

bool ChessBoard::inBetween(const string& from, const string& to) const
{
  if (diag_path(from,to))
  {
    string pos = from; //check if there is a piece at board[pos]
    int h,v; //horizontal and vertical increments
    h = (from[0] < to[0] ? 1 : -1);
    v = (from[1] < to[1] ? 1 : -1);
    pos[0] += h;
    pos[1] += v; 
    while (pos.compare(to))
    {
      if (board.count(pos) > 0)
        return true;
      pos[0] += h;
      pos[1] += v;
    }
  }
 
  else if(str_path(from,to))
  {
    string pos = from; //check if there is a piece at board[pos]
  	
    //vertical path
    if (from[0] == to[0])
    {
      int v = (from[1] < to[1] ? 1 : -1);
      pos[1] += v;
      while (pos.compare(to))
      {
        if (board.count(pos) > 0)
          return true;
        pos[1] += v;
      }
    }
    //horizontal path
    else
    {
      int h = (from[0] < to[0] ? 1 : -1);
      pos[0] += h;
      while (pos.compare(to))
      {
        if (board.count(pos) > 0)
          return true;
        pos[0] += h;
      } 
    }
  }
  return false;
}

bool ChessBoard::isCheck(Team t) const
{
  const string king_pos = kingPos(t);
  //for all pieces of opposite colour, 
  //check whether a valid move can reach the king
  map<const string, ChessPiece*>::const_iterator it;
  for (it = board.begin(); it != board.end(); it++)
  {
    //pieces of opposite colour
    if ((it->second)->get_team() != t)
    {
      //valid move to king?
      if ((it->second)->valid_move(it->first, king_pos))
        return true;
    }		
  }
  return false;
}

bool ChessBoard::validMove(Team t)
{
  //for all pieces of colour "t"
  //check whether a valid move puts them out of check
  map<const string, ChessPiece*>::const_iterator it;
  for (it = board.begin(); it != board.end(); it++)
  {
    //pieces of colour "t"
    if ((it->second)->get_team() == t)
    {
      //find position "pos" to which the piece can move 
      string pos = "A1";
      while (pos.compare("H8"))
      {
        if (it->second->valid_move(it->first,pos))
        {
          //make the move and see if it puts team "t" out of check
          ChessPiece* store = NULL; 
          makeMove(it->first,pos,store);
          if (!isCheck(t))
          {
            rollBack(it->first,pos,store);
            return true;
          }
          rollBack(it->first,pos,store);
        }
        pos[1] = (pos[0] == 'H' ? pos[1] + 1 : pos[1]); 
	pos[0] = (pos[0] == 'H' ? 'A' : pos[0] + 1);
      }
    } 
  }
  return false;
}

/********************************************************************/


/************************* public functions *************************/

ChessBoard::ChessBoard()
{
  setup();
  turn = white;
  cout << "A new chess game is started!" << endl;
}

void ChessBoard::resetBoard()
{
  clearBoard();
  setup();
  turn = white;
  cout << "A new chess game is started!" << endl;
}

void ChessBoard::submitMove(string from, string to)
{
  //check for right length
  if (from.length() != 2)
  {
    cout << "First argument invalid: "
         << "positions should be two characters long.\n";
    return;
  }
  if (to.length() != 2)
  {
    cout << "Second argument invalid: "
         << "positions should be two characters long.\n";
    return;
  }

  from[0] = toupper(from[0]);
  to[0] = toupper(to[0]);
  //check for valid position
  if (from[0] < 'A' || from[0] > 'H' || from[1] < '1' || from[1] > '8')
  {
    cout << "First argument invalid: first character should be between A-H "
         << "and second character should be between 1-8.\n";
    return;
  }
  if (to[0] < 'A' || to[0] > 'H'|| to[1] < '1' || to[1] > '8')
  {
    cout << "Second argument invalid: first character should be between A-H "
         << "and second character should be between 1-8.\n";
    return;
  }

  //check there is a chess piece at start 'from'
  if (board.count(from) == 0)
  {
    cout << "There is no piece at position " << from << "!\n";
    return;
  }
  
  //check it is the right person's turn
  if (turn != board[from]->get_team())
  {
    cout << "It is not " << !turn << "'s turn to move!\n";
    return;
  }

  //check the move is valid for the individual piece
  if (!board[from]->valid_move(from,to))
  {
    board[from]->print();
    //board[from]->print();
    cout << " cannot move to " << to << "!\n";
    return;
  }
  
  //check the move does not put team "turn" in check   
  ChessPiece* store = NULL; 
  makeMove(from,to,store);
  if (isCheck(turn))
  {
    board[to]->print();
    cout << " cannot move to " << to << "!\n";
    rollBack(from,to,store);
    return;
  }
	
  //move is successful
  board[to]->print();
  cout << " moves from " << from << " to " << to;
  if (store != NULL)
  {
    cout << " taking ";
    store->print();
  }
  delete store;

  //check if opposite team has a valid move
  if (!validMove(!turn))
  {
    if (isCheck(!turn))
      cout << endl << !turn << " is in checkmate\n";
    else
      cout << endl << !turn << " is in stalemate\n";
    //end of game
    clearBoard();
    return;
  }

  //check if team "turn" is in check
  if (isCheck(!turn))
    cout << endl << !turn << " is in check";
  
  //change turn
  turn = (turn == white ? black : white);
  cout << endl;
}

/********************************************************************/
