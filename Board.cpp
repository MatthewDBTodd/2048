#include <algorithm>
#include "Board.h"
#include "randomNum.h"
#include "Tile.h"

Board::Board() : board(16), curScore{0}, turnNum{0} {
    for (auto& tile : board) {
        emptyTiles.push_back(&tile);
    }
}

Board::Board(const Board& b) : board{b.board}, curScore{b.curScore}, turnNum{b.turnNum} {
    // so the empty tile pointers are not pointing to the same tiles in the original board
    for (auto& tile : board) {
        emptyTiles.push_back(&tile);
    }
}

Board& Board::operator=(const Board& b) {
    board = b.board;
    curScore = b.curScore;
    turnNum = b.turnNum;
    // so the empty tile pointers are not pointing to the same tiles in the original board
    for (auto& tile: board) {
        emptyTiles.push_back(&tile);
    }
    return *this;
}

bool Board::moveBoard(const char c) {
    switch (c) {
        case 'u': return moveUp(); break;
        case 'd': return moveDown(); break;
        case 'l': return moveLeft(); break;
        case 'r': return moveRight(); break;
        default: throw "Invalid move selection\n";
    }
}

void Board::placeRandomTile() {
    int randomIndex {getRandomNum(emptyTiles.size())};
    int randomValue {getRandomNum(9)};
    randomValue = (randomValue == 9) ? 4 : 2;
    emptyTiles[randomIndex]->setValue(randomValue);
    emptyTiles.erase(std::remove(emptyTiles.begin(), emptyTiles.end(), emptyTiles[randomIndex]), emptyTiles.end());
}

void Board::unlockTiles() {
    for (auto& tile: board) {
        tile.unlock();
    }
}

bool Board::isGameOver() {
    if (emptyTiles.size() > 0) {
        return false;
    }
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

bool Board::moveRight() {
    bool hasMoved {false};
    for (int i {static_cast<int>(board.size()-1)}; i >= 0; --i) {
        if ((i+1) % 4 == 0 || board[i] == 0) continue;
        if ((board[i] == board[i+1]) && (board[i].isUnlocked() && board[i+1].isUnlocked())) {
            curScore += (board[i].value() * 2);
            board[i+1].setValue(board[i].value() * 2);
            board[i].setValue(0);
            markAsEmpty(&board[i]);
            board[i+1].lock();
            hasMoved = true;
        } else if (board[i+1] == 0) {
            board[i+1].setValue(board[i].value());
            board[i].setValue(0);
            markAsEmpty(&board[i]);
            markAsOccupied(&board[i+1]);
            hasMoved = true;
            i += 2;
        }
    }
    if (hasMoved) ++turnNum;
    return hasMoved;
}

bool Board::moveLeft() {
    bool hasMoved {false};
    for (int i {0}; i < static_cast<int>(board.size()); ++i) {
        if (i % 4 == 0 || board[i] == 0) continue;
        if ((board[i] == board[i-1]) && (board[i].isUnlocked() && board[i-1].isUnlocked())) {
            curScore += (board[i].value() * 2);
            board[i-1].setValue(board[i].value() * 2);
            board[i].setValue(0);
            markAsEmpty(&board[i]);
            board[i-1].lock();
            hasMoved = true;
        } else if (board[i-1] == 0) {
            board[i-1].setValue(board[i].value());
            board[i].setValue(0);
            markAsEmpty(&board[i]);
            markAsOccupied(&board[i-1]);
            hasMoved = true;
            i -= 2;
        }
    }
    if (hasMoved) ++turnNum;
    return hasMoved;
}

bool Board::moveUp() {
    bool hasMoved {false};
    for (int i {0}; i < static_cast<int>(board.size()); ++i) {
        if (i < 4 || board[i] == 0) continue;
        if ((board[i] == board[i-4]) && (board[i].isUnlocked() && board[i-4].isUnlocked())) {
            curScore += (board[i].value() * 2);
            board[i-4].setValue(board[i].value() * 2);
            board[i].setValue(0);
            markAsEmpty(&board[i]);
            board[i-4].lock();
            hasMoved = true;
        } else if (board[i-4] == 0) {
            board[i-4].setValue(board[i].value());
            board[i].setValue(0);
            markAsEmpty(&board[i]);
            markAsOccupied(&board[i-4]);
            hasMoved = true;
            i -= 5;
        }
    }
    if (hasMoved) ++turnNum;
    return hasMoved;
}

bool Board::moveDown() {
    bool hasMoved {false};
    for (int i {static_cast<int>(board.size()-1)}; i >= 0; --i) {
        if (i > 11 || board[i] == 0) continue;
        if ((board[i] == board[i+4]) && (board[i].isUnlocked() && board[i+4].isUnlocked())) {
            curScore += (board[i].value() * 2);
            board[i+4].setValue(board[i].value() * 2);
            board[i].setValue(0);
            markAsEmpty(&board[i]);
            board[i+4].lock();
            hasMoved = true;
        } else if (board[i+4] == 0) {
            board[i+4].setValue(board[i].value());
            board[i].setValue(0);
            markAsEmpty(&board[i]);
            markAsOccupied(&board[i+4]);
            hasMoved = true;
            i += 5;
        }
    }
    if (hasMoved) ++turnNum;
    return hasMoved;
}

void Board::markAsEmpty(Tile* t) {
    emptyTiles.push_back(t);
}

void Board::markAsOccupied(Tile* t) {
    emptyTiles.erase(std::remove(emptyTiles.begin(), emptyTiles.end(), t), emptyTiles.end());
}
