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
    Game() : score {0}, numTurns {0}, display {new TerminalDisplay}, input {new PlayerInput} {}
    Game(Display* dd) : score {0}, numTurns {0}, display {dd}, input {new PlayerInput} {}
    Game(GameInput* gi) : score {0}, numTurns {0}, display {new TerminalDisplay}, input {gi} {}
    Game(Display* dd, GameInput* gi) : score {0}, numTurns {0}, display {dd}, input {gi} {}
    //void setDisplay(Display* dd);
    //void setInput(GameInput* gi);
    void start();
};

#endif