#include "Queen.h"
#include "Rook.h"
#include "Board.h"
/*******************/
Queen::Queen(char t, int row, char col): Soldier(t,row,col){}
/*******************/
int Queen::valid_move(Board& board,string command, int owner)	{

	if( !board.valid_command(command,owner) )	{
		return INVALID_INPUT;
	}

	char cCol;
	int cRow;
	char nCol;
	int nRow;

	board.parse_command(command,cCol,cRow,nCol,nRow,owner);

	// rook and queen are moving same horizonally and vertically.
	if( col == nCol || row == nRow )	{
		if( owner == BLACK )
			return Rook('R',row,col).valid_move(board,command,owner);

		return Rook('r',row,col).valid_move(board,command,owner);

	}

	// bishop and queen are moving same diagonally.
	if( owner == BLACK )
		return Bishop('B',row,col).valid_move(board,command,owner);

	return Bishop('b',row,col).valid_move(board,command,owner);
}
/*******************/
