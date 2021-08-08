#include "Bishop.h"
#include "Board.h"
/*******************/
Bishop::Bishop(char t, int row, char col): Soldier(t,row,col){}
/*******************/
int Bishop::valid_move(Board& board,string command, int owner)	{

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
		return ILLEGAL_MOVE;																// or eating self soldier.
	}

	if( col == nCol && row == nRow ) {// staying in place is not a move.
		return ILLEGAL_MOVE;
	}

	if( abs(row - nRow) != abs(col - nCol) )	{ // have to preform diagonal move.
		return ILLEGAL_MOVE;
	}

	int i;

	/****diagonal move****/

	//white move
	if( row < nRow && col < nCol && getOwner() == WHITE )		{ // move to lower-right board. check if its diagonal and clear.

		for(i = 1; row + i <= 7 && (col-'A') + i <= 7; i++)	{

			if( row + i != nRow || col + i != nCol )	{
				if( board(row + i,(col-'A') + i)->getSoldier()->getOwner() != NONE )	{
					return ILLEGAL_MOVE;
				}
			}

			if( row + i == nRow && col + i == nCol )	{

				return true;

			}
		}
	}


	if( row < nRow && col > nCol && getOwner() == WHITE )		{ // move to lower-left board. check if its diagonal and clear.

		for(i = 1; row + i <= 7 && (col-'A') - i >= 0; i++)	{

			if( row + i != nRow || col - i != nCol )	{
				if( board(row + i,(col-'A') - i)->getSoldier()->getOwner() != NONE )	{
					return ILLEGAL_MOVE;
				}
			}

			if( row + i == nRow && col - i == nCol )	{

				return true;
			}
		}
	}

	if( row > nRow && col < nCol && getOwner() == WHITE )		{ // move to upper-right board. check if its diagonal and clear.

		for(i = 1; row - i >= 0 && (col-'A') + i <= 7; i++)	{

			if( row - i != nRow || col + i != nCol )	{
				if( board(row - i,(col-'A') + i)->getSoldier()->getOwner() != NONE )	{
					return ILLEGAL_MOVE;
				}
			}

			if( row - i == nRow && col + i == nCol )	{

				return true;
			}
		}
	}

	if( row > nRow && col > nCol && getOwner() == WHITE )		{ // move to upper-left board. check if its diagonal and clear.

		for(i = 1; row - i >= 0 && (col-'A') - i >= 0; i++)	{

			if( row - i != nRow || col - i != nCol )	{
				if( board(row - i,(col-'A') - i)->getSoldier()->getOwner() != NONE )	{
					return ILLEGAL_MOVE;
				}
			}

			if( row - i == nRow && col - i == nCol )	{


				return true;
			}
		}
	}

	//black move
	if( row < nRow && col < nCol && getOwner() == BLACK )		{ // move to lower-right board. check if its diagonal and clear.

		for(i = 1; row + i <= 7 && (col-'A') + i <= 7; i++)	{

			if( row + i != nRow || col + i != nCol )	{
				if( board(row + i,(col-'A') + i)->getSoldier()->getOwner() != NONE )	{
					return ILLEGAL_MOVE;
				}
			}

			if( row + i == nRow && col + i == nCol )	{


				return true;
			}
		}
	}


	if( row < nRow && col > nCol && getOwner() == BLACK )		{ // move to lower-left board. check if its diagonal and clear.

		for(i = 1; row + i <= 7 && (col-'A') - i >= 0; i++)	{

			if( row + i != nRow || col - i != nCol )	{
				if( board(row + i,(col-'A') - i)->getSoldier()->getOwner() != NONE )	{
					return ILLEGAL_MOVE;
				}
			}

			if( row + i == nRow && col - i == nCol )	{

				return true;
			}
		}
	}

	if( row > nRow && col < nCol && getOwner() == BLACK )		{ // move to upper-right board. check if its diagonal and clear.

		for(i = 1; row - i >= 0 && (col-'A') + i <= 7; i++)	{

			if( row - i != nRow || col + i != nCol )	{
				if( board(row - i,(col-'A') + i)->getSoldier()->getOwner() != NONE )	{
					return ILLEGAL_MOVE;
				}
			}

			if( row - i == nRow && col + i == nCol )	{

				return true;
			}
		}
	}

	if( row > nRow && col > nCol && getOwner() == BLACK )		{ // move to upper-left board. check if its diagonal and clear.

		for(i = 1; row - i >= 0 && (col-'A') - i >= 0; i++)	{

			if( row - i != nRow || col - i != nCol )	{
				if( board(row - i,(col-'A') - i)->getSoldier()->getOwner() != NONE )	{
					return ILLEGAL_MOVE;
				}
			}

			if( row - i == nRow && col - i == nCol )	{

				return true;
			}
		}
	}



	return ILLEGAL_MOVE; // none of valid moves matches the intended move.
}
/*******************/
