#include <Solver.h>

Solver::Solver(int sizex, int sizey){
    this->sizex = sizex;
    this->sizey = sizey;
    for(int i = 0; i < sizex; i++){
        std::vector<int> col;
        for(int j = 0; j < sizey; j++){
            col.push_back(0);
        }
        chance.push_back(col);
    }
}

void Solver::getMove(int* xp, int* yp){
    int x = 0, y = 0;
    int maxChance = 0;
    for(int i = 0; i < sizex; i++){
        for(int j = 0; j < sizey; j++){
            if(chance[j][i] > maxChance){
                maxChance = chance[j][i];
                x = i;
                y = j;
            } else if(chance[j][i] == maxChance){
                if(rand()%3 == 0){
                    x = i;
                    y = j;
                }                
            }
        }
    } 
    if(maxChance==0){
        getRandomMove(&x,&y);
    }
    (*xp) = x;
    (*yp) = y;
}

void Solver::getRandomMove(int* xp, int* yp){
    (*xp) = rand()%sizex;
    (*yp) = rand()%sizey;
    if(chance[*yp][*xp] < 0){
        getRandomMove(xp, yp);
    }
}

void Solver::applyResult(int x, int y, Success s){
    chance[y][x] = -1;
    switch(s){
        case HIT:
            setAround(x, y, 1, true);
        break;
        case SUNK:
            setAround(x, y, 0, false);
        break;
        default:
        break;
    }
}

void Solver::setAround(int x, int y, int value, bool add){
    for(int i = -1; i < 2; i++){
        if(!(y+i>=sizey)){
            if(chance[y+i][x] >= 0){
                if(!add)
                    chance[y+i][x] = value;
                else
                    chance[y+i][x] += value;
            }
        }
        if(!(x+i>=sizex)){
            if(chance[y][x+i] >= 0){
                if(!add)
                    chance[y][x+i] = value;
                else
                    chance[y][x+i] += value;
            }
        }
    }
}
void Solver::print(){
    
    for(int i = 0; i < sizex; i++){
        for(int j = 0; j < sizey; j++){
            std::cout << chance[j][i] << " ";
        }
        std::cout << std::endl;
    }
}