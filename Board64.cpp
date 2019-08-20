#include "Board64.h"
#include "randomNum.h"
#include "Move_.h"
#include <iostream>
#include <iomanip>
#include <fstream>

uint16_t forwardTable[65536];
uint16_t reverseTable[65536]; 
int scoreTable[65536];
uint8_t zeroTable[65536];
uint16_t resetMasks[4] {
    0xFFF0,
    0xFF0F,
    0xF0FF,
    0x0FFF
};

uint64_t rotateBoard(const uint64_t board) {
    uint64_t newBoard {0};
    for (int i {0}; i < 4; ++i) {
        for (int j {0}; j < 4; ++j) {
            // make a mask to extract the bit you're going to be moving
            uint64_t mask {0xFull << (((j*4)+i)*4)};
            // extract the bits with the mask
            mask &= board;
            // shift back to right most position
            mask >>= ((j*4)+i)*4;
            // shift to new position
            mask <<= ((i*4)+j)*4;
            // set bits on newBoard
            newBoard |= mask;
        } 
    }
    return newBoard;
}

void printBoard(uint64_t board) {
    uint64_t mask {0xF000000000000000};
    for (int i {15}; i >= 0; --i, mask >>= 4) {
        uint64_t val {board & mask};
        val >>= (i*4);
        if (!val) {
            std::cout << "-  ";
        } else {
            std::cout << (0x1 << val) << "  ";
        }
        if (i % 4 == 0) {
            std::cout << "\n\n";
        }
    }
    std::cout << "---------------------------\n";
}

void placeRandomTile(uint64_t& board) {
    int emptyTiles {numEmptyTiles(board)}; 
    int index {randomNum::getRandomNum(emptyTiles-1)};
    uint64_t val {static_cast<uint64_t>(randomNum::getRandomNum(9))};
    val = (val == 9) ? 2 : 1;
    int count {0};
    uint64_t mask {0xF};
    for (int i {0}; i < 16; ++i, mask <<= 4) {
        uint64_t tile {board & mask};
        tile >>= (i*4);
        if (tile != 0) {
            continue;
        }
        if (count++ == index) {
            board |= (val << (i*4));
            break;
        }
    }
}

int numEmptyTiles(uint64_t board) {
    int numZeroes {0};
    uint64_t rowMask {0xFFFF};
    for (int i {0}; i < 4; ++i, board >>= 16) {
        uint64_t row {board & rowMask};
        numZeroes += zeroTable[row];
    }
    return numZeroes;
}

uint64_t moveBoard(uint64_t board, char move, int& score) {
    uint64_t newBoard {0};
    uint64_t rowMask {0xFFFF};
    if (move == 'u' || move == 'd') {
        board = rotateBoard(board);
    }
    for (int i {0}; i < 4; ++i, rowMask <<= 16) {
        uint16_t row {static_cast<uint16_t>((board & rowMask) >> (16*i))};
        uint64_t newRow;
        if (move == 'r' || move == 'd') {
            newRow = forwardTable[row];
        } else {
            newRow = reverseTable[row];
        }
        score += scoreTable[row];
        newBoard |= (newRow << (i*16));
    }
    if (move == 'u' || move == 'd') {
        // reverse back
        newBoard = rotateBoard(newBoard);
    }
    return newBoard;
}

int getMask(const uint16_t row, const int pos) {
    return (row & ~resetMasks[pos]) >> (pos << 2);
}

template <typename T>
uint16_t merge(uint16_t row, int bitNum, T& move) {
    move.lastValue = (move.lastValue == 0xF) ? 0xF : move.lastValue+1;
    // zero tile
    row &= resetMasks[bitNum];
    row &= resetMasks[move.lastValueIndex];
    // set to incremented value
    row |= (move.lastValue << (move.lastValueIndex << 2));
    move.nextEmptyPosition = move.next(move.lastValueIndex);
    move.lastValue = -1;
    move.lastValueIndex = -1;
    return row;
}

template <typename T>
uint16_t swap(uint16_t row, int bitNum, int value, T& move) {
    row |= value << (move.nextEmptyPosition * 4);
    row &= resetMasks[bitNum];
    move.lastValueIndex = move.nextEmptyPosition;
    move.nextEmptyPosition = move.next(move.nextEmptyPosition);
    return row;
}

template <typename T>
uint16_t generateRow(uint16_t row, T& move) {
    for (int i {move.start}; move.end(i); i = move.next(i)) {
        int value {getMask(row, i)};
        if (!value) {
            move.nextEmptyPosition = (move.nextEmptyPosition == -1) ? i : move.nextEmptyPosition;
        } else if (value == move.lastValue) {
            row = merge(row, i, move);
        } else {
            move.lastValue = value;
            move.lastValueIndex = i;
            if (move.nextEmptyPosition != -1) {
                row = swap(row, i, value, move);
            }
        }
    }
    return row;
}

int generateScore(uint16_t row) {
    int score {0};
    char lastValue {0};
    for (int i {0}; i < 4; ++i) {
        char value = ((0xF << (i*4)) & row) >> (i*4);
        if (value == 0) { continue; }
        if (value == lastValue) {
            score += (0x1 << (value+1));
            lastValue = 0;
        } else {
            lastValue = value; 
        }
    }
    return score;
}

void populateTables() {
    //std::ofstream out;
    //out.open("table.txt");
    for (int i {0}; i < 65536; ++i) {
        Forward f;
        Reverse r;
        uint16_t row {static_cast<uint16_t>(i)};
        forwardTable[i] = generateRow(row, f); 
        reverseTable[i] = generateRow(row, r);
        scoreTable[i] = generateScore(row);
        zeroTable[i] = generateNumZeroes(row);
        /* 
        out << std::setfill('0') << std::setw(4) << std::hex << i << '\n' <<
        "\tForward --> " << forwardTable[i] << '\n' <<
        "\tReverse --> " << reverseTable[i] << '\n' <<
        "\tScore ----> " << scoreTable[i] << '\n' <<
        "\tZeroes ---> " << +zeroTable[i] << "\n\n" << std::dec;
        */
    }
}

uint8_t generateNumZeroes(uint16_t row) {
    uint8_t generateNumZeroes {0};
    uint64_t mask {0xF};
    for (int i {0}; i < 4; ++i, row >>= 4) {
        uint64_t val {row & mask};
        if (!val) {
            ++generateNumZeroes;
        }
    }
    return generateNumZeroes;
}

bool isGameOver(uint64_t board) {
    if (numEmptyTiles(board) > 0) {
        return true;
    }
    uint64_t rowMask {0xFFFF};
    // need to use a copy as bit shifting the board will lose the bits for the up/down
    uint64_t boardCopy {board};
    // right/left
    for (int i {0}; i < 4; ++i, boardCopy >>= 16) {
        uint64_t row {boardCopy & rowMask};
        // row has changed, i.e. made a successful move
        if (row != forwardTable[row]) {
            return false;
        }
    }
    // up/down
    boardCopy = rotateBoard(board);
    for (int i {0}; i < 4; ++i, boardCopy >>= 16) {
        uint64_t row {boardCopy & rowMask};
        if (row != reverseTable[row]) {
            return false;
        }
    }
    return true;
}