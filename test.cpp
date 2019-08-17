#include <iostream>
#include <cstdint>
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

int main() {
    uint64_t mask {0x0};
    printBoard(mask);
    std::cout << '\n' << numEmptyTiles(mask) << " empty tiles\n";
    std::cout << "----------------\n";
    placeRandomTile(mask);
    placeRandomTile(mask);
    printBoard(mask);
    rotateBoard(mask);
}