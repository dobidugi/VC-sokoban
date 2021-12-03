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
private:
	Validator*  validator;
	void move(int direction);
};