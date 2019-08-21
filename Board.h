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
    uint64_t rotateBoard(uint64_t board) const;
    int getMask(const uint16_t row, const int pos) const;
};

#endif