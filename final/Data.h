#pragma once
#include "State.h";
#include <vector>

using namespace  std;
class Data
{
public:
	int getMoveCount() const;
	int getDirection() const;
	int getClearCount() const;
	vector<vector<State>> getMap() const;
	Data(vector<vector<State>> map, int moveCount, int  direction, int clearCount);
private:
	int moveCount;
	int direction;
	int clearCount;
	vector<vector<State>> map;
};