#ifndef POSITION_H_
#define POSITION_H_

#include "Soldier.h"

class Position	{

	public:
		Position();
		Position(int row, int col, Soldier *soldier);
		~Position();
		Position *operator=(Soldier *other);
		Soldier* getSoldier();
		int getRow();
		int getCol();


	private:
		int row;
		int col;
		void setRow(int row);
		void setCol(int col);
		Soldier *soldier;

};


#endif
