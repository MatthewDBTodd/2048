#include <iostream>
#include <memory>
#include <ncurses.h>
#include "Game.h"

Game::Game() : score {0}, numTurns {0}, display {new TerminalDisplay}, input {new PlayerInput} {}

Game::Game(Display* dd) : score {0}, numTurns {0}, display {dd}, input {new PlayerInput} {}

Game::Game(GameInput* gi) : score {0}, numTurns {0}, display {new TerminalDisplay}, input {gi} {}

Game::Game(Display* dd, GameInput* gi) : score {0}, numTurns {0}, display {dd}, input {gi} {}

void Game::start() {
    board.placeRandomTile();
    board.placeRandomTile();
    display->draw(board);
    while (true) {
        char ch {input->input()};
        std::shared_ptr<Mover> m {factory.get(ch)};
        if (m->moveBoard(board)) {
            board.placeRandomTile();
        }
        board.resetTileStatus();
        display->draw(board);
        if (board.isGameOver()) {
            initscr();
            cbreak();
            keypad(stdscr, TRUE);
            noecho();
            scrollok(stdscr, TRUE);
            printw("Game Over\nPress F1 to quit\n");
            while (true) {
                int ch {getch()};
                if (ch == KEY_F(1)) break;
            }
            endwin();
            break;
        }
    }
}