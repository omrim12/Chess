#include "Rook.h"
#include "Board.h"
/*******************/
Rook::Rook(char t, int row, char col): Soldier(t,row,col){}
/*******************/
int Rook::valid_move(Board& board,string command, int owner)	{

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
	int i;

	if( getOwner() != owner || board(nRow,nCol-'A')->getSoldier()->getOwner() == owner ){	// trying to move opponent's soldier
		return ILLEGAL_MOVE;																	    // or eating self soldier.
	}

	if( col == nCol && row == nRow ) {// staying in place is not a move.
		return ILLEGAL_MOVE;
	}

	if( abs(nCol - col) == abs(nRow - row) )		{ // cannot preform diagonal movement.
		return ILLEGAL_MOVE;
	}

	/****vertical move*****/
	if( col == nCol && getOwner() == BLACK )	{

		if( row < nRow )	{ // move forward. check if path is clear
			for(i = row + 1; i < nRow; i++)	{
				if( board(i,nCol-'A')->getSoldier()->getType() != '.')	{
					return ILLEGAL_MOVE;
				}
			}
		}

		if( row > nRow )	{ // move backward. check if path is clear
			for(i = nRow + 1; i < row; i++)	{
				if( board(i,nCol-'A')->getSoldier()->getType() != '.')	{
					return ILLEGAL_MOVE;
				}
			}
		}

		return true;
	}

	if( col == nCol && getOwner() == WHITE )	{

		if( row < nRow )	{ // move backward. check if path is clear
			for(i = row + 1; i < nRow; i++)	{
				if( board(i,nCol-'A')->getSoldier()->getType() != '.')	{
					return ILLEGAL_MOVE;
				}
			}
		}

		if( row > nRow )	{ // move forward. check if path is clear
			for(i = nRow + 1; i < row; i++)	{
				if( board(i,nCol-'A')->getSoldier()->getType() != '.')	{
					return ILLEGAL_MOVE;
				}
			}
		}

		return true;
	}

	/****horizonal move*****/
	if( row == nRow && getOwner() == BLACK )	{

		if( col < nCol )	{ // move right. check if path is clear
			for(i = (col-'A') + 1; i < nCol-'A'; i++)	{
				if( board(nRow,i)->getSoldier()->getType() != '.')	{
					return ILLEGAL_MOVE;
				}
			}
		}

		if( col > nCol )	{ // move left. check if path is clear
			for(i = (nCol-'A') + 1; i < (col-'A'); i++)	{
				if( board(nRow,i)->getSoldier()->getType() != '.')	{
					return ILLEGAL_MOVE;
				}
			}
		}

		return true;
	}

	if( row == nRow && getOwner() == WHITE )	{

		if( col < nCol )	{ // move right. check if path is clear
			for(i = (col-'A') + 1; i < (nCol-'A'); i++)	{
				if( board(nRow,i)->getSoldier()->getType() != '.')	{
					return ILLEGAL_MOVE;
				}
			}
		}

		if( col > nCol )	{ // move left. check if path is clear
			for(i = (nCol-'A') + 1; i < (col-'A'); i++)	{
				if( board(nRow,i)->getSoldier()->getType() != '.')	{
					return ILLEGAL_MOVE;
				}
			}
		}

		return true;
	}

	return ILLEGAL_MOVE; // none of valid moves matches the intended move.

}
/*******************/
