#include "Position.h"
#include <iostream>
/*******************/
Position::Position()
:row(-1),
 col(-1),
 soldier(new Soldier(-1,-1))
{}
/*******************/
Position::Position(int row, int col, Soldier *soldier)
:row(row),
 col(col),
 soldier(soldier)
{}
/*******************/
Position::~Position()	{delete soldier;}
/*******************/
Position *Position::operator=(Soldier *other)	{

	other->setCol(col + 'A');
	other->setRow(row);

	soldier = other;

	return this;

}
/*******************/
Soldier* Position::getSoldier()	{

	return soldier;
}
/*******************/
int Position::getRow()	{

	return row;
}
/*******************/
int Position::getCol()	{

	return col;
}

