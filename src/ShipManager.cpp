#include <ShipManager.h>
ShipManager::ShipManager(int size_x, int size_y){
    srand(time(NULL));
    this->size_x = size_x;
    this->size_y = size_y;
    for(int i = 0; i < size_y; i++){
        std::vector<int> col;
        for(int j = 0; j < size_x; j++){
            col.push_back(0);
        }
        board.push_back(col);
    } 
}
Success ShipManager::checkHit(int x, int y){
    if(x >= size_x || x < 0 || y >= size_y || y < 0 ){
        return MISS;
    }
    for(int i = 0; i < ships.size(); i++){
        Success hit = ships[i].checkHit(x, y, true);
        if(hit == HIT){
            board[y][x] = 2;
            return hit;
        } else if (hit == SUNK){
            board[y][x] = 3;
            sunk += 1;
            if(sunk == ships.size()){
                return LOSE;
            }
            return hit;
        }
    }
    return MISS;
}
void ShipManager::displayBoard(){
    for(int i = 0; i < size_x; i++){
        for(int j = 0; j < size_y; j++){
            switch(board[i][j]){
                case 0:
                    std::cout << "- ";
                    break;
                case 1:
                    std::cout << "O ";
                    break;
                case 2:
                    std::cout << "X ";
                    break;
                case 3:
                    std::cout << "S ";
                    break;
                case 4:
                    std::cout << "M ";
                    break;
            }
        }
        std::cout << std::endl;
    }
}

int ShipManager::getTile(int x, int y){
    return board[y][x];
}

void ShipManager::setTile(int x, int y, int i){
    if(x >= size_x || x < 0 || y >= size_y || y < 0 ){
        return;
    }
    board[y][x] = i;
}

bool ShipManager::addShip(int x, int y, int size, bool isVertical){
    int totalx = (isVertical?x+1:x+size), totaly = (isVertical?y+size:y+1);
    if(totalx > size_x || totaly > size_y){
        return false;
    }
    for(int i = 0; i < ships.size(); i++){
        for(int j = 0; j < size; j++){
            int checkx = (isVertical?x:x+j);
            int checky = (isVertical?y+j:y);
            if(ships[i].checkHit(checkx, checky, false) == HIT){
                return false;
            }
        }
    }

    // everythings good, push back ship
    Battleship bs(x, y, size, isVertical);
    ships.push_back(bs);
    for(int i = 0; i < size; i++){
        int checkx = (isVertical?x:x+i);
        int checky = (isVertical?y+i:y);
        board[checky][checkx] = 1;
    }

    return true;
}

void ShipManager::addRandomPiece(int size){
    int x = rand()%(size_x-size+1), y = rand()%(size_y-size+1);
    if(!addShip(x, y, size, (rand()%2))){
        addRandomPiece(size);
    }
}

void ShipManager::randomBoard(){
    addRandomPiece(2);   
    addRandomPiece(3);   
    addRandomPiece(3);   
    addRandomPiece(4);   
    addRandomPiece(5);
}