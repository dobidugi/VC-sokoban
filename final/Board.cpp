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
    for (int i = 0; i < this->ySize(); i++)
    {
        for (int j = 0; j < this->xSize(); j++)
        {
            switch (map[i][j])
            {
            case State::WALL:
                cout << "1";
                break;
            case State::NORMAL:
                cout << "0";
                break;
            case State::PLAYER:
                cout << "9";
                break;
            case State::KEY:
                cout << "2";
                break;
            case State::NOT_CLEAR:
                cout << "3";
                break;
            case State::CLEAR:
                cout << "4";
                break;
            }
        }
        cout << endl;
    }
}


void Board::calcStageSize(int stage)
{
    string file = to_string(stage) + ".dat";
    ifstream in;
    in.open(file);
    if (!in.is_open()) {
        std::cout << "파일을 찾을 수 없습니다!" << std::endl;
    }
    char buff[30];
    int tmpX = 0;
    int tmpY = 0;
    while (in) {
        in.getline(buff, 30);
        for (int z = 0; z < 30; z++) {
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
        in.getline(buff, 30);
        tmpY++;
    }
    this->mapSize = { tmpY, tmpX };
    this->map.resize(tmpY, vector<State>(tmpX, State::NORMAL));
}

void Board::loadStage(int stage) {
    string file = to_string(stage) + ".dat";
    ifstream in;
    string s;
    char buff[30];
    in.open(file);
    if (!in.is_open()) {
        std::cout << "파일을 찾을 수 없습니다!" << std::endl;
        return;
    }
    int i = 0;
    int j = 0;
    this->calcStageSize(stage);

    nowClearCount = 0;
    allClearCount = 0;

    while (in) {
        in.getline(buff, 30);
        for (int k = 0; k < 30; k++) {
            if (buff[k] == NULL)
                break;
            else
            {
                cout << buff[k];
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
    for (int i = 0; i < this->ySize(); i++)
    {
        for (int j = 0; j < this->xSize(); j++)
        {
            switch (map[i][j])
            {
            case State::WALL:
                cout << "1";
                break;
            case State::NORMAL:
                cout << "0";
                break;
            case State::PLAYER:
                cout << "9";
                break;
            case State::KEY:
                cout << "2";
                break;
            case State::NOT_CLEAR:
                cout << "3";
                break;
            case State::CLEAR:
                cout << "4";
                break;
            }
        }
        cout << endl;
    }
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