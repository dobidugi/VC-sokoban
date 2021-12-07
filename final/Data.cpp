#include <iostream>
#include <vector>
#include "Data.h"

Data::Data(vector<vector<State>> map, int moveCount, int direction, int clearCount)
{
	this->map = map;
	this->moveCount = moveCount;
	this->direction = direction;
	this->clearCount = clearCount;
}
\

int Data::getMoveCount() const
{
	return this->moveCount;
}

int Data::getDirection() const
{
	return this->direction;
}

int Data::getClearCount() const
{
	return this->clearCount;
}

vector<vector<State>> Data::getMap() const
{
	return this->map;
}