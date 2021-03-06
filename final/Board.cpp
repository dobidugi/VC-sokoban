#include <iostream>
#include <string>
#include <fstream>
#include "Board.h"
#include "State.h"



void Board::setSize(int y, int x)
{
	this->mapSize = { y, x };
}

int Board::ySize() const
{
	return this->mapSize.first;
}

int Board::xSize() const
{
	return this->mapSize.second;
}

void Board::update(int y, int x, State value)
{
    this->map[y][x] = value;
}


void Board::calcStageSize(int stage)
{
    string file = to_string(stage) + ".dat";
    ifstream in;
    in.open(file);

 
    char* buff = new char[this->mapMaxSize];
    int tmpX = 0;
    int tmpY = 0;
    while (in) {
        in.getline(buff, mapMaxSize);
        for (int z = 0; z < mapMaxSize; z++) {
            if (buff[z] == NULL) {
                break;
            }
            else {
                tmpX++;
            }
        }
        break;
    }
    while (in) {
        in.getline(buff, mapMaxSize);
        tmpY++;
    }
    this->mapSize = { tmpY, tmpX };
    this->map.resize(tmpY, vector<State>(tmpX, State::NORMAL));
    delete[] buff;
}

void Board::loadStage(int stage) {
    string file = to_string(stage) + ".dat";
    ifstream in;
    string s;
    char* buff = new char[mapMaxSize];
    in.open(file);
    if (!in.is_open()) {
        fileFlag = false;
        return;
    }
    fileFlag = true;
    int i = 0;
    int j = 0;
    this->calcStageSize(stage);

    nowClearCount = 0;
    allClearCount = 0;

    while (in) {
        in.getline(buff, mapMaxSize);
        for (int k = 0; k < mapMaxSize; k++) {
            if (buff[k] == NULL)
                break;
            else
            {
                switch (buff[k] - '0')
                {
                case 0:
                    this->map[i][k] = State::NORMAL;
                    break;
                case 1:
                    this->map[i][k] = State::WALL;
                    break;
                case 2:
                    this->map[i][k] = State::KEY;
                    break;
                case 3:
                    this->map[i][k] = State::NOT_CLEAR;
                    allClearCount++;
                    break;
                case 4:
                    this->map[i][k] = State::CLEAR;
                    allClearCount++;
                    nowClearCount++;
                    break;
                case 9:
                    this->playerPos = { i, k };
                    this->map[i][k] = State::PLAYER;
                    break;
                }
              
                j++;
            }

        }
        i++;
        j = 0;
    }

    delete[] buff;
}

bool Board::isOutOfRange(int y, int x)
{
    if (y < 0 || y >= this->ySize() || x < 0 || x >= this->xSize()) return true;
    return  false;
}


State Board::nowPositionState(int y, int x)
{
    return map[y][x];
}

void Board::draw()
{

}

pair<int, int> Board::getPlayerPosition()
{
    return this->playerPos;
}

void Board::setPlayerPosition(pair<int, int> pos)
{
    this->playerPos = pos;
}

int Board::getNowClearCount() const
{
    return nowClearCount;
}

int Board::getAllClearCount() const
{
    return allClearCount;
}

void Board::addNowClearCount()
{
    this->nowClearCount++;
}

bool Board::isFindFile() const
{
    return this->fileFlag;
}


void Board::setNowClearCount(int count)
{
    this->nowClearCount = count;
}