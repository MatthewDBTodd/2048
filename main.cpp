#include "Game.h"
#include "AIinput.h"
#include "mainMenu.h"

int main(int argc, char *argv[]) {
    initMenu();
    int ch {getChoice()};
    switch (ch) {
        case 0: {
            int strength {getAIStrength()};
            Game g(new AIinput(strength));
            g.start();
            break;
        }
        default: {
            Game g;
            g.start();
            break;
        }
    }
    return 0;
}
