#include "catch.hpp"
#include "../Mover.h"

TEST_CASE("Right") {
    Board b;
    Right r;

    SECTION("Test moving off right edge") {
        b[3] = 2;
        b[7] = 2;
        b[11] = 2;
        b[15] = 2;
        r.moveBoard(b);
        for (int i {0}; i < b.size(); ++i) {
            if ((i + 1) % 4 != 0) {
                REQUIRE(b[i].value() == 0);
            } else {
                REQUIRE(b[i].value() == 2);
            }
        }
    }

    SECTION("Test moving single tile right several tiles") {
        b[0] = 2;
        b[4] = 2;
        b[8] = 2;
        b[12] = 2;
        r.moveBoard(b);
        for (int i {0}; i < b.size(); ++i) {
            if ((i + 1) % 4 != 0) {
                REQUIRE(b[i].value() == 0);
            } else {
                REQUIRE(b[i].value() == 2);
            }
        }
    }

    SECTION("Test moving multiple tiles right with no merges") {
        b[0] = 2;
        b[1] = 4;
        b[2] = 8;
        b[4] = 2;
        b[5] = 4;
        b[9] = 2;
        b[10] = 4;
        b[13] = 2;
        b[14] = 4;
        b[15] = 8;
        r.moveBoard(b);
        REQUIRE(b[0] == 0);
        REQUIRE(b[1] == 2);
        REQUIRE(b[2] == 4);
        REQUIRE(b[3] == 8);
        REQUIRE(b[4] == 0);
        REQUIRE(b[5] == 0);
        REQUIRE(b[6] == 2);
        REQUIRE(b[7] == 4);
        REQUIRE(b[8] == 0);
        REQUIRE(b[9] == 0);
        REQUIRE(b[10] == 2);
        REQUIRE(b[11] == 4);
        REQUIRE(b[12] == 0);
        REQUIRE(b[13] == 2);
        REQUIRE(b[14] == 4);
        REQUIRE(b[15] == 8);
    }

    SECTION("Test right gridlocked") {
        b[0] = 2;
        b[1] = 4;
        b[2] = 8;
        b[3] = 16;
        r.moveBoard(b);
        REQUIRE(b[0] == 2);
        REQUIRE(b[1] == 4);
        REQUIRE(b[2] == 8);
        REQUIRE(b[3] == 16);
    }

    SECTION("Test single merge right") {
        b[0] = 2;
        b[3] = 2;
        r.moveBoard(b);
        REQUIRE(b[3] == 4);
    }

    SECTION("Test single merge right between two tiles not blocked") {
        b[0] = 2;
        b[1] = 2;
        r.moveBoard(b);
        REQUIRE(b[3] == 4);
    }

    SECTION("Test 2 different right value merges in 1 row") {
        b[0] = 2;
        b[1] = 2;
        b[2] = 4;
        b[3] = 4;
        r.moveBoard(b);
        REQUIRE(b[0] == 0);
        REQUIRE(b[1] == 0);
        REQUIRE(b[2] == 4);
        REQUIRE(b[3] == 8);
    }

    SECTION("Test 2 same value merges right in 1 row") {
        b[0] = 2;
        b[1] = 2;
        b[2] = 2;
        b[3] = 2;
        r.moveBoard(b);
        REQUIRE(b[0] == 0);
        REQUIRE(b[1] == 0);
        REQUIRE(b[2] == 4);
        REQUIRE(b[3] == 4);
    }
}

