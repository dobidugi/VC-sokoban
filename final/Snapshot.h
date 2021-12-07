#pragma once
#include <vector>
#include <stack>
#include "Board.h"
#include "Player.h"
#include "State.h"
#include "Data.h"
class Snapshot
{
public:
	Snapshot(Board *board, Player* player);
	void capture();
	void rollback();
private:
	Board* board;
	Player* player;
	stack<Data> stack;
};