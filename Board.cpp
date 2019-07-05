#include <iostream>
#include "Board.h"

std::ostream& operator<<(std::ostream& os, const Board& b) {
    int count {0};
    os << "\n\n";
    for (const auto& tile : b.board) {
        os << tile;
        if (++count % 4 == 0) {
            os << "\n\n\n";
        }
    }
    return os;
}

const Tile& Board::operator[](const int i) const {
    if (i < 0 || i >= board.size()) {
        throw std::exception();
    }
    return board[i];
}

Tile& Board::operator[](const int i) {
    if (i < 0 || i >= board.size()) {
        throw std::exception();
    }
    return board[i];
}