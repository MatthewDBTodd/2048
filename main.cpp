#include "Game.h"
#include "AIinput.h"
#include "mainMenu.h"
#include "Expectimax.h"

/* 
#include <iostream>
#include <iomanip>
#include "Board64.h"
*/

int main(int argc, char *argv[]) {
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
    //Game g(new DebugDisplay(), new Expectimax());
    //Game g(new TerminalDisplay(), new Expectimax());
    //g.start();
}
