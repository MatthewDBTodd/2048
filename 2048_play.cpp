#include "Game.h"

int main(int argc, char *argv[]) {
    Game g(new PlayerInput);
    g.play();
    return 0;
}
