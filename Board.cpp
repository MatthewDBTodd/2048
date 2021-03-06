#include "Board.h"
#include "randomNum.h"
#include "Move_.h"

/*
 * Board is represented as a 64-bit integer
 * left most digit is top left (i.e. the most significant bit):
 * 0x0123456789ABCDEF:
 * 0   1   2   3
 * 4   5   6   7
 * 8   9   A   B
 * C   D   E   F
 */
uint16_t Board::forwardTable[65536];
uint16_t Board::reverseTable[65536]; 
int Board::scoreTable[65536];
uint8_t Board::zeroTable[65536];
const uint16_t Board::resetMasks[4] {0xFFF0, 0xFF0F, 0xF0FF, 0x0FFF};

Board::Board() : board {0}, _score {0} {
    populateTables();
}

void Board::placeRandomTile() {
    int emptyTiles {numEmptyTiles()}; 
    int index {randomNum::getRandomNum(emptyTiles-1)};
    uint64_t val {static_cast<uint64_t>(randomNum::getRandomNum(9))};
    val = (val == 9) ? 2 : 1;
    int count {0};
    uint64_t boardCopy {board};
    for (int i {0}; i < 16; ++i, boardCopy >>= 4) { 
        uint64_t tile {boardCopy & 0xF}; 
        if (tile != 0) { 
            continue;
        }
        if (count++ == index) { 
            board |= (val << (i << 2));
            break;
        }
    }
}

bool Board::moveBoard(const char move) {
    uint64_t newBoard {0};
    uint64_t rowMask {0xFFFF};
    if (move == 'u' || move == 'd') {
        board = rotateBoard(board);
    }
    bool hasMoved {false};
    for (int i {0}; i < 4; ++i, board >>= 16) { 
        uint64_t row {board & rowMask}; 
        uint64_t newRow {(move == 'r' || move == 'd') ? forwardTable[row] : reverseTable[row]}; 
        if (newRow != row) {
            hasMoved = true;
            _score += scoreTable[row];
        }
        newBoard |= (newRow << (i << 4)); 
    }
    if (move == 'u' || move == 'd') {
        newBoard = rotateBoard(newBoard);
    }
    board = newBoard;
    return hasMoved;
}

bool Board::isGameOver() {
    if (numEmptyTiles() > 0) {
        return false;
    }
    uint64_t rowMask {0xFFFF};
    // need to use a copy as bit shifting the board will lose the bits for the up/down iteration
    uint64_t boardCopy {board};
    // right/left:
    for (int i {0}; i < 4; ++i, boardCopy >>= 16) {
        uint64_t row {boardCopy & rowMask};
        // row has changed, i.e. made a successful move
        if (row != forwardTable[row]) {
            return false;
        }
    }
    // up/down:
    boardCopy = rotateBoard(board);
    for (int i {0}; i < 4; ++i, boardCopy >>= 16) {
        uint64_t row {boardCopy & rowMask};
        if (row != reverseTable[row]) {
            return false;
        }
    }
    return true;
}

int Board::operator[](const std::size_t i) const {
    std::size_t index {15-i};
    uint64_t mask {0xF};
    mask <<= (index*4);
    uint64_t val {board & mask};
    val >>= (index*4);
    val = (0x1ull << val);
    val = (val == 1) ? 0 : val;
    return static_cast<int>(val);
}

void Board::populateTables() {
    for (int i {0}; i < 65536; ++i) {
        Forward f;
        Reverse r;
        uint16_t row {static_cast<uint16_t>(i)};
        forwardTable[i] = generateRow(row, f); 
        reverseTable[i] = generateRow(row, r);
        scoreTable[i] = generateScore(row);
        zeroTable[i] = generateNumZeroes(row);
    }
}

template <typename T>
uint16_t Board::generateRow(uint16_t row, T& move) const {
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

template <typename T>
uint16_t Board::merge(uint16_t row, int bitNum, T& move) const {
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
uint16_t Board::swap(uint16_t row, int bitNum, int value, T& move) const {
    row |= value << (move.nextEmptyPosition * 4);
    row &= resetMasks[bitNum];
    move.lastValueIndex = move.nextEmptyPosition;
    move.nextEmptyPosition = move.next(move.nextEmptyPosition);
    return row;
}


int Board::generateScore(uint16_t row) const {
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

uint8_t Board::generateNumZeroes(uint16_t row) const {
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

int Board::numEmptyTiles() const {
    int numZeroes {0};
    uint64_t boardCopy {board};
    for (int i {0}; i < 4; ++i, boardCopy >>= 16) {
        uint64_t row {boardCopy & 0xFFFF};
        numZeroes += zeroTable[row];
    }
    return numZeroes;
}

/*
 * Transpose the board for up/down movement:
 * 0   1   2   3      0   4   8   C
 * 4   5   6   7 ---> 1   5   9   D
 * 8   9   A   B      2   6   A   E
 * C   D   E   F      3   7   B   F
 */
uint64_t Board::rotateBoard(uint64_t board) const {
    uint64_t x {(board ^ (board >> 12)) & 0x0000F0000F0000F0};
    uint64_t y {x << 12};
    board ^= x ^ y;

    x = (board ^ (board >> 24)) & 0x00000000F0000F00;
    y = x << 24;
    board ^= x ^ y;

    x = (board ^ (board >> 36)) & 0x000000000000F000;
    y = x << 36;
    board ^= x ^ y;

    return board;
}

int Board::getMask(const uint16_t row, const int pos) const {
    return (row & ~resetMasks[pos]) >> (pos << 2);
}