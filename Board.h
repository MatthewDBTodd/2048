#ifndef BOARD_H
#define BOARD_H

#include "Tile.h"
#include <vector>
#include <array>

class Board {
public:
    Board();
    Board(const Board& b);
    Board& operator=(const Board& b);
    int score() const { return curScore; }
    int turn() const { return turnNum; }
    bool moveBoard(const char c);
    void placeRandomTile();
    void unlockTiles();
    bool isGameOver();
    int operator[](const std::size_t i) const;
private:
    std::array<Tile, 16> board;
    int curScore;
    int turnNum;
    int numEmptyTiles;
    template <typename T>
    bool move(const T& move);
};

#endif