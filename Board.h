#ifndef BOARD_H
#define BOARD_H

#include <cstdint>

class Board {
public:
    Board();
    void placeRandomTile();
    bool moveBoard(const char move);
    bool isGameOver();
    int score() const { return _score; }
    int operator[](const std::size_t i) const;
private:
    uint64_t board;
    int _score;
    // Lookup tables
    static uint16_t forwardTable[65536];
    static uint16_t reverseTable[65536]; 
    static int scoreTable[65536];
    static uint8_t zeroTable[65536];
    const static uint16_t resetMasks[4];

    void populateTables();
    template <typename T>
    uint16_t generateRow(uint16_t row, T& move) const;
    template <typename T>
    uint16_t merge(uint16_t row, int bitNum, T& move) const;
    template <typename T>
    uint16_t swap(uint16_t row, int bitNum, int value, T& move) const;
    int generateScore(uint16_t row) const;
    uint8_t generateNumZeroes(uint16_t row) const;
    int numEmptyTiles() const;
    uint64_t rotateBoard(const uint64_t board) const;
    int getMask(const uint16_t row, const int pos) const;
};

// old code

/* 
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
*/

#endif