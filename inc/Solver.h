#ifndef SOLVER_H
#define SOLVER_H
#include <ShipManager.h>
#include <vector>

class Solver{
    public:
    Solver(int sizex, int sizey);
    void getMove(int* xp, int* yp);
    void applyResult(int x, int y, Success s);
    void setAround(int x, int y, int value, bool add);
    void print();
    private:
    void getRandomMove(int* xp, int* yp);
    int sizex, sizey;
    std::vector<std::vector<int> > chance;
};

#endif