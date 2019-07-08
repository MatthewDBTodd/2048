#include <ncurses.h>
#include <cmath>
#include "Board.h"
#include "Display.h"

#define RED 1
#define YELLOW 2
#define GREEN 3
#define BLUE 4
#define MAGENTA 5
#define CYAN 6

const char* setWidth(int val);
void init();
void initColours();
void printVerticalPadding(int tileWidth, int rows);

void TerminalDisplay::draw(const Board& b, const int score, const int turns) const {
    init();
    printw("      Score: %i    Turn: %i", score, turns);
    move(3, horizontalMargin);
    int x, y;
    for (int i {0}; i < b.size(); ++i) {
        if (i != 0 && i % 4 == 0) {
            getyx(stdscr, y, x);
            move(y+tileHeight, horizontalMargin);
        }
        if( b[i].value() == 0) {
            std::string val {"-"};
            displayTile(setWidth(val));
            continue;
        }
        int log {static_cast<int>(log2(b[i].value()))};
        int colorVal {(log % numColours) + 1};
        std::string val {setWidth(std::to_string(b[i].value()))};
        attron(COLOR_PAIR(colorVal));
        displayTile(val);
        attroff(COLOR_PAIR(colorVal));
    }
    getyx(stdscr, y, x);
    move(y+(tileHeight+2), horizontalMargin);
    refresh();
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

void TerminalDisplay::displayTile(std::string val) const {
    int y, x;
    printVerticalPadding(tileWidth, ((tileHeight-1)/2));
    printw("%s", val.c_str());
    getyx(stdscr, y, x);
    move(y+1, x-tileWidth);
    printVerticalPadding(tileWidth, ((tileHeight-1)/2));
    getyx(stdscr, y, x);
    move(y-tileHeight, x+tileWidth);
}

void initColours() {
    init_pair(YELLOW, COLOR_BLACK, COLOR_YELLOW);
    init_pair(GREEN, COLOR_BLACK, COLOR_GREEN);
    init_pair(BLUE, COLOR_WHITE, COLOR_BLUE);
    init_pair(MAGENTA, COLOR_WHITE, COLOR_MAGENTA);
    init_pair(CYAN, COLOR_BLACK, COLOR_CYAN);
    init_pair(RED, COLOR_WHITE, COLOR_RED);
}

void init() {
    initscr();
    scrollok(stdscr, TRUE);
    start_color();
    initColours();
}

void printVerticalPadding(int tileWidth, int rows) {
    for (int i {0}; i < rows; ++i) {
        for (int j {0}; j < tileWidth; ++j) {
            addch(' ');
        }
        int y, x;
        getyx(stdscr, y, x);
        move(y+1, x-tileWidth);
    }
}