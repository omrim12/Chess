#include "Pawn.h"
#include "Board.h"
/*******************/
Pawn::Pawn(char t, int row, char col): Soldier(t,row,col), startRow(row), startCol(col-'A'){}
/*******************/
bool Pawn::operator==(Pawn *other)	{

	if( other->startRow == startRow && other->startCol == startCol )
		return true;

	return false;
}
/*******************/
int Pawn::valid_move(Board& board,string command, int owner) 	{

	if( !board.valid_command(command,owner) )	{
		return INVALID_INPUT;
	}

	char cCol;
	int cRow;
	char nCol;
	int nRow;

	board.parse_command(command,cCol,cRow,nCol,nRow,owner);

	//try to move a opponent's soldier
	if( getOwner() != owner )	{
		return ILLEGAL_MOVE;
	}

	//try to move to a taken position
	if( col == nCol && board(nRow,nCol-'A')->getSoldier()->getType() != '.' )	{
		return ILLEGAL_MOVE;
	}



	/****PROMOTION****/
	if( command.length() == 7 )	{

		//invalid white pawn promotion
		if( owner == WHITE && command[6] != 'q' && command[6] != 'r' && command[6] != 'b' && command[6] != 'n' )	{
			return ILLEGAL_MOVE;
		}

		//invalid black pawn promotion
		if( owner == BLACK && command[6] != 'Q' && command[6] != 'R' && command[6] != 'B' && command[6] != 'N' )	{
			return ILLEGAL_MOVE;
		}

		// if this pawn didnt reach towards the end of board yet
		if( row != 6 && owner == BLACK )	{
			return ILLEGAL_MOVE;
		}

		if( row != 1 && owner == WHITE )	{
			return ILLEGAL_MOVE;
		}

		return true; // ready for promotion
	}


	/****regular moves****/

	// regular white move
	if( col == nCol && getOwner() == WHITE )	{

		if( row < nRow || (row - nRow > 1  && moved) ){	//after moved
			return ILLEGAL_MOVE;
		}

		if( row < nRow || (row - nRow > 2 && !moved) )	{//before moved
			return ILLEGAL_MOVE;
		}

		if(row - nRow == 2 && !moved && board(row - 1,nCol-'A')->getSoldier()->getType() != '.')	{	//trying to pass over other soldier
			return ILLEGAL_MOVE;
		}
		if( justMovedTwice )
			justMovedTwice = false;

		if( row - nRow == 2 )
			justMovedTwice = true;

		return true;
	}

	// regular black move
	if( col == nCol && getOwner() == BLACK )	{

		if(  row > nRow || (nRow - row > 1 && moved) ){	//after moved
			return ILLEGAL_MOVE;
		}

		if(  row > nRow || (nRow - row > 2 && !moved) )	{//before moved
			return ILLEGAL_MOVE;
		}

		if(nRow - row == 2 && !moved && board(row + 1,nCol-'A')->getSoldier()->getType() != '.')	{//trying to pass over other soldier
			return ILLEGAL_MOVE;
		}

		if( justMovedTwice )
			justMovedTwice = false;

		if( nRow - row == 2 )
			justMovedTwice = true;

		return true;
	}

	/****eating moves****/

	// white intended to eat upper-right black soldier
	if( nCol == col + 1 && nRow == row - 1 && getOwner() == WHITE )	{
		if( board(row-1,(col-'A')+1)->getSoldier()->getOwner() == BLACK )	{

			return true;

		}

		/****EN_PASSANT****/
		if( board(row,(col-'A')+1)->getSoldier()->getType() == 'P'
			&& board(row,(col-'A')+1)->getSoldier()->isMovedTwice() )	{

			// en passant preformed
			board(row,(col-'A')+1)->getSoldier()->setAlive(false);
			*board(row,(col-'A')+1) = new Soldier(row,col+1);

			return EN_PASSANT;
		}
	}

	// black intended to eat bottom-right white soldier
	else if( nCol == col + 1 && nRow == row + 1 && getOwner() == BLACK )	{
		if( board(row+1,(col-'A')+1)->getSoldier()->getOwner() == WHITE )		{

			return true;
		}

		/****EN_PASSANT****/
		if( board(row,(col-'A')+1)->getSoldier()->getType() == 'p'
			&& board(row,(col-'A')+1)->getSoldier()->isMovedTwice() )	{

			board(row,(col-'A')+1)->getSoldier()->setAlive(false);
			*board(row,(col-'A')+1) = new Soldier(row,col+1); // en passant preformed

			return EN_PASSANT;
		}

	}

	// white intended to eat upper-left black soldier
	else if( nCol == col - 1 && nRow == row - 1 && getOwner() == WHITE )	{
		if( board(row-1,(col-'A')-1)->getSoldier()->getOwner() == BLACK )		{

			return true;
		}

		/****EN_PASSANT****/
		if( board(row,(col-'A')-1)->getSoldier()->getType() == 'P'
			&& board(row,(col-'A')-1)->getSoldier()->isMovedTwice() )	{

			board(row,(col-'A')-1)->getSoldier()->setAlive(false);
			*board(row,(col-'A')-1) = new Soldier(row,col-1); // en passant preformed

			return EN_PASSANT;
		}
	}

	// black intended to eat bottom-left white soldier
	else if( nCol == col - 1 && nRow == row + 1 && getOwner() == BLACK )	{
		if( board(row+1,(col-'A')-1)->getSoldier()->getOwner() == WHITE )		{

			return true;
		}

		/****EN_PASSANT****/
		if( board(row,(col-'A')-1)->getSoldier()->getType() == 'p'
			&& board(row,(col-'A')-1)->getSoldier()->isMovedTwice() )	{

			//en passant preformed
			board(row,(col-'A')-1)->getSoldier()->setAlive(false);
			*board(row,(col-'A')-1) = new Soldier(row,col-1); // en passant preformed

			return EN_PASSANT;
		}
	}


	return ILLEGAL_MOVE; //none of valid moves matches the intended move
}
/*******************/
