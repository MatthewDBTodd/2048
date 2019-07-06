#include "catch.hpp"
#include "../Board.h"
#include "../Mover.h"

TEST_CASE("Board::operator[]") {
    SECTION("Test const[]") {
        const Board b;
        REQUIRE(b[0].value() == 0);
        REQUIRE_THROWS(b[-1]);
        REQUIRE_THROWS(b[16]);
    }

    SECTION("Test non const[]") {
        Board b;
        REQUIRE(b[0].value() == 0);
        Tile t;
        t.setValue(16);
        b[0] = t;
        REQUIRE(b[0].value() == 16);
        REQUIRE_THROWS(b[-1]);
        REQUIRE_THROWS(b[16]);
    }
}

TEST_CASE("Board::isGameOver()") {
    Board b;

    SECTION("Sanity check, blank board") {
        REQUIRE(!b.isGameOver());
    }

    SECTION("Single blank tile") {
        for (int i {1}; i < b.size(); ++i) {
            b[i] = i;
        }
        REQUIRE(!b.isGameOver());
    }

    SECTION("Full board with all same value") {
        for (int i {0}; i < b.size(); ++i) {
            b[i] = 2;
        }
        REQUIRE(!b.isGameOver());
    }

    SECTION("(0,0) -> (1,0)") {
        for (int i {0}; i < b.size(); ++i) {
            b[i] = i;
        }
        b[0] = 4;
        REQUIRE(!b.isGameOver());
    }

    SECTION("(0,3) -> (1,3") {
        for (int i {0}; i < b.size(); ++i) {
            b[i] = i;
        }
        b[7] = 3;
        REQUIRE(!b.isGameOver());
    }

    SECTION("(3,0) -> (3,1)") {
        for (int i {0}; i < b.size(); ++i) {
            b[i] = i;
        }
        b[13] = 12;
        REQUIRE(!b.isGameOver());
    }

    SECTION("(2,3) -> (3,3)") {
        for (int i {0}; i < b.size(); ++i) {
            b[i] = i;
        }
        b[15] = 11;
        REQUIRE(!b.isGameOver());
    }

    SECTION("Full board with different values") {
        for (int i {0}; i < b.size(); ++i) {
            b[i] = (i+1);
        }
        REQUIRE(b.isGameOver());
    }
}

TEST_CASE("Board::placeRandomTile()") {
    Board b;

    SECTION("Blank board") {
        b.placeRandomTile();
        bool tilePlaced {false};
        for (int i {0}; i < b.size(); ++i) {
            if (b[i] != 0) {
                tilePlaced = true;
                break;
            }
        }
        REQUIRE(tilePlaced);
    }

    SECTION("One blank tile left") {
        for (int i {1}; i < b.size(); ++i) {
            b[i] = (i+1);
        }
        b.placeRandomTile();
        REQUIRE(b[0] != 0);
    }

    SECTION("Sanity check - gridlocked board") {
        for (int i {0}; i < b.size(); ++i) {
            b[i] = (i+1);
        }
        REQUIRE_THROWS(b.placeRandomTile());
    }
}

TEST_CASE("Board::resetTileStatus") {
    Board b;
    Down d;
    for (int i {0}; i < b.size(); ++i) {
        b[i] = 4;
    }

    SECTION("Sanity check - all tile statuses after merging set to true") {
        d.moveBoard(b);
        bool merged {true};
        for (int i {8}; i < b.size(); ++i) {
            if (!b[i].hasMerged()) {
                merged = false;
                break;
            }
        }
        REQUIRE(merged);
    }

    SECTION("Resetting merge statuses after turn") {
        d.moveBoard(b);
        b.resetTileStatus();
        bool merged {false};
        for (int i {0}; i < b.size(); ++i) {
            if (b[i].hasMerged()) {
                merged = true;
                break;
            }
        }
        REQUIRE(!merged);
    }
}