#include "catch.hpp"
#include "../MoveFactory.h"

TEST_CASE("Test get") {
    MoveFactory f;

    SECTION("Test it throws an exception if not found") {
        REQUIRE_THROWS(f.get('z'));//
    }
}