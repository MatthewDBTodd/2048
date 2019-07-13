#include "Game.h"
#include "AIinput.h"
#include "mainMenu.h"

int main(int argc, char *argv[]) {
    initM();
    int ch {getChoice()};
    switch (ch) {
        case 0: {
            Game g;
            g.start();
        }
        default: {
            int strength {getAIStrength()};
            Game g(new AIinput(strength));
            g.start();
        }
    }
}
