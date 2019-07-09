#include <ncurses.h>
#include <iomanip>
#include <vector>
#include "Tile.h"


Tile::Tile() : val {0}, locked {false} {}

void Tile::setValue(const int v) {
    val = (v < 0) ? 0 : v;
}

bool Tile::operator==(const Tile& t) const {
    return val == t.val;
}

bool Tile::operator==(const int n) const {
    return val == n;
}

bool Tile::operator!=(const Tile& t) const {
    return val != t.val;
}