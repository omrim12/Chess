#include "Board.h"
#include <cstring>
/*******************/


/********Interface Implementation********/
Board::Board():
board(new Position**[LINE]),
white_soldiers(new Soldier*[LINE*2]),
black_soldiers(new Soldier*[LINE*2])
{
	int i;

	for(i = 0; i < LINE; i++)	{
		board[i] = new Position*[LINE];
	}

	//Pawns initializing
	for(i = 0; i < 8; i++)	{
		Pawn *black_P = new Pawn('P',1,i + 'A');
		Pawn *white_P = new Pawn('p',6,i + 'A');
		black_soldiers[i] = black_P;
		white_soldiers[i] = white_P;
		board[1][i] = new Position(1,i,black_P);
		board[6][i] = new Position(6,i,white_P);
	}

	//Rooks initializing
	Rook *black_R1 = new Rook('R',0,0 + 'A');
	Rook *black_R2 = new Rook('R',0,7 + 'A');
	Rook *white_R1 = new Rook('r',7,0 + 'A');
	Rook *white_R2 = new Rook('r',7,7 + 'A');
	black_soldiers[i] = black_R1;
	white_soldiers[i] = white_R1;
	i++;
	black_soldiers[i] = black_R2;
	white_soldiers[i] = white_R2;
	i++;
	board[0][0] = new Position(0,0,black_R1);
	board[0][7] = new Position(0,7,black_R2);
	board[7][0] = new Position(7,0,white_R1);
	board[7][7] = new Position(7,7,white_R2);

	//Knights initializing
	Knight *black_N1 = new Knight('N',0,1 + 'A');
	Knight *black_N2 = new Knight('N',0,6 + 'A');
	Knight *white_N1 = new Knight('n',7,1 + 'A');
	Knight *white_N2 = new Knight('n',7,6 + 'A');
	black_soldiers[i] = black_N1;
	white_soldiers[i] = white_N1;
	i++;
	black_soldiers[i] = black_N2;
	white_soldiers[i] = white_N2;
	i++;
	board[0][1] = new Position(0,1,black_N1);
	board[0][6] = new Position(0,6,black_N2);
	board[7][1] = new Position(7,1,white_N1);
	board[7][6] = new Position(7,6,white_N2);

	//Bishops initializing
	Bishop *black_B1 = new Bishop('B',0,2 + 'A');
	Bishop *black_B2 = new Bishop('B',0,5 + 'A');
	Bishop *white_B1 = new Bishop('b',7,2 + 'A');
	Bishop *white_B2 = new Bishop('b',7,5 + 'A');
	black_soldiers[i] = black_B1;
	white_soldiers[i] = white_B1;
	i++;
	black_soldiers[i] = black_B2;
	white_soldiers[i] = white_B2;
	i++;
	board[0][2] = new Position(0,2,black_B1);
	board[0][5] = new Position(0,5,black_B2);
	board[7][2] = new Position(7,2,white_B1);
	board[7][5] = new Position(7,5,white_B2);

	//Kings & Queens initializing
	Queen *black_Q = new Queen('Q',0,3 + 'A');
	Queen *white_Q = new Queen('q',7,3 + 'A');
	King *whiteKing = new King('k',7,4 + 'A');
	King *blackKing = new King('K',0,4 + 'A');
	black_soldiers[i] = black_Q;
	white_soldiers[i] = white_Q;
	i++;
	black_soldiers[i] = blackKing;
	white_soldiers[i] = whiteKing;
	white_K = whiteKing;
	black_K = blackKing;
	board[0][3] = new Position(0,3,black_Q);
	board[0][4] = new Position(0,4,blackKing);
	board[7][3] = new Position(7,3,white_Q);
	board[7][4] = new Position(7,4,whiteKing);

	//Empty tiles
	for(i = 2; i < 6; i++)	{
		for(int j = 0; j < 8; j++)	{
			board[i][j] = new Position(i,j,new Soldier(i,j + 'A'));
		}
	}

	cout << toString();
}
/*******************/
Board::~Board()	{

	for(int i = 0; i < LINE*2; i++)	{
		for(int j = 0; j < LINE*2; j++)	{
			delete board[i][j];
		}
	}
}
/*******************/
Position *Board::operator()(int row, int col)	{

	return board[row][col];
}
/*******************/
void Board::Play()	{ //MAIN GAME METHOD.

	//game status holders
	int blackmate = 0;
	int whitemate = 0;
	int whitecheck = 0;
	int blackcheck = 0;
	int inmate = 0;

	//command buffer
	string command = "";

	//to indicate whether a command successfully parsed
	bool parsed = true;

	//coordinates buffers
	int currRowBuff;
	char currColBuff;
	int nextRowBuff;
	char nextColBuff;
	int valid_move; // to indicate a valid/invalid move durring game
	string checkStatCommand; //to indicate check status during game

	int turn = 1; // to indicate turns

	// while game is still on
	while( whitemate != MATE && blackmate != MATE && whitemate != STALEMATE && blackmate != STALEMATE && !inmate )	{

		/************************************************White's turn************************************************/
		cout << turn << ") White's turn, please enter a move:" << endl;
		getline(cin,command);

		if(!cin)
			return;

		// input parser
		parsed = parse_command(command,currColBuff,currRowBuff,nextColBuff,nextRowBuff,WHITE);

		/***while move or command are invalid***/

		while( !valid_command(command,WHITE) && !parsed )	{
			cout << turn << ") Invalid input; please enter a move:" << endl;
			getline(cin,command);
			if(!cin)
				return;
			parsed = parse_command(command,currColBuff,currRowBuff,nextColBuff,nextRowBuff,WHITE);
		}

		valid_move = board[currRowBuff][currColBuff - 'A']->getSoldier()->valid_move(*this,command,WHITE);

		if( valid_move != ILLEGAL_MOVE && valid_move != INVALID_INPUT )	{
			whitecheck = checkNextMove(currRowBuff,currColBuff -'A',nextRowBuff,nextColBuff-'A',WHITE,1);
		}

		while( valid_move == ILLEGAL_MOVE || valid_move == INVALID_INPUT || whitecheck == IN_CHECK )	{

			if( valid_move == ILLEGAL_MOVE || whitecheck == IN_CHECK )	{
				cerr << turn << ") Illegal move; please enter a move:" << endl;
				getline(cin,command);
				if(!cin)
					return;
				parsed = parse_command(command,currColBuff,currRowBuff,nextColBuff,nextRowBuff,WHITE);
				if( parsed )
					valid_move = board[currRowBuff][currColBuff - 'A']->getSoldier()->valid_move(*this,command,WHITE);
				if( valid_move != INVALID_INPUT && valid_move != ILLEGAL_MOVE )	{
					whitecheck = checkNextMove(currRowBuff,currColBuff -'A',nextRowBuff,nextColBuff-'A',WHITE,1);
				}
			}

			while( !valid_command(command,WHITE) )	{
				cout << turn << ") Invalid input; please enter a move:" << endl;
				getline(cin,command);
				if(!cin)
					return;
				parsed = parse_command(command,currColBuff,currRowBuff,nextColBuff,nextRowBuff,WHITE);
				if( parsed )
					valid_move = board[currRowBuff][currColBuff - 'A']->getSoldier()->valid_move(*this,command,WHITE);
				if( valid_move != INVALID_INPUT && valid_move != ILLEGAL_MOVE )	{
					whitecheck = checkNextMove(currRowBuff,currColBuff -'A',nextRowBuff,nextColBuff-'A',WHITE,1);
				}
			}
		}

		/***command and move are valid***/

		// PROMOTION INDICATED
		if( command.length() == 7 )	{
			board[nextRowBuff][nextColBuff - 'A']->getSoldier()->setAlive(false); //soldier got eaten
			switch( command[6] ) 	{// indicates type to promote

				case 'q':
					*board[nextRowBuff][nextColBuff - 'A'] = new Queen('q',nextRowBuff,nextColBuff);
					break;
				case 'r':
					*board[nextRowBuff][nextColBuff - 'A'] = new Rook('r',nextRowBuff,nextColBuff);
					break;
				case 'n':
					*board[nextRowBuff][nextColBuff - 'A'] = new Knight('n',nextRowBuff,nextColBuff);
					break;
				case 'b':
					*board[nextRowBuff][nextColBuff - 'A'] = new Bishop('b',nextRowBuff,nextColBuff);
					break;
			}
			//Pawn has been promoted. update new soldier at soldiers array.
			changeSoldier(board[currRowBuff][currColBuff-'A']->getSoldier(),board[nextRowBuff][nextColBuff - 'A']->getSoldier(),WHITE);
			board[nextRowBuff][nextColBuff - 'A']->getSoldier()->setMoved(true);
		}

		else	{
			//Castling mode
			if( valid_move == CASTLE )	{

				if( currColBuff < nextColBuff )	{
				board[7][7]->getSoldier()->setMoved(true);
				*board[7][5] = board[7][7]->getSoldier();
				*board[7][7] = new Soldier(7,7);
				}

				else {
					board[7][0]->getSoldier()->setMoved(true);
					*board[7][3] = board[7][0]->getSoldier();
					*board[7][0] = new Soldier(7,0);
				}
			}

			board[nextRowBuff][nextColBuff - 'A']->getSoldier()->setAlive(false); //soldier got eaten
			*board[nextRowBuff][nextColBuff - 'A'] = board[currRowBuff][currColBuff - 'A']->getSoldier();
			board[nextRowBuff][nextColBuff - 'A']->getSoldier()->setMoved(true);
		}
		*board[currRowBuff][currColBuff - 'A'] = new Soldier(currRowBuff,currColBuff);

		/***Recheck game status***/

		blackmate = isMate(black_K,BLACK);
		whitemate = isMate(white_K,WHITE);
		inmate = isInMate();

		cout << toString();

		// if game has ended
		if( whitemate || blackmate || inmate )
			continue;

		turn++; //turn has been taken. increase turns
		/************************************************Black's turn************************************************/
		cout << turn << ") Black's turn, please enter a move:" << endl;
		getline(cin,command);
		if(!cin)
			return;

		// input parser
		parsed = parse_command(command,currColBuff,currRowBuff,nextColBuff,nextRowBuff,BLACK);

		/***while move or command are invalid***/

		while( !valid_command(command,WHITE) && !parsed )	{
			cout << turn << ") Invalid input; please enter a move:" << endl;
			getline(cin,command);
			if(!cin)
				return;
			parsed = parse_command(command,currColBuff,currRowBuff,nextColBuff,nextRowBuff,BLACK);
		}

		valid_move = board[currRowBuff][currColBuff - 'A']->getSoldier()->valid_move(*this,command,BLACK);
		if( valid_move != ILLEGAL_MOVE && valid_move != INVALID_INPUT )
			blackcheck = checkNextMove(currRowBuff,currColBuff -'A',nextRowBuff,nextColBuff-'A',BLACK,1);

		while( valid_move == ILLEGAL_MOVE|| valid_move == INVALID_INPUT || blackcheck == IN_CHECK )	{

			if( valid_move == ILLEGAL_MOVE || blackcheck == IN_CHECK )	{
				cerr << turn << ") Illegal move; please enter a move:" << endl;
				getline(cin,command);
				if(!cin)
					return;
				parsed = parse_command(command,currColBuff,currRowBuff,nextColBuff,nextRowBuff,BLACK);
				if( parsed )
					valid_move = board[currRowBuff][currColBuff - 'A']->getSoldier()->valid_move(*this,command,BLACK);
				if( valid_move != INVALID_INPUT && valid_move != ILLEGAL_MOVE )	{
					blackcheck = checkNextMove(currRowBuff,currColBuff -'A',nextRowBuff,nextColBuff-'A',BLACK,1);
				}
			}

			while( !valid_command(command,WHITE) )	{
				cout << turn << ") Invalid input; please enter a move:" << endl;
				getline(cin,command);
				if(!cin)
					return;
				parsed = parse_command(command,currColBuff,currRowBuff,nextColBuff,nextRowBuff,BLACK);
				if( parsed )
					valid_move = board[currRowBuff][currColBuff - 'A']->getSoldier()->valid_move(*this,command,BLACK);
				if( valid_move != INVALID_INPUT && valid_move != ILLEGAL_MOVE )	{
					blackcheck = checkNextMove(currRowBuff,currColBuff -'A',nextRowBuff,nextColBuff-'A',BLACK,1);
				}
			}
		}

		/***command and move are valid***/

		// PROMOTION INDICATED
		if( command.length() == 7 )	{
			board[nextRowBuff][nextColBuff - 'A']->getSoldier()->setAlive(false); //soldier got eaten
			switch( command[6] ) 	{// indicates type to promote

				case 'Q':
					*board[nextRowBuff][nextColBuff - 'A'] = new Queen('Q',nextRowBuff,nextColBuff);
					break;
				case 'R':
					*board[nextRowBuff][nextColBuff - 'A'] = new Rook('R',nextRowBuff,nextColBuff);
					break;
				case 'N':
					*board[nextRowBuff][nextColBuff - 'A'] = new Knight('N',nextRowBuff,nextColBuff);
					break;
				case 'B':
					*board[nextRowBuff][nextColBuff - 'A'] = new Bishop('B',nextRowBuff,nextColBuff);
					break;
			}
			//Pawn has been promoted. update new soldier at soldiers array.
			changeSoldier(board[currRowBuff][currColBuff-'A']->getSoldier(),board[nextRowBuff][nextColBuff - 'A']->getSoldier(),BLACK);
			board[nextRowBuff][nextColBuff - 'A']->getSoldier()->setMoved(true);
		}

		else	{
			//Castling mode
			if( valid_move == CASTLE )	{
				if( currColBuff < nextColBuff )	{
				board[0][7]->getSoldier()->setMoved(true);
				*board[0][5] = board[0][7]->getSoldier();
				*board[0][7] = new Soldier(0,7);

				}

				else {
					board[0][0]->getSoldier()->setMoved(true);
					*board[0][3] = board[0][0]->getSoldier();
					*board[0][0] = new Soldier(0,0);
				}
			}

			board[nextRowBuff][nextColBuff - 'A']->getSoldier()->setAlive(false); //soldier got eaten
			*board[nextRowBuff][nextColBuff - 'A'] = board[currRowBuff][currColBuff - 'A']->getSoldier();
			board[nextRowBuff][nextColBuff - 'A']->getSoldier()->setMoved(true);
		}
		*board[currRowBuff][currColBuff - 'A'] = new Soldier(currRowBuff,currColBuff);

		/***Recheck game status***/

		blackmate = isMate(black_K,BLACK);
		whitemate = isMate(white_K,WHITE);
		inmate = isInMate();

		cout << toString();
		turn++; //turn has been taken. increase turns
	}


	//Game has ended. verify what was the game status
	if( whitemate == MATE)
		cout << "Black wins with checkmate!" << endl;
	if( blackmate == MATE )
		cout << "White wins with checkmate!" << endl;
	if( whitemate == STALEMATE || blackmate == STALEMATE )
		cout << "The game is drawn due to stalemate!" << endl;
	if( inmate )
		cout << "The game is drawn due to insufficient material!" << endl;

	delete this; //Program ended.
}
/*******************/
bool Board::valid_command(const string command, int owner) const	{ //COMMAND VALIDATOR

	//potential promotion move
	if( command.length() == 7 )	{

		if( command[0] < 'A' ||  command[0] > 'H' || command[1] > '8' || command[1] < '1'
			|| command[3] < 'A' || command[3] > 'H' || command[4] > '8' || command[4] < '1' || command[2] != ' '
			|| command[5] != ' ' )
			return false;

		return true;
	}

	if( command.length() != 5 )
		return false;

	if( command[0] < 'A' ||  command[0] > 'H' || command[1] > '8' || command[1] < '1'
		|| command[3] < 'A' || command[3] > 'H' || command[4] > '8' || command[4] < '1'
		|| command [2] != ' ' )
		return false;

	return true;
}
/*******************/
bool Board::parse_command(const string command, char& currCol, int& currRow, char& nextCol, int& nextRow,int owner)	{ //COMMAND PARSER FROM INPUT

	if( !valid_command(command,owner) )
		return false;

	currCol = command[0];
	currRow = LINE - (command[1] - '0');
	nextCol = command[3];
	nextRow = LINE - (command[4] - '0');

	return true;

}
/*******************/
string Board::create_command(int currRow, char currCol, int nextRow, char nextCol)	{ //CREATES AN ARTIFICIAL COMMAND

	stringstream new_command;

	new_command << currCol;
	new_command << LINE - currRow;
	new_command << ' ';
	new_command << nextCol;
	new_command << LINE - nextRow;

	return new_command.str();
}
/*******************/
bool Board::isCheck(King *k,int owner)	{ // runs on each player from the opposite team and indicates if a
									      // valid move towards the king can be taken.

	if( owner == WHITE )	{

		for(int i = 0; i < LINE*2; i++)	{
			string checkStatCommand = create_command(black_soldiers[i]->getRow(),black_soldiers[i]->getCol(),white_K->getRow(),white_K->getCol());
			black_soldiers[i]->setTest(true);

			if( black_soldiers[i]->valid_move(*this,checkStatCommand,BLACK) == 1 && black_soldiers[i]->getAlive() )	{
				black_soldiers[i]->setTest(false);
				return true;
			}
			black_soldiers[i]->setTest(false);
		}
	}

	if( owner == BLACK )	{

		for(int i = 0; i < LINE*2; i++)	{
			string checkStatCommand = create_command(white_soldiers[i]->getRow(),white_soldiers[i]->getCol(),black_K->getRow(),black_K->getCol());
			white_soldiers[i]->setTest(true);

			if( white_soldiers[i]->valid_move(*this,checkStatCommand,WHITE) == 1 && white_soldiers[i]->getAlive())	{
				white_soldiers[i]->setTest(false);
				return true;
			}
			white_soldiers[i]->setTest(false);
		}
	}

	return false;

}
/*******************/
int Board::isMate(King *k, int owner)	{ //returns if a game has ended due to mate or stalemate.

	string checkStatCommand;
	int nextMoveStatus;

	if( owner == WHITE )	{

		//check for each player if can prevent threat on king.
		for(int index = 0; index < LINE*2; index++)	{
			if( !white_soldiers[index]->getAlive() )
				continue;
			for(int i = -7; i <= 7; i++)	{
				for(int j = -7; j <= 7; j++)	{
					if( i != 0 || j != 0 )			{

						//critical to know if those soldiers moved or not
						if( white_soldiers[index]->getType() == 'k' || white_soldiers[index]->getType() == 'p' || white_soldiers[index]->getType() == 'r' )
							white_soldiers[index]->setTest(true);

						checkStatCommand = create_command(white_soldiers[index]->getRow(),white_soldiers[index]->getCol(),white_soldiers[index]->getRow() + i,white_soldiers[index]->getCol() + j);
						if( white_soldiers[index]->valid_move(*this,checkStatCommand,WHITE) == 1 )	{
							nextMoveStatus = checkNextMove(white_soldiers[index]->getRow(),white_soldiers[index]->getCol()-'A',white_soldiers[index]->getRow() + i,(white_soldiers[index]->getCol()-'A') + j,WHITE,1);

							//if next valid position is not threatening king and is valid
							if( nextMoveStatus != IN_CHECK )	{
								white_soldiers[index]->setTest(false);
								return false;
							}
						}

						white_soldiers[index]->setTest(false);
					}
				}
			}
		}
	}

	if( owner == BLACK )	{

		//check for each player if can prevent threat on king.
		for(int index = 0; index < LINE*2; index++)	{
			if( !black_soldiers[index]->getAlive() )
				continue;
			for(int i = -7; i <= 7; i++)	{
				for(int j = -7; j <= 7; j++)	{
					if( i != 0 || j != 0 )			{

						//critical to know if those soldiers moved or not
						if( black_soldiers[index]->getType() == 'K' || black_soldiers[index]->getType() == 'P' || black_soldiers[index]->getType() == 'R' )
							black_soldiers[index]->setTest(true);

						checkStatCommand = create_command(black_soldiers[index]->getRow(),black_soldiers[index]->getCol(),black_soldiers[index]->getRow() + i,black_soldiers[index]->getCol() + j);
						if( black_soldiers[index]->valid_move(*this,checkStatCommand,BLACK) == 1 )	{
							nextMoveStatus = checkNextMove(black_soldiers[index]->getRow(),black_soldiers[index]->getCol()-'A',black_soldiers[index]->getRow() + i,(black_soldiers[index]->getCol()-'A') + j,BLACK,1);

							//if next valid position is not threatening king and is valid
							if( nextMoveStatus != IN_CHECK )	{
								black_soldiers[index]->setTest(false);
								return false;
							}
						}

						black_soldiers[index]->setTest(false);
					}
				}
			}
		}
	}

	if( owner == WHITE && isCheck(white_K,WHITE) )	{
		return MATE;
	}

	if( owner == BLACK && isCheck(black_K,BLACK) )	{
		return MATE;
	}

	return STALEMATE; //king was not in check status but there were no legal moves to preform.

}
/*******************/
bool Board::isInMate()	{ // insufficient material

	int i;

	int livingBlackBishop = 0;
	int livingWhiteBishop = 0;

	int livingBlackKnight = 0;
	int livingWhiteKnight = 0;

	bool insufficient_m_WHITE = false;
	bool insufficient_m_BLACK = false;

	/**********************************************************************/
	for(i = 0; i < LINE*2; i++)	{

		if( white_soldiers[i]->getAlive() == true && white_soldiers[i]->getType() == 'p' ) //if any pawn left on board
			return false;

		// can only be a pair of a king and bishop or a king and knight or only a king
		if( white_soldiers[i]->getAlive() == true && white_soldiers[i]->getType() != 'b' && white_soldiers[i]->getType() != 'n' && white_soldiers[i]->getType() != 'k' )
			return false;

		if( white_soldiers[i]->getType() == 'b' && white_soldiers[i]->getAlive())
			livingWhiteBishop++;

		if( white_soldiers[i]->getType() == 'n' && white_soldiers[i]->getAlive() )
			livingWhiteKnight++;
	}

	/**********************************************************************/
	for(i = 0; i < LINE*2; i++)	{

		if( black_soldiers[i]->getAlive() == true && black_soldiers[i]->getType() == 'P' ) //if any pawn left on board
					return false;

		// can only be a pair of a king and bishop or a king and knight or only a king
		if( black_soldiers[i]->getAlive() == true && black_soldiers[i]->getType() != 'B' && black_soldiers[i]->getType() != 'N' && black_soldiers[i]->getType() != 'K' )
			return false;

		if( black_soldiers[i]->getType() == 'B' && black_soldiers[i]->getAlive() )
			livingBlackBishop++;

		if( black_soldiers[i]->getType() == 'N' && black_soldiers[i]->getAlive() )
			livingBlackKnight++;
	}
	/**********************************************************************/
	if( livingWhiteBishop > 1 || livingWhiteKnight > 1 || livingBlackBishop > 1 || livingBlackKnight > 1 )
		return false;

	if( livingWhiteBishop == 1 && livingWhiteKnight == 0 && white_K->getAlive() )
		insufficient_m_WHITE = true;

	if( livingWhiteBishop == 0 && livingWhiteKnight == 1 && white_K->getAlive() )
		insufficient_m_WHITE = true;

	if( livingBlackBishop == 1 && livingBlackKnight == 0 && black_K->getAlive() )
		insufficient_m_BLACK = true;

	if( livingBlackBishop == 0 && livingBlackKnight == 1 && black_K->getAlive() )
		insufficient_m_BLACK = true;

	if( insufficient_m_BLACK && insufficient_m_WHITE )
		return true;

	return false;
}
/*******************/
King *Board::getKing(int owner)	{

	if(owner == WHITE )
		return white_K;

	return black_K;
}
/*******************/
int Board::checkNextMove(int cRow, int cCol, int nRow, int nCol, int owner, int special)	{ // returns if a soldier's move is putting/keeping his king in check status.

	if( owner == BLACK && board[nRow][nCol]->getSoldier() == white_K )
		return IN_CHECK;

	if( owner == WHITE && board[nRow][nCol]->getSoldier() == black_K )
		return IN_CHECK;

	Soldier *savedInCurr = board[cRow][cCol]->getSoldier(); //save soldier in current position
	Soldier *savedInNext = board[nRow][nCol]->getSoldier(); //save soldier in next position
	Soldier *rookBefore; 									//in case of simulating castling.
	Soldier *rookAfter;

	// Simulating a move to new position and check if entering a check status
	savedInNext->setAlive(false);
	*board[nRow][nCol] = board[cRow][cCol]->getSoldier(); // move to new position
	*board[cRow][cCol] = new Soldier(cRow,cCol); 		// clear old position

	if( special == CASTLE )	{ //simulate castling special move

		if( cCol > nCol )	{
			if( owner == WHITE )	{
				rookBefore = board[7][0]->getSoldier();
				rookAfter = board[7][3]->getSoldier();

				*board[7][3] = board[7][0]->getSoldier();
				*board[7][0] = new Soldier(7,0);
			}
			else	{
			rookBefore = board[0][0]->getSoldier();
			rookAfter = board[0][3]->getSoldier();

			*board[0][3] = board[0][0]->getSoldier();
			*board[0][0] = new Soldier(0,0);
			}
		}


		if( cCol < nCol )	{
			if( owner == WHITE )	{
				rookBefore = board[7][7]->getSoldier();
				rookAfter = board[7][5]->getSoldier();

				*board[7][5] = board[7][7]->getSoldier();
				*board[7][7] = new Soldier(7,7);
			}
			else	{
			rookBefore = board[0][7]->getSoldier();
			rookAfter = board[0][5]->getSoldier();

			*board[0][5] = board[0][7]->getSoldier();
			*board[0][7] = new Soldier(0,7);
			}
		}
	}

	if( isCheck(getKing(owner),owner) )	{

		savedInNext->setAlive(true);
		*board[nRow][nCol] = savedInNext;// return saved soldier to intended position.
		*board[cRow][cCol] = savedInCurr;// return current soldier to original position

		if( special == CASTLE )	{
			if( cCol > nCol )	{
				if( owner == WHITE )	{
					*board[7][0] = rookBefore;
					*board[7][3] = rookAfter;
				}
				else	{
				*board[0][0] = rookBefore;
				*board[0][3] = rookAfter;
				}
			}


			if( cCol < nCol )	{
				if( owner == WHITE )	{
					*board[7][7] = rookBefore;
					*board[7][5] = rookAfter;
				}
				else	{
				*board[0][7] = rookBefore;
				*board[0][5] = rookAfter;
				}
			}
		}

		return IN_CHECK; //cannot move into check
	}

	savedInNext->setAlive(true);
	*board[nRow][nCol] = savedInNext; // return saved soldier to intended position.
	*board[cRow][cCol] = savedInCurr; // return current soldier to original position

	if( special == CASTLE )	{
		if( cCol > nCol )	{
			if( owner == WHITE )	{
				*board[7][0] = rookBefore;
				*board[7][3] = rookAfter;
			}
			else	{
			*board[0][0] = rookBefore;
			*board[0][3] = rookAfter;
			}
		}


		if( cCol < nCol )	{
			if( owner == WHITE )	{
				*board[7][7] = rookBefore;
				*board[7][5] = rookAfter;
			}
			else	{
			*board[0][7] = rookBefore;
			*board[0][5] = rookAfter;
			}
		}
	}

	return 1;

}
/*******************/
string Board::toString()	{

	string displayBoard = "";
	int rowDisplay = 0;
	int i;

	while( rowDisplay < 8)	{
		displayBoard += '8' - rowDisplay;
		displayBoard += " ";
		for(i = 0; i < 7; i++)	{
			displayBoard += board[rowDisplay][i]->getSoldier()->getType();
			displayBoard += " ";
		}
		displayBoard += board[rowDisplay][i]->getSoldier()->getType();
		displayBoard += '\n';
		rowDisplay++;
	}

	displayBoard += "  ";
	for(i = 0; i < 7; i++)	{
		displayBoard += ('A' + i);
		displayBoard += " ";
	}
	displayBoard += ('A' + i);

	displayBoard += '\n';

	return displayBoard;
}
/*******************/
void Board::changeSoldier(Soldier *root, Soldier *dest, int owner)	{ // for updating soldiers array after promotion move

	for(int i = 0; i < LINE; i++)	{

		if( owner == WHITE && white_soldiers[i] == root )	{
			delete white_soldiers[i];
			white_soldiers[i] = dest;
			white_soldiers[i]->setMoved(true);
			return;
		}

		if( owner == BLACK && black_soldiers[i] == root )	{
			delete black_soldiers[i];
			black_soldiers[i] = dest;
			black_soldiers[i]->setMoved(true);
			return;
		}
	}
}
