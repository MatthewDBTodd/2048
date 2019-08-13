#include "Game.h"
#include "Display.h"
#include "GameInput.h"
#include "AIinput.h"

//Game::Game() : display {new TerminalDisplay}, input {new PlayerInput} {}

//Game::Game(Display* dd) : display {dd}, input {new PlayerInput} {}

Game::Game(GameInput* gi) : display {new TerminalDisplay}, input {gi} {
    // if input passed in is AI, need to assign it a pointer to the board
    AIinput* testPtr {dynamic_cast<AIinput*>(gi)};
    if (testPtr) {
        testPtr->assignBoard(&board);
    }
}

Game::Game(Display* dd, GameInput* gi) : display {dd}, input {gi} {
    // if input passed in is AI, need to assign it a pointer to the board
    AIinput* testPtr {dynamic_cast<AIinput*>(gi)};
    if (testPtr) {
        testPtr->assignBoard(&board);
    }
}

Score Game::play() {
    board.placeRandomTile();
    board.placeRandomTile();
    display->draw(board);
    while (true) {
        char ch {input->input()};
        if (board.moveBoard(ch)) {
            board.placeRandomTile();
        }
        display->draw(board);
        if (board.isGameOver()) {
            display->gameOver(board);
            return board.scoreInfo();
        }
    }
}