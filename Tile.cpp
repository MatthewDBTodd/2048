#include <iomanip>
#include "Tile.h"

void Tile::setValue(const int v) {
    val = (v < 0) ? 0 : v;
}

void Tile::move(Tile& dest) {
    if (dest == 0) {
        swap(*this, dest);
    } else if (*this == dest) {
        merge(*this, dest);
    } else {
        return;
    }
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

Tile& Tile::operator*=(const int n) {
    val *= n;
    merged = true;
}

std::ostream& operator<<(std::ostream& os, const Tile& t) {
    if (t.val) {
        return os << std::setw(7) << t.val; 
    } else {
        return os << std::setw(7) << "-";
    }
}

void swap(Tile& t1, Tile& t2) {
    if (t1.value() && t2.value()) return;
    Tile temp = t1;
    t1 = t2;
    t2 = temp;
}

void merge(Tile& origin, Tile& dest) {
    if (origin != dest || dest.hasMerged()) return;
    dest *= 2;
    origin.zeroTile();
}