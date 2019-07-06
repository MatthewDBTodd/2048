#include <iostream>
#include <memory>
#include "Game.h"

/* 
void Game::setDisplay(Display* dd) {
    display = dd;
}
*/

/* 
void Game::setInput(GameInput* gi) {
    input = gi;
}
*/

void Game::start() {
    board.placeRandomTile();
    board.placeRandomTile();
    
    // print board here
    display->draw(board);

    while (true) {
        char ch {input->input()};
        std::shared_ptr<Mover> m {factory.get(ch)};
        if (m->moveBoard(board)) {
            board.placeRandomTile();
        }
        board.resetTileStatus();

        // print board here
        display->draw(board);

        if (board.isGameOver()) {
            std::cout << "Game over\n";
            break;
        }
    }
}