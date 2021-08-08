#ifndef SOLDIER_H_
#define SOLDIER_H_
#include <iostream>
#include <cstdlib>
#include <sstream>
using namespace std;

enum {
	NONE = -1,
	WHITE = 0,
	BLACK = 1,
	ILLEGAL_MOVE = 2,
	INVALID_INPUT = 3,
	CASTLE = 4,
	EN_PASSANT = 5,
	IN_CHECK = 6,
	MATE = 7,
	LINE = 8,
	STALEMATE = 9
};

class Board;

class Soldier	{

	public:
		Soldier(int row, char col);
		Soldier(char t,int row,char col);
		virtual ~Soldier();
		Soldier& operator=(Soldier& other);
		virtual bool operator==(Soldier& other);
		virtual int valid_move(Board& board,string command, int owner);
		int getOwner();
		char getType();
		void setRow(int newRow);
		void setCol(char newCol);
		int getRow();
		char getCol();
		void setAlive(bool living);
		bool getAlive();
		bool isMoved();
		bool isMovedTwice(); //for En passant
		void setMoved(bool stat);
		void setTest(bool stat);
		bool getTest();

	protected:
		char type;
		int row;
		char col;
		bool moved;
		bool alive;
		bool inTest;
		bool justMovedTwice; //for En passant. class pawn

};


#endif
