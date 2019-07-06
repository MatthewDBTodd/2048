#ifndef GAME_H
#define GAME_H

#include <memory>
#include "Tile.h"
#include "Board.h"
#include "MoveFactory.h"
#include "Mover.h"
#include "Display.h"
#include "GameInput.h"

using ptr_d = std::unique_ptr<Display>;
using ptr_i = std::unique_ptr<GameInput>;

class Game {
private:
    int score;
    int numTurns;
    Board board;
    MoveFactory factory;
    ptr_d display;
    ptr_i input;
public:
    Game();
    Game(Display* dd);
    Game(GameInput* gi);
    Game(Display* dd, GameInput* gi);
    void start();
};

#endif