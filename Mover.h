#ifndef MOVER_H
#define MOVER_H

#include "Board.h"

class Mover {
public:
    virtual bool moveBoard(Board& b) const = 0;
};

class Right : public Mover {
public:
    virtual bool moveBoard(Board& b) const override;
};

class Left : public Mover {
public:
    virtual bool moveBoard(Board& b) const override;
};

class Up : public Mover {
public:
    virtual bool moveBoard(Board& b) const override;
};

class Down : public Mover {
public:
    virtual bool moveBoard(Board& b) const override;
};

#endif