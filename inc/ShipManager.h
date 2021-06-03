#ifndef SHIPMANAGER_H
#define SHIPMANAGER_H
#include <BattleShip.h>
#include <iostream>
#include <cctype>
#include <stdlib.h>
#include <time.h>

class ShipManager{
    public:
    ShipManager(int size_x, int size_y);
    Success checkHit(int x, int y);
    void displayBoard();
    bool addShip(int x, int y, int size, bool isVertical);
    void randomBoard();
    void setTile(int x, int y, int i);
    int getTile(int x, int y);
    private:
    void addRandomPiece(int size);
    int size_x, size_y;
    std::vector<std::vector<int> > board;
    std::vector<Battleship> ships;
    int sunk = 0;
};

#endif