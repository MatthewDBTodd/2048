#ifndef TILE_H
#define TILE_H

class Tile {
public:
    Tile();
    int value() const { return val; }
    void setValue(const int v);
    bool operator==(const Tile& t) const;
    bool operator==(const int n) const;
    bool operator!=(const Tile& t) const;
    bool operator!=(const int n) const;
private:
    int val;
};

#endif