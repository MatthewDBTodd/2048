#include <iostream>
#include <ncurses.h>
#include <random>
#include "GameInput.h"

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
    std::random_device d;
    std::mt19937 rng(d());
    std::uniform_int_distribution<std::mt19937::result_type> num(1, 4);
    std::size_t n {num(rng)};
    switch (n) {
        case 1: return 'u'; break;
        case 2: return 'r'; break;
        case 3: return 'd'; break;
        case 4: return 'l'; break;
        default: return 'd'; break;
    }
}