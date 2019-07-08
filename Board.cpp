#include <iostream>
#include <random>
#include "Board.h"

Board::Board() : s{16}, board(s) {}

bool Board::isGameOver() {
    for (std::size_t i {0}; i < board.size(); ++i) {
        if (board[i] == 0) return false;
        switch (i) {
            case 3: case 7: case 11: {
                if (board[i] == board[i+4]) {return false;} break;
            }
            case 12: case 13: case 14: {
                if (board[i] == board[i+1]) {return false;} break;
            }
            default:
                if (board[i] == board[i+1] || board[i] == board[i+4]) {return false;} break;
        }
    }
    return true;
}

void Board::placeRandomTile() {
    std::vector<Tile*> emptyTiles;
    for (auto& t : board) {
        if (t == 0) {
            emptyTiles.push_back(&t);
        }
    }
    if (emptyTiles.size() == 0) throw std::exception();
    int index {getRandomNum(emptyTiles.size()-1)};
    int randomVal = (getRandomNum(9) == 9) ? 4 : 2;
    emptyTiles[index]->setValue(randomVal);
}

void Board::resetTileStatus() {
    for (auto& t : board) {
        t.resetMergeStatus();
    }
}

void Board::registerObserver(MergeListener* obs) {
    Tile::registerObserver(obs);
}

const Tile& Board::operator[](const std::size_t i) const {
    if (i < 0 || i >= board.size()) {
        throw std::exception();
    }
    return board[i];
}

Tile& Board::operator[](const std::size_t i) {
    if (i < 0 || i >= board.size()) {
        throw std::exception();
    }
    return board[i];
}

int getRandomNum(std::size_t range) {
    std::random_device d;
    std::mt19937 rng(d());
    std::uniform_int_distribution<std::mt19937::result_type> num(0, range);
    return num(rng);
}
