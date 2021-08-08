#include "King.h"
#include "Board.h"
/*******************/
King::King(char t, int row, char col): Soldier(t,row,col), inTest(false){}
/*******************/
int King::valid_move(Board& board,string command, int owner)	{

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
		return ILLEGAL_MOVE;																 // or eating self soldier.
	}

	if( col == nCol && row == nRow ) {// staying in place is not a move.
		return ILLEGAL_MOVE;
	}

	//Castling mode
	if( col+2 == nCol && row == nRow && !moved && !board(7,7)->getSoldier()->isMoved() && owner == WHITE )	{

		return CASTLE;
	}

	if( col+2 == nCol && row == nRow && !moved && !board(0,7)->getSoldier()->isMoved() && owner == BLACK )	{

		return CASTLE;
	}

	if( col-2 == nCol && row == nRow && !moved && !board(7,0)->getSoldier()->isMoved() && owner == WHITE )	{

		return CASTLE;
	}

	if( col-2 == nCol && row == nRow && !moved && !board(0,0)->getSoldier()->isMoved() && owner == BLACK )	{

		return CASTLE;
	}

	/****king moves****/
	if( abs(nRow - row) <= 1 && abs(nCol - col) <= 1 )	{

		return true;
	}

	return ILLEGAL_MOVE;
}
/*******************/

