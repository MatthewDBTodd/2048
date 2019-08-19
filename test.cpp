#include <iostream>
#include <cstdint>
#include <iomanip>
#include <array>
#include "randomNum.h"

using board = uint64_t;
uint64_t masks[16] {
0xFFFFFFFFFFFFFFF0, 
0xFFFFFFFFFFFFFF0F,
0xFFFFFFFFFFFFF0FF, 
0xFFFFFFFFFFFF0FFF,
0xFFFFFFFFFFF0FFFF,
0xFFFFFFFFFF0FFFFF,
0xFFFFFFFFF0FFFFFF,
0xFFFFFFFF0FFFFFFF,
0xFFFFFFF0FFFFFFFF,
0xFFFFFF0FFFFFFFFF,
0xFFFFF0FFFFFFFFFF,
0xFFFF0FFFFFFFFFFF,
0xFFF0FFFFFFFFFFFF,
0xFF0FFFFFFFFFFFFF,
0xF0FFFFFFFFFFFFFF,
0x0FFFFFFFFFFFFFFF};

void printHexBoard(const board mask) {
    std::cout << "Hex shift board\n";
    for (int i {0}; i < 16; ++i) {
        if (i > 0 && i % 4 == 0) {
            std::cout << "\n\n";
        }
        uint64_t val {(mask & ~masks[i]) >> (i*4)};
        std::cout << std::hex << val << "  ";
    }
    std::cout << "\n---------------------------\n";
}

void printBoard(board mask) {
    for (int i {0}; i < 16; ++i) {
        if (i > 0 && i % 4 == 0) {
            std::cout << "\n\n";
        }
        uint64_t val {1ull << (0xF & (mask >> (i*4)))};
        val = (val == 1) ? 0 : val;
        std::cout << val << "  ";
    }
    std::cout << "\n--------------------------\n";
}

int numEmptyTiles(board mask) {
    int count {};
    for (int i {0}; i < 16; ++i) {
        if ((1ull << (0xF & (mask >> (i*4))))-1 == 0) {
            ++count;
        }
    }
    return count;
}

void placeRandomTile(uint64_t& mask) {
    int emptyTiles {numEmptyTiles(mask)}; 
    int index {randomNum::getRandomNum(emptyTiles-1)};
    int val {randomNum::getRandomNum(9)};
    val = (val == 9) ? 4 : 2;
    int count {0};
    for (int i {0}; i < 16; ++i) {
        if ((1ull << (0xF & (mask >> (i*4))))-1 != 0) {
            continue;
        }
        if (count++ == index) {
            board valMask {(val == 2) ? 1ull : 2ull};
            mask |= (valMask << (i*4));
            break;
        }
    }
}

int getVal(board mask, int pos) {
    int n {((1ull << (0xF & (mask >> (pos*4)))))};
    n = (n == 1) ? 0 : n;
    return n;
}


void zeroTile(board& mask, int pos) {
    mask &= masks[pos];
}

void swapTiles(board& mask, int prev, int dest) {
    // single out the mask of the prev tile
    uint64_t newMask {mask & ~masks[prev]};
    // shift it to the right or left to get it in the same pos as the dest tile
    if (dest > prev) {
        newMask <<= (dest-prev)*4;
    } else {
        newMask >>= (prev-dest)*4;
    }
    // or the mask with the new mask to set the dest tile
    mask |= newMask;
    // zero the prev tile
    zeroTile(mask, prev);
}

void mergeTile(board& mask, int pos) {
    uint64_t n {0xF & (mask >> (pos*4))};
    n++;
    // zero tile
    mask &= masks[pos];
    // set to new value
    mask |= (n << (pos*4));
}

void rotateBoard(board& mask) {
    std::array<std::array<int, 4>, 4> b {};
    for (int i {0}; i < 4; ++i) {
        for (int j {0}; j < 4; ++j) {
            int index {(i*4) + j};
            int val {getVal(mask, index)};
            b[i][j] = val;
        }
    }
}

bool moveBoard(board& mask, const char move) {
    bool hasMoved {false};
    signed char nextFreeSlot {-1};
    signed char previousTileIndex {-1};
    int previousTileValue {-1};
    for (int i {15}; i >= 0; --i) {
        if (getVal(mask, i) == 0) {
            nextFreeSlot = (nextFreeSlot == -1) ? i : nextFreeSlot;
        } else if (getVal(mask, i) == previousTileValue) {
            hasMoved = true;
            mergeTile(mask, previousTileIndex); 
            zeroTile(mask, i);
            nextFreeSlot = i;
            previousTileValue = -1;
            previousTileIndex = -1;
        } else {
            previousTileValue = getVal(mask, i);
            previousTileIndex = i;
            if (nextFreeSlot != -1) {
                hasMoved = true;
                swapTiles(mask, i, nextFreeSlot); 
                previousTileIndex = nextFreeSlot;
                --nextFreeSlot;
            }
        }
        if (i % 4 == 0) {
            nextFreeSlot = -1;
            previousTileIndex = -1;
            previousTileValue = -1;
        }
    }
    return hasMoved;
}


int main() {
    uint64_t mask {0x0};
    printBoard(mask);
    std::cout << '\n' << numEmptyTiles(mask) << " empty tiles\n";
    std::cout << "----------------\n";
    placeRandomTile(mask);
    placeRandomTile(mask);
    printBoard(mask);
    moveBoard(mask, 'r');
    std::cout << "Moving right\n";
    printBoard(mask);
}