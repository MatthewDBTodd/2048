#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include <ostream>
#include "Tile.h"

class Board {
private:
    int s;
    std::vector<Tile> board;
public:
    Board() : s {16}, board(s) {}
    int size() { return s; }
    bool isGameOver();
    friend std::ostream& operator<<(std::ostream& os, const Board& b);
    const Tile& operator[](const int i) const;
    Tile& operator[](const int i);
};
#endif