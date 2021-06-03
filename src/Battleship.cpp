#include <Battleship.h>

Battleship::Battleship(int x, int y, int size, bool isVertical){
    this->x = x;
    this->y = y;
    this->size = size;
    this->isVertical = isVertical;
    for(int i = 0; i < size; i ++){
        if(isVertical){
            spaces.push_back(y+i);
        } else {
            spaces.push_back(x+i);
        }
    }
}

Success Battleship::checkHit(int x, int y, bool sinking){
    Success succ = MISS;
    for(int i = 0; i < size-hit; i++){
        int checkx = (this->isVertical?this->x:spaces[i]);
        int checky = (this->isVertical?spaces[i]:this->y);
        if(x == checkx && y == checky){
            succ = HIT;
            if(sinking){
                hit += 1;
                spaces.erase(spaces.begin()+i);
            }
            break;
        }
    }
    if(hit == size && succ == HIT){
        return SUNK;
    } 
    return succ;
}