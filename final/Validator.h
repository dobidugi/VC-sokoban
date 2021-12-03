#pragma once
#include "Board.h"
class Validator 
{
public:
	Validator(Board* board);
	bool isMovePlayer(int y, int x);
	bool isMoveKey(int y, int x);
	bool isNowPositionStateNormal(int y, int x);
	bool isNowPositionStateKey(int y, int x);
	bool isNowPositionStateNotClear(int y, int x);
	void updateBoard(int y, int x, State value);
	void setPlayerPosition(pair<int, int>);
	pair<int, int> getPlayerPosition() const;
private:
	Board* board;
};