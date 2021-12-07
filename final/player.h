#pragma once
#include <iostream>
#include "Validator.h"
#include "board.h";
using namespace std;
class Player
{
public:
	Player(Validator* validaotr);
	~Player();
	void moveLeft();
	void moveRight();
	void moveUp();
	void moveDown();
	int getMoveCount() const;
	void setMoveCount(int count);
	int getNowDirection() const;
	void setDirection(int direction);
private:
	Validator*  validator;
	void move(int direction);
	bool lock;
	int moveCount;
	int direction;
};