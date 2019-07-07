#ifndef TILE_H
#define TILE_H

#include <ostream>
#include "MergeListener.h"

class Tile {
private:
    int val;
    bool merged;
    static MergeListener* obs;
public:
    Tile();
    Tile(const int v); // for deleting later?
    void setValue(const int v);
    int value() const { return val; }
    bool move(Tile& dest);
    void resetMergeStatus() { merged = false; }
    bool hasMerged() const { return merged; }
    void registerObserver(MergeListener* o);
    bool operator==(const Tile& t) const;
    bool operator==(const int n) const;
    bool operator!=(const Tile& t) const;
    Tile& operator*=(const int n);
    friend std::ostream& operator<<(std::ostream& os, const Tile& t);
    void display() const;
};

void swap(Tile& t1, Tile& t2);
void merge(Tile& origin, Tile& dest);

#endif