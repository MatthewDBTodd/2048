#ifndef MOVER_H
#define MOVER_H

#include <vector>
#include "Tile.h"

class Mover {
public:
    virtual void moveBoard(std::vector<Tile>& board) = 0;
};

class Right : public Mover {
public:
    virtual void moveBoard(std::vector<Tile>& board) override;
};

class Left : public Mover {
public:
    virtual void moveBoard(std::vector<Tile>& board) override;
};

class Up : public Mover {
public:
    virtual void moveBoard(std::vector<Tile>& board) override;
};

class Down : public Mover {
public:
    virtual void moveBoard(std::vector<Tile>& board) override;
};

#endif