#include "Game.h"

int main() {
    Game g;
    g.start();
    /*
    Board b;
    b.placeRandomTile();
    b.placeRandomTile();
    std::cout << b;
    MoveFactory f;
    while (true) {
        std::cout << "Enter choice: ";
        char c;
        std::cin >> c;
        std::shared_ptr<Mover> m {f.get(c)};
        if (m->moveBoard(b)) {
            b.placeRandomTile();
        }
        b.resetTileStatus();
        std::cout << b;
        if (b.isGameOver()) {
            std::cout << "Game over\n";
            break;
        }
    }
    */
}