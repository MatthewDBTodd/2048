#include <algorithm>
#include "Board.h"
#include "randomNum.h"
#include "Tile.h"
#include "Move.h"

Board::Board() : curScore{0}, turnNum{0}, numEmptyTiles{16} {}

bool Board::moveBoard(const char c) {
    switch (c) {
        static Right r;
        static Left l;
        static Up u;
        static Down d;
        case 'u': return move(u); break;
        case 'd': return move(d); break;
        case 'l': return move(l); break;
        case 'r': return move(r); break;
        default: throw "Invalid move selection\n";
    }
}

void Board::placeRandomTile() {
    int randomIndex {(numEmptyTiles > 1) ? randomNum::getRandomNum(numEmptyTiles-1) : 0};
    int randomValue {randomNum::getRandomNum(9)};
    randomValue = (randomValue == 9) ? 4 : 2;
    int count {0};
    for (auto& tile : board) {
        if (tile != 0) { continue; }
        if (count++ == randomIndex) {
            tile.setValue(randomValue);
            --numEmptyTiles;
            break;
        }
    }
}

/* Tiles can only merge once per move, once a tile is merged it is locked
 * to prevent further merges. This function then unlocks all the tiles for
 * the next turn
 */
void Board::unlockTiles() {
    for (auto& tile: board) {
        tile.unlock();
    }
}

bool Board::isGameOver() {
    if (numEmptyTiles > 0) { return false; }
    for (std::size_t i {0}; i < board.size(); ++i) {
        if (board[i] == 0) return false;
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

/* move.start  = the starting position of the loop for each move type. Need to
 *               move through the loop in the opposite direction of the move direction
 *               so that tiles "in front" are moved as far as they can go first
 * move.end()  = the ending loop condition for each move type
 * move.step() = the step direction for each move type i.e. --i or ++i
 * move.test() = certain tiles don't need checking for each move type as they're 
 *               at the furthest edge
 * move.next() = the relative tile index of the tile to check for possible merges
 *               or swaps. i.e. for a down move, you want to check at index i+4
 * All defined in Move.h
 */
template <typename T>
bool Board::move(const T& move) {
    bool hasMoved {false};
    for (int i {move.start}; move.end(i); i = move.step(i)) {
        if (move.test(i) || board[i] == 0) continue;
        if ((board[i] == board[move.next(i)]) && (board[i].isUnlocked() && board[move.next(i)].isUnlocked())) {
            curScore += (board[i].value() * 2);
            board[move.next(i)].setValue(board[i].value() * 2);
            board[i].setValue(0);
            ++numEmptyTiles;
            board[move.next(i)].lock();
            hasMoved = true;
        } else if (board[move.next(i)] == 0) {
            board[move.next(i)].setValue(board[i].value());
            board[i].setValue(0);
            hasMoved = true;
            i = (move.next(0) < 0) ? move.next(i)-1 : move.next(i)+1;
        }
    }
    if (hasMoved) ++turnNum;
    return hasMoved;
}
