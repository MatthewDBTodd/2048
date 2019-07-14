#include <ncurses.h>
#include "mainMenu.h"

void initM() {
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
        if ((scanw("%d%c", &choice, &c) == 1) && choice >= 1 && choice <= 200) {
            break;
        }
    } while (true);
    erase();
    return (choice * 100);
}

void printText() {
    echo();
    erase();
    mvprintw(3, 6, "Enter the AI strength between 1 and 200: ");
    mvprintw(5, 6, "For reference, 1 is already pretty strong. It will get the 2048 tile most of the time, and move too quick to follow");
    mvprintw(7, 6, "Level 200 will move very slowly, but will generally perform better");
    mvprintw(9, 6, "Bear in mind though, that there's diminishing returns the higher you get, due to the luck aspect of the game");
    mvprintw(11, 6, "Level 20 seems to be a good middle ground between speed and strength");
    move(3, 47);
}