TEST_CASE("Left") {
    Board b;
    Left l;

    SECTION("Test moving off left edge") {
        b[0] = 2;
        b[4] = 2;
        b[8] = 2;
        b[12] = 2;
        l.moveBoard(b);
        REQUIRE(b[0] == 2);
        REQUIRE(b[4] == 2);
        REQUIRE(b[8] == 2);
        REQUIRE(b[12] == 2);
    }

    SECTION("Test moving single tile left several tiles") {
        b[3] = 2;
        b[7] = 2;
        b[11] = 2;
        b[15] = 2;
        l.moveBoard(b);
        REQUIRE(b[0] == 2);
        REQUIRE(b[4] == 2);
        REQUIRE(b[8] == 2);
        REQUIRE(b[12] == 2);
    }

    SECTION("Test moving multiple tiles left with no merges") {
        b[1] = 2;
        b[2] = 4;
        b[3] = 8;
        b[6] = 2;
        b[7] = 4;
        b[9] = 2;
        b[10] = 4;
        b[12] = 2;
        b[13] = 4;
        b[14] = 8;
        l.moveBoard(b);
        REQUIRE(b[0] == 2);
        REQUIRE(b[1] == 4);
        REQUIRE(b[2] == 8);
        REQUIRE(b[3] == 0);
        REQUIRE(b[4] == 2);
        REQUIRE(b[5] == 4);
        REQUIRE(b[6] == 0);
        REQUIRE(b[7] == 0);
        REQUIRE(b[8] == 2);
        REQUIRE(b[9] == 4);
        REQUIRE(b[10] == 0);
        REQUIRE(b[11] == 0);
        REQUIRE(b[12] == 2);
        REQUIRE(b[13] == 4);
        REQUIRE(b[14] == 8);
        REQUIRE(b[15] == 0);
    }

    SECTION("Test left gridlocked") {
        b[0] = 2;
        b[1] = 4;
        b[2] = 8;
        b[3] = 16;
        l.moveBoard(b);
        REQUIRE(b[0] == 2);
        REQUIRE(b[1] == 4);
        REQUIRE(b[2] == 8);
        REQUIRE(b[3] == 16);
    }

    SECTION("Test single merge left") {
        b[0] = 2;
        b[3] = 2;
        l.moveBoard(b);
        REQUIRE(b[0] == 4);
    }

    SECTION("Test single merge left between two tiles not blocked") {
        b[2] = 2;
        b[3] = 2;
        l.moveBoard(b);
        REQUIRE(b[0] == 4);
    }

    SECTION("Test 2 different value left merges in 1 row") {
        b[0] = 2;
        b[1] = 2;
        b[2] = 4;
        b[3] = 4;
        l.moveBoard(b);
        REQUIRE(b[0] == 4);
        REQUIRE(b[1] == 8);
        REQUIRE(b[2] == 0);
        REQUIRE(b[3] == 0);
    }

    SECTION("Test 2 same value merges left in 1 row") {
        b[0] = 2;
        b[1] = 2;
        b[2] = 2;
        b[3] = 2;
        l.moveBoard(b);
        REQUIRE(b[0] == 4);
        REQUIRE(b[1] == 4);
        REQUIRE(b[2] == 0);
        REQUIRE(b[3] == 0);
    }
}

TEST_CASE("Up") {
    Board b;
    Up u;

    SECTION("Test moving off top edge") {
        b[0] = 2;
        b[1] = 2;
        b[2] = 2;
        b[3] = 2;
        u.moveBoard(b);
        REQUIRE(b[0] == 2);
        REQUIRE(b[1] == 2);
        REQUIRE(b[2] == 2);
        REQUIRE(b[3] == 2);
    }

    SECTION("Test moving single tile up several tiles") {
        b[12] = 2;
        b[13] = 2;
        b[14] = 2;
        b[15] = 2;
        u.moveBoard(b);
        REQUIRE(b[0] == 2);
        REQUIRE(b[1] == 2);
        REQUIRE(b[2] == 2);
        REQUIRE(b[3] == 2);
    }

    SECTION("Test moving multiple tiles up with no merges") {
        b[4] = 2;
        b[8] = 4;
        b[12] = 8;
        b[9] = 2;
        b[13] = 4;
        b[6] = 2;
        b[10] = 4;
        b[3] = 2;
        b[7] = 4;
        b[11] = 8;
        u.moveBoard(b);
        REQUIRE(b[0] == 2);
        REQUIRE(b[1] == 2);
        REQUIRE(b[2] == 2);
        REQUIRE(b[3] == 2);
        REQUIRE(b[4] == 4);
        REQUIRE(b[5] == 4);
        REQUIRE(b[6] == 4);
        REQUIRE(b[7] == 4);
        REQUIRE(b[8] == 8);
        REQUIRE(b[9] == 0);
        REQUIRE(b[10] == 0);
        REQUIRE(b[11] == 8);
        REQUIRE(b[12] == 0);
        REQUIRE(b[13] == 0);
        REQUIRE(b[14] == 0);
        REQUIRE(b[15] == 0);
    }

    SECTION("Test top gridlocked") {
        b[0] = 2;
        b[4] = 4;
        b[8] = 8;
        b[12] = 16;
        u.moveBoard(b);
        REQUIRE(b[0] == 2);
        REQUIRE(b[4] == 4);
        REQUIRE(b[8] == 8);
        REQUIRE(b[12] == 16);
    }

    SECTION("Test single merge top") {
        b[0] = 2;
        b[12] = 2;
        u.moveBoard(b);
        REQUIRE(b[0] == 4);
    }

    SECTION("Test single merge top between two tiles not blocked") {
        b[8] = 2;
        b[12] = 2;
        u.moveBoard(b);
        REQUIRE(b[0] == 4);
    }

    SECTION("Test 2 different value top merges in 1 row") {
        b[0] = 2;
        b[4] = 2;
        b[8] = 4;
        b[12] = 4;
        u.moveBoard(b);
        REQUIRE(b[0] == 4);
        REQUIRE(b[4] == 8);
        REQUIRE(b[8] == 0);
        REQUIRE(b[12] == 0);
    }

    SECTION("Test 2 same value merges top in 1 row") {
        b[0] = 2;
        b[4] = 2;
        b[8] = 2;
        b[12] = 2;
        u.moveBoard(b);
        REQUIRE(b[0] == 4);
        REQUIRE(b[4] == 4);
        REQUIRE(b[8] == 0);
        REQUIRE(b[12] == 0);
    }
}

