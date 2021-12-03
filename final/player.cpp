#include <iostream>
#include "State.h"
#include "player.h"
#include "Direction.h"
#include "Validator.h"

player::player(Board *brd, Validator *validator)
{
    this->map = brd;
    this->validator = validator;
}

player::~player()
{

}

void player::moveUp()
{
    this->move(0);
}

void player::moveDown()
{
    this->move(1);
}

void player::moveLeft()
{
    this->move(2);
}

void player::moveRight()
{
    this->move(3);
}


void player::move(int direction)
{
  
    int dy[] = { -1, 1, 0, 0 };
    int dx[] = { 0, 0, -1, 1 };

    pair<int, int> playerPosition = this->map->getPlayerPosition();
    int nowY = playerPosition.first;
    int nowX = playerPosition.second;
    int ny = dy[direction] + nowY;
    int nx = dx[direction] + nowX;
    if (!validator->isMovePlayer(ny, nx)) return;

    if (validator->isNowPositionStateNormal(ny,nx))
    {
        validator->updateBoard(nowY, nowX, State::NORMAL);
        //this->map->update(nowY, nowX, State::NORMAL);
        validator->updateBoard(ny, nx, State::PLAYER);
        // this->map->update(ny, nx, State::PLAYER);
        validator->setPlayerPosition({ ny, nx });
        //this->map->setPlayerPosition({ ny, nx });
    }

    /*else if (map[ny][nx] == KEY)
    {
        int nny = dy[direction] + ny;
        int nnx = dx[direction] + nx;
        if (outOfRange(nny, nnx)) return;
        if (!checkMoveKey(nny, nnx)) return;

        if (map[nny][nnx] == NOT_CLEAR) {
            map[nny][nnx] = CLEAR;
            nowClearCount++;
        }
        else if (map[nny][nnx] == NORMAL)
            map[nny][nnx] = KEY;
        map[user.first][user.second] = NORMAL;
        map[ny][nx] = PLAYER;
        updatePlayerPosition(ny, nx);

    }*/


}