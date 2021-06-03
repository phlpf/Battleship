#include <ShipManager.h>
#include <Battleship.h>
#include <Solver.h>
#include <iostream>
#include <cctype>

void placeBattleship(ShipManager& player, int size, std::string name){
    std::cout << "place " << name << ":" << std::endl;
    int x = 0, y = 0;
    std::string answer = ""; 
    bool isVertical;
    std::cout << "x (0-7): ";
    std::cin >> x;
    std::cout << "y (0-7): ";
    std::cin >> y;
    std::cout << "is vertical [y/N]: ";
    std::cin >> answer;
    isVertical = std::tolower(answer[0]) == 'y';
    if(!player.addShip(x, y, size, isVertical)){
        std::cout << "invalid!" << std::endl;
        placeBattleship(player, size, name);
    }
}

int main(){
    ShipManager player(8, 8), opponent(8, 8), known(8, 8);
    Solver ai(8, 8);
    opponent.randomBoard();
    /*placeBattleship(player, 2, "Destroyer");
    player.displayBoard();
    placeBattleship(player, 3, "Cruiser");
    player.displayBoard();
    placeBattleship(player, 3, "Submarine");
    player.displayBoard();
    placeBattleship(player, 4, "Battleship");
    player.displayBoard();
    placeBattleship(player, 5, "Carrier");
    player.displayBoard();*/
    player.randomBoard();
    int lastx = 0, lasty = 0, dir = 0, misscount = 0, inarow = 0;
    bool tracking = true;
    while(true){
        std::cout << "Target: " << std::endl;
        int x = 0, y = 0;
        std::cout << "x (0-7): ";
        std::cin >> x;
        std::cout << "y (0-7): ";
        std::cin >> y;
        Success hit = opponent.checkHit(x, y);
        if(hit == HIT){
            std::cout << "Hit!" << std::endl;
            known.setTile(x,y,2);
        } else if(hit == MISS){
            std::cout << "Miss" << std::endl;
            known.setTile(x,y,4);
        } else if(hit == SUNK){
            std::cout << "Sunk!!" << std::endl;
            known.setTile(x,y,3);
        } else if(hit == LOSE){    
            std::cout << "Sunk!!\nYou Win!" << std::endl;
            break;
        }

        ai.getMove(&x, &y);
        std::cout << "Attacked at: " << x << ", " << y << std::endl;
        hit = player.checkHit(x, y);
        if(hit == HIT){
            std::cout << "Hit" << std::endl;
        } else if(hit == MISS){
            std::cout << "Miss" << std::endl;
        } else if(hit == SUNK){
            std::cout << "Sunk" << std::endl;
        } else if(hit == LOSE){    
            std::cout << "Sunk\nYou Lose." << std::endl;
            break;
        }
        ai.applyResult(x, y, hit);
        ai.print();

        std::cout << "your board:" << std::endl;
        player.displayBoard();
        std::cout << "hit pieces:" << std::endl;
        known.displayBoard();
    }    
}

