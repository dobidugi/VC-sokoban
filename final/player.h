#pragma once
#include <iostream>
#include "Validator.h"
#include "board.h";
using namespace std;
class player
{
public:
	player(Board* board, Validator* validaotr);
	~player();
	void moveLeft();
	void moveRight();
	void moveUp();
	void moveDown();
private:
	Board* map;
	Validator*  validator;
	void move(int direction);
};