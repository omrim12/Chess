#ifndef PAWN_H_
#define PAWN_H_

#include "Position.h"

class Pawn: public Soldier	{

	public:
		Pawn();
		Pawn(Pawn *other);
		Pawn(char t,int row,char col);
		bool operator==(Pawn *other);
		int valid_move(Board& board,string command, int owner);
		bool valid_promotion(Board& board,string command,Soldier& s, int owner);

	private:
		int startRow;
		int startCol;
};

#endif
