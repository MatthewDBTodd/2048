#ifndef TILE_H
#define TILE_H

class Tile {
public:
    Tile();
    int value() const { return val; }
    void setValue(const int v);
    void lock() { locked = true; }
    void unlock() { locked = false; }
    bool isUnlocked() const { return !locked; }
    bool operator==(const Tile& t) const;
    bool operator==(const int n) const;
    bool operator!=(const Tile& t) const;
private:
    int val;
    bool locked;
};

#endif