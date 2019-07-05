#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include <ostream>
#include "Tile.h"
#include "Mover.h"

class Board {
private:
    std::vector<Tile> board;
public:
    Board() : board(16) {}
    friend std::ostream& operator<<(std::ostream& os, const Board& b);
    const Tile& operator[](const int i) const;
    Tile& operator[](const int i);
};

void move(std::vector<Tile>& board, const Mover& m);
#endif