TEST_CASE("Down") {
    Board b;
    Down d;

    SECTION("Test moving off bottom edge") {
        b[12] = 2;
        b[13] = 2;
        b[14] = 2;
        b[15] = 2;
        d.moveBoard(b);
        REQUIRE(b[12] == 2);
        REQUIRE(b[13] == 2);
        REQUIRE(b[14] == 2);
        REQUIRE(b[15] == 2);
    }

    SECTION("Test moving single tile down several tiles") {
        b[0] = 2;
        b[1] = 2;
        b[2] = 2;
        b[3] = 2;
        d.moveBoard(b);
        REQUIRE(b[12] == 2);
        REQUIRE(b[13] == 2);
        REQUIRE(b[14] == 2);
        REQUIRE(b[15] == 2);
    }

    SECTION("Test moving multiple tiles down with no merges") {
        b[0] = 2;
        b[4] = 4;
        b[8] = 8;
        b[1] = 2;
        b[5] = 4;
        b[6] = 2;
        b[10] = 4;
        b[7] = 2;
        b[11] = 4;
        b[15] = 8;
        d.moveBoard(b);
        REQUIRE(b[0] == 0);
        REQUIRE(b[1] == 0);
        REQUIRE(b[2] == 0);
        REQUIRE(b[3] == 0);
        REQUIRE(b[4] == 2);
        REQUIRE(b[5] == 0);
        REQUIRE(b[6] == 0);
        REQUIRE(b[7] == 2);
        REQUIRE(b[8] == 4);
        REQUIRE(b[9] == 2);
        REQUIRE(b[10] == 2);
        REQUIRE(b[11] == 4);
        REQUIRE(b[12] == 8);
        REQUIRE(b[13] == 4);
        REQUIRE(b[14] == 4);
        REQUIRE(b[15] == 8);
    }

    SECTION("Test bottom gridlocked") {
        b[0] = 2;
        b[4] = 4;
        b[8] = 8;
        b[12] = 16;
        d.moveBoard(b);
        REQUIRE(b[0] == 2);
        REQUIRE(b[4] == 4);
        REQUIRE(b[8] == 8);
        REQUIRE(b[12] == 16);
    }

    SECTION("Test single merge bottom") {
        b[0] = 2;
        b[12] = 2;
        d.moveBoard(b);
        REQUIRE(b[12] == 4);
    }

    SECTION("Test single merge bottom between two tiles not blocked") {
        b[0] = 2;
        b[4] = 2;
        d.moveBoard(b);
        REQUIRE(b[12] == 4);
    }

    SECTION("Test 2 different value bottom merges in 1 row") {
        b[0] = 2;
        b[4] = 2;
        b[8] = 4;
        b[12] = 4;
        d.moveBoard(b);
        REQUIRE(b[0] == 0);
        REQUIRE(b[4] == 0);
        REQUIRE(b[8] == 4);
        REQUIRE(b[12] == 8);
    }

    SECTION("Test 2 same value merges bottom in 1 row") {
        b[0] = 2;
        b[4] = 2;
        b[8] = 2;
        b[12] = 2;
        d.moveBoard(b);
        REQUIRE(b[0] == 0);
        REQUIRE(b[4] == 0);
        REQUIRE(b[8] == 4);
        REQUIRE(b[12] == 4);
    }
}