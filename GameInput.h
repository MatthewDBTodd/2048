#ifndef GAMEINPUT_H
#define GAMEINPUT_H

class GameInput {
public:
    virtual char input() const = 0;
};

class PlayerInput : public GameInput {
public:
    virtual char input() const override;
};

class RandomInput : public GameInput {
    public:
        virtual char input() const override;
};
/* 
class AIInput : public GameInput {
public:
    virtual char input() const override;
}
*/

#endif