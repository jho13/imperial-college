#ifndef BISHOP_H
#define BISHOP_H

#include "ChessPiece.h"
#include "ChessBoard.h"
#include <string>

using namespace std;

class Bishop : public ChessPiece
{
  //CONSTRUCTOR
  Bishop(Team t, ChessBoard* p) : ChessPiece(t,p) {}

  //FUNCTION WHICH PRINTS ITSELF
  void print() const;
  
  //FUNCTION WHICH RETURNS 'true' IFF THE MOVE FROM "from" TO "to" IS VALID.
  //A MOVE IS VALID IF THE PATH "from" -> "to" IS LEGITIMATE FOR THE PIECE
  //AND ALSO THERE IS NO PIECE OBSTRUCTING THE MOVE
  bool valid_move(const string& from, const string& to) const;

  //DESTRUCTOR
  ~Bishop() {}

  //"ChessBoard" needs access to member functions
  friend ChessBoard;
};

#endif
