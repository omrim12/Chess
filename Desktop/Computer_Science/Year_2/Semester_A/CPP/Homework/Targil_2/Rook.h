#ifndef ROOK_H_
#define ROOK_H_

#include "Position.h"

class Rook: public Soldier	{

	public:
		Rook();
		Rook(char t, int row, char col);
		int valid_move(Board& board,string command, int owner);

};
#endif
