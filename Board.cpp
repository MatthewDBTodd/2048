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

/* move.start  = the starting position of the loop for each move type. Need to
 *               move through the loop in the opposite direction of the move direction
 *               so that tiles "in front" are moved as far as they can go first
 * move.end()  = the ending loop condition for each move type
 * move.step() = the step direction for each move type i.e. ++i or +4
 * move.test() = When to reset the search for empty space and/or merge for that 
 *               column/row before moving on to the next one
 * All defined in Move.h
 */
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
