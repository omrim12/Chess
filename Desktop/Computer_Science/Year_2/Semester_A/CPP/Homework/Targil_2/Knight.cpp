#include "Knight.h"
#include "Board.h"
/*******************/
Knight::Knight(char t, int row, char col): Soldier(t,row,col){}
/*******************/
int Knight::valid_move(Board& board,string command, int owner)	{

	if( command.length() != 5 )	{ // to avoid promotion mode
		return ILLEGAL_MOVE;
	}

	if( !board.valid_command(command,owner) )	{
		return INVALID_INPUT;
	}

	char cCol;
	int cRow;
	char nCol;
	int nRow;

	board.parse_command(command,cCol,cRow,nCol,nRow,owner);

	if( getOwner() != owner || board(nRow,nCol-'A')->getSoldier()->getOwner() == owner )	{// trying to move opponent's soldier
		return ILLEGAL_MOVE;
	}
	if( col == nCol && row == nRow ) {// staying in place is not a move.
		return ILLEGAL_MOVE;
	}

	/****knight moves****/
	if( col == nCol || row == nRow )
		return ILLEGAL_MOVE;

	if(abs(nCol - col) > 2 || abs(nRow - row) > 2)
		return ILLEGAL_MOVE;

	if( abs(abs(nRow - row) - abs(nCol - col)) == 1 )	{

		return true;
	}


	return ILLEGAL_MOVE;

}
/*******************/
