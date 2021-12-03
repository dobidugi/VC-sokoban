#pragma once
#include "Board.h"
class Validator 
{
public:
	Validator(Board* board);
	bool isMovePlayer(int y, int x);
	bool isNowPositionStateNormal(int y, int x);
	void updateBoard(int y, int x, State value);
	void setPlayerPosition(pair<int, int>);
private:
	Board* board;
};