#include <ncurses.h>
#include <map>
#include <algorithm>
#include "GameInput.h"
#include "randomNum.h"
#include "Board.h"

char PlayerInput::input() const {
    initscr();
    cbreak();
    keypad(stdscr, TRUE);
    noecho();
    scrollok(stdscr, TRUE);
    printw("Enter move: ");
    while (true) {
        refresh();
        int ch {getch()};
        switch (ch) {
            case KEY_LEFT: clear(); refresh(); return 'l'; break;
            case KEY_RIGHT: clear(); refresh(); return 'r'; break;
            case KEY_UP: clear(); refresh(); return 'u'; break;
            case KEY_DOWN: clear(); refresh(); return 'd'; break;
            default: break;
        }
    }
}

char RandomInput::input() const {
    std::size_t n {4};
    n = randomNum::getRandomNum(n);
    switch (n) {
        case 0: return 'u'; break;
        case 1: return 'r'; break;
        case 2: return 'd'; break;
        case 3: return 'l'; break;
        default: return 'd'; break;
    }
}
AIinput::AIinput() : gameBoard {nullptr}, iterationsPerMove {500.0} {}

void AIinput::assignBoard(Board* b) {
    gameBoard = b;
}

char AIinput::input() const {
    std::map<char, double> moveAverages {{'u', 0.0}, {'d', 0.0}, {'r', 0.0}, {'l', 0.0}};
    for (auto& move : moveAverages) {
        move.second = getAverage(move.first);
    }
    auto maxVal {std::max_element(
        moveAverages.begin(), moveAverages.end(),
        [] (const std::pair<char, double>& p1, const std::pair<char, double>& p2) {
            return p1.second < p2.second;
        }
    )};
    return maxVal->first;
}

double AIinput::getAverage(char move) const {
    double scoreTally {0};
    for (int i {0}; i < iterationsPerMove; ++i) {
        Board boardCopy {*gameBoard};
        if (boardCopy.moveBoard(move)) {
            boardCopy.placeRandomTile();
            scoreTally += simGame(boardCopy);
        } else {
            return boardCopy.score();
        }
    }
    return scoreTally / iterationsPerMove;
}

long AIinput::simGame(Board& board) const {
    while (true) {
        int rand {randomNum::getRandomNum(3)};
        char m;
        switch (rand) {
            case 0: m = 'u'; break;
            case 1: m = 'd'; break;
            case 2: m = 'l'; break;
            case 3: m = 'r'; break;
            default: throw "Random number in simGame not in correct range\n";
        }
        if (board.moveBoard(m)) {
            board.placeRandomTile();
        }
        if (board.isGameOver()) {
            return board.score();
        }
        board.unlockTiles();
    }
}