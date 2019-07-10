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
    std::vector<Tile*> emptyTiles;
    int curScore;
    int turnNum;
    template <typename T>
    bool move(T move);
    void markAsEmpty(Tile* t);
    void markAsOccupied(Tile* t);
};

#endif