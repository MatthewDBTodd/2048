#include <ncurses.h>
#include <iomanip>
#include <vector>
#include "Tile.h"

std::vector<MergeListener*> Tile::obs;

Tile::Tile() : val {0}, merged {false} {}

Tile::Tile(const int v) : val {v}, merged {false} {} // for deleting later?

void Tile::setValue(const int v) {
    val = (v < 0) ? 0 : v;
}

bool Tile::move(Tile& dest) {
    if (dest == 0) {
        swap(*this, dest);
        return true;
    } else if (*this == dest && !merged && !dest.merged) {
        notifyAll(val * 2);
        merge(*this, dest);
        return true;
    } else {
        return false;
    }
}

void Tile::registerObserver(MergeListener* o) {
    obs.push_back(o);
}

void Tile::notifyAll(const int n) const {
    for (const auto& o : obs) {
        o->notify(n);
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
    return *this;
}

std::ostream& operator<<(std::ostream& os, const Tile& t) {
    if (t.val) {
        return os << std::setw(7) << t.val; 
    } else {
        return os << std::setw(7) << "-";
    }
}

void Tile::display() const {
    initscr();
    start_color();
    init_pair(1, COLOR_BLACK, COLOR_RED);
    attron(COLOR_PAIR(1));
    printw("   %i   ", val);
    attroff(COLOR_PAIR(1));
    refresh();
    //endwin();
}

void swap(Tile& t1, Tile& t2) {
    if (t1.value() && t2.value()) return;
    Tile temp = t1;
    t1 = t2;
    t2 = temp;
}

void merge(Tile& origin, Tile& dest) {
    if (origin != dest || origin.hasMerged() || dest.hasMerged()) return;
    dest *= 2;
    origin *= 0;
}