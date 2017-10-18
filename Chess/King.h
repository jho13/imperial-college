#ifndef KING_H
#define KING_H

#include "ChessPiece.h"
#include "ChessBoard.h"
#include <string>

using namespace std;

class King : public ChessPiece
{
  //CONSTRUCTOR
  King(Team t, ChessBoard* p) : ChessPiece(t,p) {}

  //FUNCTION WHICH PRINTS ITSELF
  void print() const;
  
  //FUNCTION WHICH RETURNS 'true' IFF THE MOVE FROM "from" TO "to" IS VALID.
  //A MOVE IS VALID IF THE PATH "from" -> "to" IS LEGITIMATE FOR THE PIECE
  //AND ALSO THERE IS NO PIECE OBSTRUCTING THE MOVE
  bool valid_move(const string& from, const string& to) const;

  //DESTRUCTOR
  ~King() {}

  //"ChessBoard" needs access to member functions
  friend ChessBoard;
};

#endif
