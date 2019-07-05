#include "Mover.h"

void Right::moveBoard(Board& b) const {
    for (int i {b.size() - 1}; i >= 0; --i) {
        if ((i+1) % 4 == 0) continue;
        int j {i};
        while (b[j].move(b[j+1])) {
            ++j;
            if ((j+1) % 4 == 0) break;
        }
    }
}

void Left::moveBoard(Board& b) const {
    for (int i {0}; i < b.size(); ++i) {
        if (i % 4 == 0) continue;
        int j {i};
        while (b[j].move(b[j-1])) {
            --j;
            if (j % 4 == 0) break;
        }
    }
}

void Up::moveBoard(Board& b) const {
    for (int i {0}; i < b.size(); ++i) {
        if (i < 4) continue;
        int j {i};
        while (b[j].move(b[j-4])) {
            j -= 4;
            if (j < 4) break;
        }
    }
}

void Down::moveBoard(Board& b) const {
    for (int i {b.size() - 1}; i >= 0; --i) {
        if (i > 11) continue;
        int j {i};
        while (b[j].move(b[j+4])) {
            j += 4;
            if (j > 11) break;
        }
    }
}