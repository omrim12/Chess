#ifndef BOARD_H_
#define BOARD_H_

#include "King.h"
#include "Queen.h"
#include "Rook.h"
#include "Bishop.h"
#include "Knight.h"
#include "Pawn.h"

class Board 	{

	public:
		Board();
		~Board();
		Position *operator()(int row, int col);
		void Play();
		bool valid_command(const string command, int owner) const;
		bool parse_command(const string command, char& currCol, int& currRow, char& nextCol, int& nextRow, int owner);
		string create_command(int currRow, char currCol, int nextRow, char nextCol);
		bool isCheck(King *k, int owner);
		int isMate(King *k, int owner);
		bool isInMate();
		string toString();
		int checkNextMove(int cRow, int cCol, int nRow, int nCol, int owner, int special);


	private:
		King *getKing(int owner);
		void changeSoldier(Soldier *root, Soldier *dest, int owner);
		Position* **board;
		Soldier **white_soldiers;
		Soldier **black_soldiers;
		King *white_K;
		King *black_K;
};

#endif
