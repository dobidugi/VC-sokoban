#include "Snapshot.h"
#include "Board.h"
#include "Player.h"
#include "State.h"
Snapshot::Snapshot(Board* board, Player* player)
{
	this->board = board;
	this->player = player;
}


void Snapshot::capture()
{
	int y = board->ySize();
	int x = board->xSize();
	vector<vector<State>> tmp(y, vector<State>(x, State::NORMAL));
	
	for (int i = 0; i <y; i++)
	{
		for (int j = 0; j < x; j++)
		{
			tmp[i][j] = board->nowPositionState(i, j);
		}
	}
	
	stack.push({ tmp, {player->getMoveCount() , board->getNowClearCount()} });
	cout << "capture";
}

void Snapshot::rollback()
{
	int y = board->ySize();
	int x = board->xSize();
	if (!stack.empty())
	{
		vector<vector<State>> tmpMap = stack.top().first;
		int tmpCount = stack.top().second.first;
		int tmpClearCount = stack.top().second.second;
		stack.pop();
		for (int i = 0; i <y; i++)
		{
			for (int j = 0; j <x; j++)
			{
				board->update(i, j, tmpMap[i][j]);
				if (tmpMap[i][j] == State::PLAYER)
				{
					board->setPlayerPosition({ i, j });
				}
			}
		}
		player->setMoveCount(tmpCount);
		board->setNowClearCount(tmpClearCount);
	}
	
}