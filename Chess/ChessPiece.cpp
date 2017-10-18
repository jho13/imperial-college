#include "ChessPiece.h"

ChessPiece::ChessPiece(Team t, ChessBoard* p) : team(t), cbptr(p) {}

Team ChessPiece::get_team() const 
{ 
  return team; 
}
