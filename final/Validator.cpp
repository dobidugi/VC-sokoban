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

bool Validator::isNowPositionStateKey(int y, int x) 
{
	if (board->nowPositionState(y, x) == State::KEY) return true;
	return false;
}

bool Validator::isNowPositionStateNotClear(int y, int x)
{
	if (board->nowPositionState(y, x) == State::NOT_CLEAR) return true;
	return false;
}

bool Validator::isMoveKey(int y, int x)
{
	State nowState = board->nowPositionState(y, x);
	if (board->isOutOfRange(y, x)) return false;
	if (nowState == State::WALL || nowState == State::CLEAR) return false;
	return true;
}


void Validator::updateBoard(int y, int x, State value)
{
	board->update(y, x, value);
}


void Validator::setPlayerPosition(pair<int, int> pos)
{
	board->setPlayerPosition(pos);
}

pair<int, int> Validator::getPlayerPosition() const
{
	return board->getPlayerPosition();
}
