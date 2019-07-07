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
    for (int i {0}; i < b.size(); ++i) {
        if (i != 0 && i % 4 == 0) {
            int y, x;
            getyx(stdscr, y, x);
            move(y+4, 0);
        }
        if( b[i].value() == 0) {
            int x, y;
            printw("            ");
            getyx(stdscr, y, x);
            move(y+1, x-12);
            printw("     -      ");
            getyx(stdscr, y, x);
            move(y+1, x-12);
            printw("            ");
            getyx(stdscr, y, x);
            move(y-2, x);
            continue;
        }
        start_color();
        init_pair(YELLOW, COLOR_BLACK, COLOR_YELLOW);
        init_pair(GREEN, COLOR_BLACK, COLOR_GREEN);
        init_pair(BLUE, COLOR_WHITE, COLOR_BLUE);
        init_pair(MAGENTA, COLOR_WHITE, COLOR_MAGENTA);
        init_pair(CYAN, COLOR_BLACK, COLOR_CYAN);
        init_pair(RED, COLOR_WHITE, COLOR_RED);
        int logged {static_cast<int>(log2(b[i].value()))};
        int colorVal {(logged % 6) + 1};
        attron(COLOR_PAIR(colorVal));
        printw("           ");
        attroff(COLOR_PAIR(colorVal));
        printw(" ");
        int y, x;
        getyx(stdscr, y, x);
        move(y+1, x-12);
        attron(COLOR_PAIR(colorVal));
        printw("%s", setWidth(b[i].value()));
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
    int y, x;
    getyx(stdscr, y, x);
    move(y+4, 0);
    refresh();
}

const char* setWidth(int val) {
    constexpr int strLength {11};
    std::string str {std::to_string(val)};
    std::size_t numLength {str.length()};
    str = "";
    std::size_t i {0};
    for (; i < ((strLength - numLength)/2); ++i) {
        str.push_back(' ');
    }
    str += std::to_string(val);
    for (i = str.length(); i < strLength; ++i) {
        str.push_back(' ');
    }
    return str.c_str();
}