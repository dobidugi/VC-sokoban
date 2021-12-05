#pragma once
#include <vector>
#include <stack>
#include "Board.h"
#include "Player.h"
#include "State.h"
class Snapshot
{
public:
	Snapshot(Board *board, Player* player);
	void capture();
	void rollback();
private:
	Board* board;
	Player* player;
	stack<pair<vector<vector<State>>, pair<int, int>>> stack;
};