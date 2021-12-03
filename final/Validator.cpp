#include "Validator.h"
#include "State.h"
#include <iostream>

using namespace std;
Validator::Validator(Board* board)
{
	this->board = board;
}



bool Validator::isMovePlayer(int y, int x)
{
	State nowState = board->nowPositionState(y, x);
	if (board->isOutOfRange(y, x)) return false;
	if (nowState == State::WALL || nowState == State::NOT_CLEAR || nowState == State::CLEAR) return false;
	return true;
}

bool Validator::isNowPositionStateNormal(int y, int x)
{
	if (board->nowPositionState(y, x) == State::NORMAL) return true;
	return false;
}

void Validator::updateBoard(int y, int x, State value)
{
	board->update(y, x, value);
}


void Validator::setPlayerPosition(pair<int, int> pos)
{
	board->setPlayerPosition(pos);
}
//bool Board::outOfState(int y, int x)
//{
//    if (y < 0 || y >= this->ySize() || x < 0 || x >= this->xSize()) return true;
//    return  false;
//}
//
//bool Board::isMovedPlayer(int y, int x)
//{
//    if (this->outOfState(y, x)) return false;
//    if (map[y][x] == State::WALL || map[y][x] == State::NOT_CLEAR || map[y][x] == State::CLEAR) return false;
//    return true;
//}