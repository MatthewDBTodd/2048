#include <ncurses.h>
#include "mainMenu.h"

void initMenu() {
    initscr();
    cbreak();
    keypad(stdscr, TRUE);
    noecho();
}

void displayMenu(int highlightedCh) {
    start_color();
    init_pair(2, COLOR_GREEN, COLOR_BLACK);
    attron(COLOR_PAIR(2));
    mvprintw(3, 6, "2048");
    mvprintw(5, 6, "Select choice with the arrow keys and press enter");
    attroff(COLOR_PAIR(2));
    init_pair(1, COLOR_BLACK, COLOR_WHITE); 
    if (highlightedCh == 0) {
        attron(COLOR_PAIR(1));
    }
    mvprintw(7, 6, "Watch the AI play");
    attroff(COLOR_PAIR(1));
    if (highlightedCh == 1) {
        attron(COLOR_PAIR(1));
    }
    mvprintw(9, 6, "Play game");
    attroff(COLOR_PAIR(1));
}

int getChoice() {
    int highlightedText {0};
    displayMenu(highlightedText);
    while (true) {
        int ch {getch()};
        switch (ch) {
            case KEY_UP: 
            case KEY_DOWN: {
                ++highlightedText;
                highlightedText = highlightedText % 2;
                displayMenu(highlightedText);
                break;
            } 
            case 10:
            case KEY_ENTER: {
                erase();
                return highlightedText;
            }
        }
    }
}

int getAIStrength() {
    int choice {1000};
    do {
        printText();
        char c {};
        if ((scanw("%d%c", &choice, &c) == 1) && choice >= 100 && choice <= 20000) {
            break;
        }
    } while (true);
    erase();
    return choice;
}

void printText() {
    echo();
    erase();
    mvprintw(3, 6, "Enter the AI strength between 100 and 20000: ");
    mvprintw(5, 6, "The number entered is the number of game simulations the AI will run for each of the 4 moves per turn");
    mvprintw(7, 6, "100 will get the 2048 tile ~83%% of the time, and the 4096 tile ~7%% of the time");
    mvprintw(9, 6, "500 will get the 2048 tile ~96%% of the time, and the 4096 tile ~45%% of the time");
    mvprintw(11, 6, "1000 will get the 2048 tile ~97%% of the time, and the 4096 tile ~51%% of the time");
    mvprintw(13, 6, "Anything above 1000 gets quickly diminishing returns, though you will still see small improvements, but at the cost of slower move times");
    move(3, 51);
}