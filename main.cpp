#include <vector>
#include <iostream>
#include "Tile.h"
#include "Board.h"

int main() {
    Board b;
    for (int i {1}; i < b.size(); ++i) {
        b[i] = (i+1);
    }
    std::cout << b;
    return 0;
}