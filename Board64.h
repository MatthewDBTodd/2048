#ifndef BOARD64_H
#define BOARD64_H

#include <cstdint>

extern uint16_t forwardTable[65536];
extern uint16_t reverseTable[65536]; 
extern int scoreTable[65536];
extern uint8_t zeroTable[65536];
extern uint16_t resetMasks[4];

void populateTables();
uint64_t rotateBoard(const uint64_t board);
void printBoard(uint64_t board);
void placeRandomTile(uint64_t& board);
int numEmptyTiles(uint64_t board);
uint64_t moveBoard(uint64_t board, char move, int& score);
bool isGameOver(uint64_t board);
int getMask(const uint16_t row, const int pos);

template <typename T>
uint16_t merge(uint16_t row, int bitNum, T& move);

template <typename T>
uint16_t swap(uint16_t row, int bitNum, int value, T& move);

template <typename T>
uint16_t generateRow(uint16_t row, T& move);
int generateScore(uint16_t row);
uint8_t generateNumZeroes(uint16_t row);
#endif