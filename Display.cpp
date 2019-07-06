#include <ncurses.h>
#include <sstream>
#include "Board.h"
#include "Display.h"

void TerminalDisplay::draw(const Board& b) const {
    initscr();
    scrollok(stdscr, TRUE);
    std::ostringstream buffer;
    buffer << b;
    printw("%s", buffer.str().c_str());
    refresh();
}