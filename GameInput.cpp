#include <ncurses.h>
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