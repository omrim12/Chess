#ifndef BISHOP_H_
#define BISHOP_H_

#include "Position.h"

class Bishop: public Soldier	{

	public:
		Bishop();
		Bishop(char t, int row, char col);
		int valid_move(Board& board,string command, int owner);
};


#endif
