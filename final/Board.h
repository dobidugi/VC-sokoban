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
	State nowPositionState(int y, int x);
	pair<int, int> getPlayerPosition();
	void setPlayerPosition(pair<int, int> pos);
	bool isOutOfRange(int y, int x);
	int getNowClearCount() const;
	int getAllClearCount() const;
	void addNowClearCount();
	bool isFindFile() const;
private:
	vector<vector<State>> map;
	pair<int, int> mapSize;
	pair<int, int> playerPos;
	int nowClearCount;
	int allClearCount;
	void calcStageSize(int stage);
	void draw();
	bool fileFlag;
	int mapMaxSize = 100;
};