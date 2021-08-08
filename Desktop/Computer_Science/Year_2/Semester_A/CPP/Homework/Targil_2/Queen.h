#ifndef QUEEN_H_
#define QUEEN_H_

#include "Position.h"

class Rook;

class Queen: public Soldier	{

	public:
		Queen();
		Queen(char t,int row, char col);
		int valid_move(Board& board,string command, int owner);

};
#endif
