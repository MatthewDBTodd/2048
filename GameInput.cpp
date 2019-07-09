#include <iostream>
#include <ncurses.h>
#include <random>
#include "GameInput.h"
#include "randomNum.h"

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
    n = getRandomNum(n);
    switch (n) {
        case 0: return 'u'; break;
        case 1: return 'r'; break;
        case 2: return 'd'; break;
        case 3: return 'l'; break;
        default: return 'd'; break;
    }
}
/* 
AIinput::AIinput() : gameBoard {nullptr} {}

void AIinput::assignBoard(Board* b) {
    gameBoard = b;
}
*/