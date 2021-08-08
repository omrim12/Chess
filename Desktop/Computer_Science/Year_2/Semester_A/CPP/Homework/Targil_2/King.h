#ifndef KING_H_
#define KING_H_

#include "Position.h"

class King: public Soldier	{

	public:
		King();
		King(char t, int row, char col);
		int valid_move(Board& board,string command, int owner);

	private:
		bool inTest;



};
#endif
