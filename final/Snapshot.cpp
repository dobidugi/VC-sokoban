#include "Snapshot.h"
#include "Board.h"
#include "Player.h"
#include "State.h"
#include "Data.h"
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
	
	Data* data = new Data(tmp, player->getMoveCount(), player->getNowDirection(), board->getNowClearCount());
	stack.push(*data);
}

void Snapshot::rollback()
{
	int y = board->ySize();
	int x = board->xSize();
	if (!stack.empty())
	{
		Data data = stack.top(); stack.pop();
		vector<vector<State>> tmpMap = data.getMap();
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
		player->setMoveCount(data.getMoveCount());
		player->setDirection(data.getDirection());
		board->setNowClearCount(data.getClearCount());
	}
	
}