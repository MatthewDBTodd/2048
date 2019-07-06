#include "Mover.h"

bool Right::moveBoard(Board& b) const {
    bool hasMoved {false};
    for (int i {b.size() - 1}; i >= 0; --i) {
        if ((i+1) % 4 == 0 || b[i] == 0) continue;
        int j {i};
        while (b[j].move(b[j+1])) {
            hasMoved = true;
            ++j;
            if ((j+1) % 4 == 0) break;
        }
    }
    return hasMoved;
}

bool Left::moveBoard(Board& b) const {
    bool hasMoved {false};
    for (int i {0}; i < b.size(); ++i) {
        if (i % 4 == 0 || b[i] == 0) continue;
        int j {i};
        while (b[j].move(b[j-1])) {
            hasMoved = true;
            --j;
            if (j % 4 == 0) break;
        }
    }
    return hasMoved;
}

bool Up::moveBoard(Board& b) const {
    bool hasMoved {false};
    for (int i {0}; i < b.size(); ++i) {
        if (i < 4 || b[i] == 0) continue;
        int j {i};
        while (b[j].move(b[j-4])) {
            hasMoved = true;
            j -= 4;
            if (j < 4) break;
        }
    }
    return hasMoved;
}

bool Down::moveBoard(Board& b) const {
    bool hasMoved {false};
    for (int i {b.size() - 1}; i >= 0; --i) {
        if (i > 11 || b[i] == 0) continue;
        int j {i};
        while (b[j].move(b[j+4])) {
            hasMoved = true;
            j += 4;
            if (j > 11) break;
        }
    }
    return hasMoved;
}