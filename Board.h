#ifndef BOARD_H
#define BOARD_H

#include "Tile.h"
#include "Score.h"
#include <array>

class Board {
public:
    Board();
    int score() const { return curScore; }
    int turn() const { return turnNum; }
    Score scoreInfo() const;
    bool moveBoard(const char c);
    void placeRandomTile();
    bool isGameOver();
    int operator[](const std::size_t i) const;
private:
    std::array<Tile, 16> board;
    int curScore;
    int turnNum;
    int numEmptyTiles;
    template <typename Move>
    bool move(Move& move);
    template <typename Move>
    void merge(Move& move, int i);
    template <typename Move>
    void swap(Move& move, int i);
};

#endif