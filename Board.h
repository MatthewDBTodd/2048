#ifndef BOARD_H
#define BOARD_H

#include "Tile.h"
#include <array>

class Board {
public:
    Board();
    int score() const { return curScore; }
    int turn() const { return turnNum; }
    bool moveBoard(const char c);
    void placeRandomTile();
    bool isGameOver();
    int operator[](const std::size_t i) const;
    int numEmptyTiles() { return _numEmptyTiles; }
    int placeTileEmptyPos(int pos, int value);
    void placeTile(int pos, int value);
private:
    std::array<Tile, 16> board;
    int curScore;
    int turnNum;
    int _numEmptyTiles;
    template <typename Move>
    bool move(Move& move);
    template <typename Move>
    void merge(Move& move, int i);
    template <typename Move>
    void swap(Move& move, int i);
};

#endif