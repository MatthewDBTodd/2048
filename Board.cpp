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

bool Board::isGameOver() {
    for (std::size_t i {0}; i < board.size(); ++i) {
        if (board[i] == 0) return false;
        switch (i) {
            case 3: case 7: case 11: {
                if (board[i] == board[i+4]) return false;
            }
            case 12: case 13: case 14: {
                if (board[i] == board[i+1]) return false;
            }
            default:
                if (board[i] == board[i+1] || board[i] == board[i+4]) return false;
        }
    }
    return true;
}