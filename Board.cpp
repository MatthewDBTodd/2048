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