#include <iostream>
#include "Game.h"
#include "randomNum.h"

int main() {
    //Game g;
    Game g(new AIinput);
    g.start();
}