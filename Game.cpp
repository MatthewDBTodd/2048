#include "Game.h"
#include "Display.h"
#include "GameInput.h"

Game::Game() : display {new TerminalDisplay}, input {new PlayerInput} {}

Game::Game(Display* dd) : display {dd}, input {new PlayerInput} {}

Game::Game(GameInput* gi) : display {new TerminalDisplay}, input {gi} {}

Game::Game(Display* dd, GameInput* gi) : display {dd}, input {gi} {}

void Game::start() {
    board.placeRandomTile();
    board.placeRandomTile();
    display->draw(board);
    while (true) {
        char ch {input->input()};
        if (board.moveBoard(ch)) {
            board.placeRandomTile();
        }
        board.unlockTiles();
        display->draw(board);
        if (board.isGameOver()) {
            display->gameOver(board);
            break;
        }
    }
}