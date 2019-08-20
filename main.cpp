/* 
#include "Game.h"
#include "AIinput.h"
#include "mainMenu.h"
#include "Expectimax.h"
*/

#include <iostream>
#include <iomanip>
#include "Board64.h"

int main(int argc, char *argv[]) {
    populateTables();
    uint64_t board {0};
    int score {0};
    placeRandomTile(board);
    placeRandomTile(board);
    std::cout << std::setfill('0') << std::setw(16) << std::hex << board << std::dec << '\n';
    printBoard(board);
    std::cout << "Moving right\n";
    board = moveBoard(board, 'r', score);
    printBoard(board);
    std::cout << "Placing random tile\n";
    placeRandomTile(board);
    printBoard(board);
    std::cout << "Moving left\n";
    board = moveBoard(board, 'l', score);
    printBoard(board);
    std::cout << "Placing random tile\n";
    placeRandomTile(board);
    printBoard(board);
    std::cout << "Moving up\n";
    board = moveBoard(board, 'u', score);
    printBoard(board);
    std::cout << "Placing random tile\n";
    placeRandomTile(board);
    printBoard(board);
    std::cout << "Moving down\n";
    board = moveBoard(board, 'd', score);
    printBoard(board);
    std::cout << "Placing random tile\n";
    placeRandomTile(board);
    printBoard(board);

    /* 
    populateTables();
    uint64_t board {0};
    int score {0};
    placeRandomTile(board);
    placeRandomTile(board);
    printBoard(board);
    board = moveBoard(board, 'r', score);
    printBoard(board);
    */
    /* 
    Game g(new DebugDisplay(), new Expectimax());
    Game g(new TerminalDisplay(), new Expectimax());
    g.start();
    initMenu();
    int ch {getChoice()};
    switch (ch) {
        case 0: {
            int strength {getAIStrength()};
            Game g(new AIinput(strength));
            g.start();
            break;
        }
        default: {
            Game g;
            g.start();
            break;
        }
    }
    return 0;
    */
}
