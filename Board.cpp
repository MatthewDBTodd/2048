#include "Board.h"
#include "randomNum.h"
#include "Move_.h"

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

bool Board::moveBoard(const char move) {
    uint64_t newBoard {0};
    uint64_t rowMask {0xFFFF};
    if (move == 'u' || move == 'd') {
        board = rotateBoard(board);
    }
    bool hasMoved {false};
    for (int i {0}; i < 4; ++i, rowMask <<= 16) {
        uint16_t row {static_cast<uint16_t>((board & rowMask) >> (16*i))};
        uint64_t newRow {(move == 'r' || move == 'd') ? forwardTable[row] : reverseTable[row]};
        if (newRow != row) {
            hasMoved = true;
            _score += scoreTable[row];
        }
        newBoard |= (newRow << (i*16));
    }
    // reverse back
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
    uint64_t rowMask {0xFFFF};
    for (int i {0}; i < 4; ++i, boardCopy >>= 16) {
        uint64_t row {boardCopy & rowMask};
        numZeroes += zeroTable[row];
    }
    return numZeroes;
}

uint64_t Board::rotateBoard(const uint64_t board) const {
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

int Board::getMask(const uint16_t row, const int pos) const {
    return (row & ~resetMasks[pos]) >> (pos << 2);
}

// old code
/* 
#include <algorithm>
#include "Board.h"
#include "randomNum.h"
#include "Tile.h"
#include "Move.h"

Board::Board() : curScore{0}, turnNum{0}, _numEmptyTiles{16} {}

bool Board::moveBoard(const char c) {
    static Right r;
    static Left l;
    static Up u;
    static Down d;
    switch (c) {
        case 'u': return move(u); break;
        case 'd': return move(d); break;
        case 'l': return move(l); break;
        case 'r': return move(r); break;
        default: throw "Invalid move selection\n";
    }
}

void Board::placeRandomTile() {
    int randomIndex {(_numEmptyTiles > 1) ? randomNum::getRandomNum(_numEmptyTiles-1) : 0};
    int randomValue {randomNum::getRandomNum(9)};
    randomValue = (randomValue == 9) ? 4 : 2;
    int count {0};
    for (auto& tile : board) {
        if (tile != 0) { continue; }
        if (count++ == randomIndex) {
            tile.setValue(randomValue);
            --_numEmptyTiles;
            break;
        }
    }
}

bool Board::isGameOver() {
    if (_numEmptyTiles > 0) { return false; }
    for (std::size_t i {0}; i < board.size(); ++i) {
        switch (i) {
            // tiles on the right most column only need to check below
            case 3: case 7: case 11: {
                if (board[i] == board[i+4]) {return false;} break;
            }
            // tiles on the bottom row only need to check to their right
            case 12: case 13: case 14: {
                if (board[i] == board[i+1]) {return false;} break;
            }
            // all remaining tiles check below and to the right
            default:
                if (board[i] == board[i+1] || board[i] == board[i+4]) {return false;} break;
        }
    }
    return true;
}

int Board::operator[](const std::size_t i) const {
    return board[i].value();
}

int Board::placeTileEmptyPos(int pos, int value) {
    int count {0};
    for (auto& tile : board) {
        if (tile != 0) { continue; }
        if (count++ == pos) {
            tile.setValue(value);
            --_numEmptyTiles;
            break;
        }
    } 
    return count-1;
}

void Board::placeTile(int pos, int value) {
    board[pos].setValue(value);
    if (value == 0) {
        ++_numEmptyTiles;
    }
}

 * move.start  = the starting position of the loop for each move type. Need to
 *               move through the loop in the opposite direction of the move direction
 *               so that tiles "in front" are moved as far as they can go first
 * move.end()  = the ending loop condition for each move type
 * move.step() = the step direction for each move type i.e. ++i or +4
 * move.test() = When to reset the search for empty space and/or merge for that 
 *               column/row before moving on to the next one
 * All defined in Move.h
 * 
template <typename Move>
bool Board::move(Move& move) {
    bool hasMoved {false};
    for (int i {move.start}; move.end(i); i = move.step(i)) {
        if (board[i] == 0) {
            move.nextFreeSlot = (move.nextFreeSlot == -1) ? i : move.nextFreeSlot;
        } else if (board[i] == move.previousTileValue) {
            hasMoved = true;
            merge(move, i);
        } else {
            move.previousTileValue = board[i].value();
            move.previousTile = i;
            if (move.nextFreeSlot != -1) {
                hasMoved = true;
                swap(move, i);
            } 
        }
        if (move.test(i)) {
            reset(move);
        }
    }
    if (hasMoved) { ++turnNum; }
    return hasMoved;
}

template <typename Move>
void Board::merge(Move& move, int i) {
    int value {board[i].value()};
    curScore += (value * 2);
    board[move.previousTile].setValue(value * 2);
    board[i].setValue(0);
    ++_numEmptyTiles;
    move.nextFreeSlot = i;
    move.previousTileValue = -1;
    move.previousTile = -1;
}

template <typename Move>
void Board::swap(Move& move, int i) {
    board[move.nextFreeSlot].setValue(board[i].value());
    board[i].setValue(0);
    move.previousTile = move.nextFreeSlot;
    move.nextFreeSlot = move.step(move.nextFreeSlot);
}
*/