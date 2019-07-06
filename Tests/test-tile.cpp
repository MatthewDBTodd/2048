#include "catch.hpp"
#include "../Tile.h"

TEST_CASE("Tile::setValue()") {
    Tile t;
    SECTION("Passing in a positive value") {
        t.setValue(4);
        REQUIRE(t.value() == 4);
    }

    SECTION("Passing in a negative value") {
        t.setValue(-2);
        REQUIRE(t.value() == 0);
    }
}

TEST_CASE("swap() function") {
    Tile t1;
    Tile t2;
    SECTION("Both having non zero values, should not allow") {
        t1.setValue(2);
        t2.setValue(4);
        swap(t1, t2);
        REQUIRE(t1.value() == 2);
        REQUIRE(t2.value() == 4);
    }

    SECTION("Swap with one zero value - should allow") {
        t2.setValue(2);
        swap(t1, t2);
        REQUIRE(t1.value() == 2);
        REQUIRE(t2.value() == 0);
    }
}

TEST_CASE("merge() functon") {
    Tile t1;
    Tile t2;

    SECTION("Attempt to merge two non-equal tiles") {
        t1.setValue(2);
        t2.setValue(4);
        merge(t1, t2);
        REQUIRE(t1.value() == 2);
        REQUIRE(t2.value() == 4);
    }

    SECTION("Attempt legitimate merge") {
        t1.setValue(4);
        t2.setValue(4);
        merge(t1, t2);
        REQUIRE(t1.value() == 0);
        REQUIRE(t2.value() == 8);
    }

    SECTION("Attempt merge on already merged tile") {
        t1.setValue(2);
        t2.setValue(2);
        merge(t2, t1);
        Tile t3;
        t3.setValue(4);  
        merge(t3, t1); // should have no effect, t1 has already merged once
        REQUIRE(t1.value() == 4);
        REQUIRE(t2.value() == 0);
        REQUIRE(t3.value() == 4);
    }
}

TEST_CASE("Test Tile::move()") {
    Tile t1;
    t1.setValue(2);
    bool result;

    SECTION("Moving a tile in to an empty tile") {
        Tile t2;
        result = t1.move(t2);
        REQUIRE(result);
        REQUIRE(t1.value() == 0);
        REQUIRE(t2.value() == 2);
    }

    SECTION("Attempting to move a tile in to an occupied non-identical tile") {
        Tile t2;
        t2.setValue(4);
        result = t1.move(t2);
        REQUIRE(!result);
        REQUIRE(t1.value() == 2);
        REQUIRE(t2.value() == 4);
    }

    SECTION("Moving a tile which results in a merge") {
        Tile t2;
        t2.setValue(2);
        result = t1.move(t2);
        REQUIRE(result);
        REQUIRE(t2.value() == 4);
        REQUIRE(t1.value() == 0);
    }
}

TEST_CASE("Test that double merges do not happen") {
    Tile t1, t2, t3;
    t3 = 4;
    t2 = 2;
    t1 = 2;
    t1.move(t2);
    REQUIRE(t2.value() == 4);
    REQUIRE(t1.value() == 0);
    t2.move(t3);
    REQUIRE(t2.value() == 4);
    REQUIRE(t3.value() == 4);
}
