#include <ncurses.h>
#include "Game.h"

int main(int argc, char *argv[]) {
    initscr();
    cbreak();
    keypad(stdscr, TRUE);
    noecho();
    if (argc == 2) {
        try {
            int i {std::stoi(argv[1])};
            Game g(new AIinput(i)); 
            g.start();
            return 0;
        } catch (std::exception) {}
    }
    move(10, 10);
    printw("No argument / Invalid argument provided"); 
    move (12, 10);
    printw("Defaulting to AI strength 500. Press a key to continue");
    getch();
    endwin();
    Game g(new AIinput);
    g.start();
    return 0;
}