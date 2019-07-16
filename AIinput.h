#ifndef AIINPUT_H
#define AIINPUT_H

#include "GameInput.h"

class Board;

class AIinput : public GameInput {
public:
    AIinput();
    AIinput(int n);
    virtual char input() const override;
    void assignBoard(Board* b);
private:
    Board* gameBoard;
    int iterationsPerMove;
    double getAverage(char move) const;
    long simGame(Board& board) const;
};

#endif
