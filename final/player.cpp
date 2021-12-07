#include <iostream>
#include "State.h"
#include "Player.h"
#include "Validator.h"

Player::Player(Validator *validator)
{
    this->validator = validator;
    lock = false;
    moveCount = 0;
    direction = 1;
}

Player::~Player()
{

}

void Player::moveUp()
{
    this->move(0);
}

void Player::moveDown()
{
    this->move(1);
}

void Player::moveLeft()
{
    this->move(2);
}

void Player::moveRight()
{
    this->move(3);
}


void Player::move(int direction)
{
  
    if (lock) return;
    this->direction = direction;
    moveCount++;
    int dy[] = { -1, 1, 0, 0 };
    int dx[] = { 0, 0, -1, 1 };

    pair<int, int> PlayerPosition = validator->getPlayerPosition();
    int nowY = PlayerPosition.first;
    int nowX = PlayerPosition.second;
    int ny = dy[direction] + nowY;
    int nx = dx[direction] + nowX;
    if (!validator->isMovePlayer(ny, nx)) return;

    if (validator->isNowPositionStateNormal(ny,nx))
    {
        validator->updateBoard(nowY, nowX, State::NORMAL);
        validator->updateBoard(ny, nx, State::PLAYER);
        validator->setPlayerPosition({ ny, nx });
    }

    else if (validator->isNowPositionStateKey(ny,nx))
    {
  
        int nny = dy[direction] + ny;
        int nnx = dx[direction] + nx;
        if(!validator->isMoveKey(nny,nnx)) return ;
        if (validator->isNowPositionStateNotClear(nny, nnx))
        {
            validator->updateBoard(nny, nnx, State::CLEAR);
            validator->addNowClearCount();
        }

        else if (validator->isNowPositionStateNormal(nny, nnx))
        {
            validator->updateBoard(nny, nnx, State::KEY);
        }

        validator->updateBoard(nowY, nowX, State::NORMAL);
        validator->updateBoard(ny, nx, State::PLAYER);
        validator->setPlayerPosition({ ny, nx });

    }
    if (validator->isEndGame())
    {
        lock = true;
    }

}

int Player::getMoveCount() const
{
    return this->moveCount;
}

void Player::setMoveCount(int count)
{
    this->moveCount = count;
}

int Player::getNowDirection() const
{
    return this->direction;
}