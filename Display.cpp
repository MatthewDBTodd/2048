#include <ncurses.h>
#include <sstream>
#include "Board.h"
#include "Display.h"

void TerminalDisplay::draw(const Board& b, const int score, const int turns) const {
    initscr();
    scrollok(stdscr, TRUE);
    printw("      Score: %i    Turn: %i\n\n", score, turns);
    std::ostringstream buffer;
    buffer << b;
    printw("%s", buffer.str().c_str());
    refresh();
}