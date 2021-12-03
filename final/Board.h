#pragma once
#include <vector>
#include "State.h"
using namespace std;
class Board
{
public:
	void setSize(int y, int x);
	int ySize() const;
	int xSize() const;
	void update(int y, int x, State value);
	void loadStage(int stage);
	bool isMovedPlayer(int y, int x);
	State nowPositionState(int y, int x);
	pair<int, int> getPlayerPosition();
	void setPlayerPosition(pair<int, int> pos);
	bool isOutOfRange(int y, int x);
private:
	vector<vector<State>> map;
	pair<int, int> mapSize;
	pair<int, int> playerPos;
	
	void calcStageSize(int stage);
	void draw();
};