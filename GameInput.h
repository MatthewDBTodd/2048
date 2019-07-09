#ifndef GAMEINPUT_H
#define GAMEINPUT_H

class Board;

class GameInput {
public:
    virtual char input() const = 0;
};

class PlayerInput : public GameInput {
public:
    virtual char input() const override;
};

// Mainly useful for testing end game conditions
class RandomInput : public GameInput {
public:
        virtual char input() const override;
};

/* 
class AIinput : public GameInput {
public:
    AIinput();
    virtual char input() const override;
    void assignBoard(Board* b);
private:
    Board* gameBoard;
};
*/

#endif