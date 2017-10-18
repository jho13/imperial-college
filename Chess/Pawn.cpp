#include "Pawn.h"
#include "path.h"
#include <iostream>
#include <cstdlib>

using namespace std;

void Pawn::print() const
{
  cout << team << "'s Pawn";
}

bool Pawn::valid_move(const string& from, const string& to) const
{
  //"from" and "to" are distinct
  if (same(from,to))
    return false;

  //there is no piece of the same colour at destination
  if (cbptr->board.count(to) > 0 && (cbptr->board[to]->get_team() == team))
    return false;

  //going in right direction
  if ((!team && from[1] - to[1] <= 0) || (team && from[1] - to[1] >= 0))
    return false;

  //path is either diagonal or straight
  if (!(str_path(from,to) || diag_path(from,to)))
    return false;

  //valid region is ㅗ or ㅜ shape in front of the pawn
  if (!adj(from,to) && !((abs(from[1] - to[1]) == 2) 
    && (from[0] - to[0] == 0)))
    return false;

  //diagonal move iff is a piece at "to"
  if ((abs(from[0] - to[0]) == 1) && (cbptr->board.count(to) == 0))
    return false;
  if ((abs(from[0] - to[0]) == 0) && (cbptr->board.count(to) > 0))
    return false;
  
  //only move two squares on first go
  if (abs(from[1] - to[1]) == 2 && team == white && from[1] != '2')
    return false;
  if (abs(from[1] - to[1]) == 2 && team == black && from[1] != '7')
    return false;
  
  //there is no piece between source and destination squares
  if (cbptr->inBetween(from,to))
    return false;

  //move is successful
  return true;
}
