#include <ncurses.h>
#include <sstream>
#include "Board.h"
#include "Display.h"
#include <cstring>
#include <cmath>

#define RED 1
#define YELLOW 2
#define GREEN 3
#define BLUE 4
#define MAGENTA 5
#define CYAN 6

const char* setWidth(int val);

void TerminalDisplay::draw(const Board& b, const int score, const int turns) const {
    initscr();
    scrollok(stdscr, TRUE);
    printw("      Score: %i    Turn: %i\n\n", score, turns);
    int x, y;
    for (int i {0}; i < b.size(); ++i) {
        if (i != 0 && i % 4 == 0) {
            getyx(stdscr, y, x);
            move(y+4, 0);
        }
        if( b[i].value() == 0) {
            displayZeroTile();
            continue;
        }
        start_color();
        initColours();
        int logged {static_cast<int>(log2(b[i].value()))};
        int colorVal {(logged % 6) + 1};
        std::string o {setWidth(std::to_string(b[i].value()))};
        displayColourTile(colorVal, o);
    }
    getyx(stdscr, y, x);
    move(y+4, 0);
    refresh();
}

void TerminalDisplay::initColours() const {
    init_pair(YELLOW, COLOR_BLACK, COLOR_YELLOW);
    init_pair(GREEN, COLOR_BLACK, COLOR_GREEN);
    init_pair(BLUE, COLOR_WHITE, COLOR_BLUE);
    init_pair(MAGENTA, COLOR_WHITE, COLOR_MAGENTA);
    init_pair(CYAN, COLOR_BLACK, COLOR_CYAN);
    init_pair(RED, COLOR_WHITE, COLOR_RED);
}

std::string TerminalDisplay::setWidth(std::string val) const {
    std::size_t valLength {val.length()};
    std::string output {}; 
    std::size_t i {0};
    for (; i < ((tileWidth - valLength) / 2); ++i) {
        output.push_back(' ');
    }
    output += val;
    for (i = output.length(); i < tileWidth; ++i) {
        output.push_back(' ');
    }
    return output;
}

void TerminalDisplay::displayColourTile(int colorVal, std::string val) const {
    int y, x;
    attron(COLOR_PAIR(colorVal));
    printw("           ");
    attroff(COLOR_PAIR(colorVal));
    printw(" ");
    getyx(stdscr, y, x);
    move(y+1, x-12);
    attron(COLOR_PAIR(colorVal));
    printw("%s", val.c_str());
    attroff(COLOR_PAIR(colorVal));
    printw(" ");
    getyx(stdscr, y, x);
    move(y+1, x-12);
    attron(COLOR_PAIR(colorVal));
    printw("           ");
    attroff(COLOR_PAIR(colorVal));
    printw(" ");
    getyx(stdscr, y, x);
    move(y-2, x);
}

void TerminalDisplay::displayZeroTile() const {
    int y, x;
    printw("            ");
    getyx(stdscr, y, x);
    move(y+1, x-12);
    printw("     -      ");
    getyx(stdscr, y, x);
    move(y+1, x-12);
    printw("            ");
    getyx(stdscr, y, x);
    move(y-2, x);
}