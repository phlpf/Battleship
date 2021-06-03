#ifndef BATTLESHIP_H
#define BATTLESHIP_H
#include <vector>
typedef enum {
    MISS = 0, HIT, SUNK, LOSE
} Success;

class Battleship{
    public:
    Battleship(int x, int y, int size, bool isVertical);
    Success checkHit(int x, int y, bool sinking);
    private:
    int x, y, size;
    bool isVertical;
    int hit = 0;
    std::vector<int> spaces;
};

#endif