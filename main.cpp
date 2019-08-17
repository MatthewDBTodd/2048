#include "Game.h"
//#include "AIinput.h"
#include "mainMenu.h"
#include "Expectimax.h"

int main(int argc, char *argv[]) {
    //Game g(new DebugDisplay(), new Expectimax());
    Game g(new TerminalDisplay(), new Expectimax());
    g.start();
    /* 
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
    */
}
