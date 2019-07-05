#ifndef TILE_H
#define TILE_H

#include <ostream>

class Tile {
private:
    int val;
    bool merged;
public:
    Tile() : val {0}, merged {false} {}
    Tile(const int v) : val {v}, merged {false} {} // for deleting later
    void setValue(const int v);
    int value() const { return val; }
    bool move(Tile& t2);
    void zeroTile() { val = 0; }
    void resetMergeStatus() { merged = false; }
    bool hasMerged() const { return merged; }
    bool operator==(const Tile& t) const;
    bool operator==(const int n) const;
    bool operator!=(const Tile& t) const;
    Tile& operator*=(const int n);
    friend std::ostream& operator<<(std::ostream& os, const Tile& t);
};

void swap(Tile& t1, Tile& t2);
void merge(Tile& origin, Tile& dest);

#endif