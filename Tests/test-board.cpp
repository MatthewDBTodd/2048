#include "catch.hpp"
#include "../Board.h"

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

TEST_CASE("move()") {
    /*
     * test moving a tile several times until it reaches a non equal tile
     * test moving a tile several times until it reaches a merge
     * test moving a tile several times until it reaches the edge
     *
    SECTION("Moving a single tile until it reaches the edge") {
        tiles[0].setValue(2);
        move(tiles, r);
        REQUIRE(tiles[0] == 0);
        REQUIRE(tiles[1] == 0);
        REQUIRE(tiles[2] == 0);
        REQUIRE(tiles[3] == 2);
    }

    SECTION("Moving a single tile several times until it reaches a non equal tile") {
        tiles[0].setValue(2);
        tiles[3].setValue(4);
        move(tiles, r);
        REQUIRE(tiles[0] == 0);
        REQUIRE(tiles[1] == 0);
        REQUIRE(tiles[2] == 2);
        REQUIRE(tiles[3] == 4);
    }

    SECTION("Moving a single tile several times until it reaches a merge") {
        tiles[0].setValue(2);
        tiles[3].setValue(2);
        move(tiles, r);
        REQUIRE(tiles[0] == 0);
        REQUIRE(tiles[1] == 0);
        REQUIRE(tiles[2] == 0);
        REQUIRE(tiles[3] == 4);
    }
    */
}