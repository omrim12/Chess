#include "Soldier.h"
#include "Board.h"
/*******************/
Soldier::Soldier(int row,char col):
type('.'),
row(row),
col(col),
moved(false),
alive(false),
inTest(false),
justMovedTwice(false)
{}
/*******************/
Soldier::Soldier(char t, int row, char col):
type(t),
row(row),
col(col),
moved(false),
alive(true),
inTest(false),
justMovedTwice(false)
{}
/*******************/
Soldier::~Soldier()	{}
/*******************/
Soldier& Soldier::operator=(Soldier& other)
{
	type = other.type;
	moved = other.moved;

	return *this;
}
/*******************/
bool Soldier::operator==(Soldier& other)	{

	if( type == other.type && moved == other.moved )
		return true;
	return false;

}
/*******************/
int Soldier::valid_move(Board& board,string command, int owner)	{

	return ILLEGAL_MOVE; // cannot move a default soldier.
}
/*******************/
int Soldier::getOwner()	{

	if( type == '.' )
		return NONE;

	if( isupper(type) )
		return BLACK;

	return WHITE;

}
/*******************/
char Soldier::getType()	{
	return type;
}
/*******************/
int Soldier::getRow()	{

	return row;
}
/*******************/
char Soldier::getCol()	{

	return col;
}
/*******************/
void Soldier::setRow(int newRow)	{

	row = newRow;
}
/*******************/
void Soldier::setCol(char newCol)	{

	col = newCol;
}
/******************/
void Soldier::setAlive(bool living)	{
	alive = living;
}
/******************/
bool Soldier::getAlive()	{
	return alive;
}
/******************/
bool Soldier::isMoved()	{
	return moved;
}
/******************/
bool Soldier::isMovedTwice(){

	return justMovedTwice;
}
/******************/
void Soldier::setMoved(bool stat)	{
	moved = stat;
}
/*******************/
void Soldier::setTest(bool stat)	{
	inTest = stat;
}
/*******************/
bool Soldier::getTest()	{
	return inTest;
}
