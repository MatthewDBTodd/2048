#ifndef GAME_H
#define GAME_H

#include <memory>
#include "Board.h"
#include "MoveFactory.h"
#include "Mover.h"
#include "Display.h"
#include "GameInput.h"
#include "MergeListener.h"

using ptr_d = std::unique_ptr<Display>;
using ptr_i = std::unique_ptr<GameInput>;

class Game : public MergeListener {
private:
    int score;
    int numTurns;
    Board board;
    MoveFactory factory;
    ptr_d display;
    ptr_i input;
    void end();
public:
    Game();
    Game(Display* dd);
    Game(GameInput* gi);
    Game(Display* dd, GameInput* gi);
    void start();
    virtual void notify(const int value) override;
};

#endif