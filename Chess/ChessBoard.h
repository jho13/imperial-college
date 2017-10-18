#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include <map>
#include <string>
#include "enum.h"

using namespace std;

class ChessPiece;

class ChessBoard
{
 private:
  Team turn;
  map<const string, ChessPiece*> board;
  
  //FUCNTION WHICH SETS UP THE BOARD
  void setup();
  
  //FUNCTION WHICH CLEARS ALL THE PIECES PRESENT ON THE BOARD
  void clearBoard();

  //FUNCTION WHICH MOVES THE PIECE FROM "from" TO "to",
  //TAKING THE PIECE AT "to" IF THERE EXISTS ONE.
  //THE PIECE IS STORED IN "store".
  void makeMove(const string from, const string to, ChessPiece*& store);
  
  //FUNCTION WHICH 'ROLLBACKS' TO THE PREVIOUS STATE BEFORE
  //"makemove".
  void rollBack(const string from, const string to, ChessPiece* store);

  //RETURNS THE POSITION OF TEAM "t" KING
  string kingPos(Team t) const;

  //FUCNTION WHICH RETURNS 'true' IF THERE IS A CHESSPIECE
  //BETWEEN "from" AND "to" (FUNCTION WILL RETURN 'false'
  //IF THE PATH IS NOT DIAGONAL OR STRAIGHT).
  bool inBetween(const string& from, const string& to) const;

  //RETURNS 'true' IF TEAM "t" IS IN CHECK
  bool isCheck(Team t) const;

  //RETURNS 'true' IF TEAM "t" CAN MAKE A VALID MOVE ON THE NEXT GO
  //i.e. A MOVE THAT IS VALID AND RESULTS IN TEAM "t" NOT BEING IN CHECK
  bool validMove(Team t);

  //pieces need to access some member functions of "ChessBoard"
  friend class King;
  friend class Queen;
  friend class Rook;
  friend class Knight;
  friend class Bishop;
  friend class Pawn;
  
 public:
  //CONSTRUCTOR - INCLUDES BOARD SET UP
  ChessBoard();

  //FUCTION WHICH RESETS BOARD TO STARTING STATE
  void resetBoard();
  
  //FUNCTION WHICH PROCESSES A MOVE FROM "from" TO "to".
  //1.CHECKS FOR VALID POSITIONS "from" AND "to"
  //2.CHECKS THERE IS A PIECE OF THE RIGHT COLOUR AT "from"
  //3.CHECKS THE MOVE IS VALID FOR THE INDIVIDUAL PIECES
  //4.CHECKS THE MOVE DOES NOT PUT THE TEAM "turn" IN CHECK 
  //5.IF SUCCESSFUL, MAKES THE MOVE, TAKING ANY PIECES AT "to"
  //6.CHECKS WHETHER THE OTHER TEAM IS IN CHECK OR CHECKMATE OR STALEMATE
  void submitMove(string from, string to);
};

#endif
