#ifndef GAME_H
#define GAME_H

#include <memory>
#include "Board.h"
#include "Display.h"
#include "GameInput.h"

using ptr_d = std::unique_ptr<Display>;
using ptr_i = std::unique_ptr<GameInput>;


class Game {
public:
    Game();
    Game(Display* dd);
    Game(GameInput* gi);
    Game(Display* dd, GameInput* gi);
    void start();
private:
    Board board;
    ptr_d display;
    ptr_i input;
};

#endif