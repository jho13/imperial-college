#ifndef CHESSPIECE_H
#define CHESSPIECE_H

#include "ChessBoard.h"
#include "enum.h"
#include <map>
#include <string>

using namespace std;

class ChessPiece 
{
 protected:
  const Team team;
  /*const*/ ChessBoard* cbptr;

  //CONSTRUCTOR
  ChessPiece(Team t, ChessBoard* p);

  //PRINT THE PIECE (E.G. "White's King")
  virtual void print() const = 0;
  
  //DETERMINES WHETHER THE PIECE CAN MOVE FROM "from" TO "to
  //(DOES NOT LOOK AT WHETHER THIS MOVE WOULD PUT THE TEAM IN CHECK)
  virtual bool valid_move(const string& from, const string& to) const = 0;
  
  //DESTRUCTOR
  virtual ~ChessPiece() {}

 public:

  //FUNCTION WHICH RETURS "team"
  Team get_team() const;

  //"ChessBoard" needs access to member functions
  friend ChessBoard;
};

#endif
