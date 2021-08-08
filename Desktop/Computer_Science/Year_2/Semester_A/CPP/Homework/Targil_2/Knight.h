#ifndef KNIGHT_H_
#define KNIGHT_H_

#include "Position.h"

class Knight: public Soldier	{

	public:
		Knight();
		Knight(char t, int row, char col);
		int valid_move(Board& board,string command, int owner);
};

#endif
